#include "main_node.hpp"

#include <algorithm>
#include <chrono>
#include <vector>
#include <functional>

#include "signaling.pb.h"

MainNode::MainNode(ros::NodeHandle nh)
	: nh_(std::move(nh)) {
	nh_.param<bool>("debug/direct_running_mode", direct_running_mode_, false);

	// UdpModule: loads its own params; started later with session id.
	udp_module_ = std::make_unique<trb::udp::UdpModule>(
		nh_, trb::udp::UdpModule::Config::configFromRosParam(nh_));
	udp_module_->setAudioDatagramCallback(
		[this](const uint8_t* data, size_t size, uint64_t ts_ntp) {
			if (audio_module_ && audio_module_->isRunning()) {
				(void)audio_module_->pushRemoteOpusPacket(data, size, ts_ntp);
			}
		});
	udp_module_->setHandshakeReadyCallback([this]() { onUdpHandshakeReady(); });
	udp_module_->setPeerLostCallback([this]() { onUdpPeerLost(); });

	// AudioModule
	audio_module_ = std::make_unique<trb::audio::AudioModule>(
		nh_, trb::audio::AudioModule::configFromRosParam(nh_));
	audio_module_->setEncodedPacketCallback(
		std::bind(&MainNode::onEncodedAudioPacket, this,
		          std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	audio_module_->initialize();

	video_module_ = std::make_unique<trb::video::VideoModule>(
		nh_, trb::video::VideoModule::Config::configFromRosParam(nh_));
	video_module_->setEncodedFrameCallback(
		std::bind(&MainNode::onEncodedVideoFrame, this,
				  std::placeholders::_1, std::placeholders::_2,
				  std::placeholders::_3, std::placeholders::_4));
	video_module_->setSpsPpsCallback(
		std::bind(&MainNode::onSpsPpsCaptured, this,
				  std::placeholders::_1, std::placeholders::_2,
				  std::placeholders::_3));

	video_stats_timer_ = nh_.createTimer(
		ros::Duration(1.0),
		&MainNode::videoStatsTimerCallback,
		this);

	loadFovTable();

	if (direct_running_mode_) {
		udp_module_->start(std::string{});
		enterDirectRunningMode();
		ROS_INFO("teleop_robot_bridge node initialized in direct running mode");
		return;
	}

	grpc_module_ = std::make_unique<GrpcModule>(
		nh_, GrpcModule::configFromRosParam(nh_));
	grpc_module_->setRegisteredCallback([this]() { onGrpcRegistered(); });
	grpc_module_->setHeartbeatFailCallback([this]() { onGrpcHeartbeatFail(); });
	grpc_module_->setStreamEndCallback([this]() { onGrpcStreamEnd(); });
	grpc_module_->setSignalingEventCallback(
		[this](const signaling::EventMessage& msg) { onSignalingEvent(msg); });
	grpc_module_->start();

	ROS_INFO("teleop_robot_bridge node initialized");
}

MainNode::~MainNode() {
	if (negotiation_retry_timer_.hasStarted()) {
		negotiation_retry_timer_.stop();
	}
	if (video_stats_timer_.hasStarted()) {
		video_stats_timer_.stop();
	}

	// Shutdown order matters for a clean Ctrl+C:
	//   1. gRPC first: cancels all in-flight RPCs and the event stream so
	//      timer callbacks currently mid-RPC return immediately, avoiding
	//      multi-second waits on heartbeat_timer_.stop().
	//   2. Video before UDP: encoded-frame callback pushes into UdpModule.
	//   3. Audio before UDP: encoded-audio callback pushes into UdpModule.
	//   4. UDP last: its recv/send/fec/control threads are lightweight and
	//      all poll with short timeouts.
	if (grpc_module_) {
		grpc_module_->stop();
		grpc_module_.reset();
	}
	if (video_module_) {
		video_module_->stop();
		video_module_.reset();
	}
	if (audio_module_) {
		audio_module_->stop();
		audio_module_.reset();
	}
	if (udp_module_) {
		udp_module_->stop();
		udp_module_.reset();
	}
}

void MainNode::enterDirectRunningMode() {
	{
		std::lock_guard<std::mutex> lock(video_config_mutex_);
		video_config_sent_ = true;
	}
	if (audio_module_) {
		audio_module_->markConfigPublished();
	}
	setState(State::kRunning, "direct running mode");
	startVideoAndNegotiate();
	if (audio_module_) {
		audio_module_->start();
	}
}

void MainNode::ensureNegotiationRetryTimer() {
	if (negotiation_retry_timer_.hasStarted()) {
		return;
	}
	negotiation_retry_timer_ = nh_.createTimer(
		ros::Duration(1.0),
		&MainNode::negotiationRetryTimerCallback,
		this);
	ROS_INFO("Negotiation retry timer started");
}

void MainNode::stopNegotiationRetryTimer() {
	if (negotiation_retry_timer_.hasStarted()) {
		negotiation_retry_timer_.stop();
	}
}

void MainNode::negotiationRetryTimerCallback(const ros::TimerEvent &event) {
	(void)event;
	if (state_.load() != State::kNegotiating) {
		stopNegotiationRetryTimer();
		return;
	}
	ROS_INFO_THROTTLE(5.0, "Retrying AV negotiation in negotiating state");
	tryAdvanceNegotiation();
	startVideoAndNegotiate();
}

void MainNode::onEncodedVideoFrame(const uint8_t *data, size_t size, uint64_t timestamp_us, bool keyframe) {
	const State current_state = state_.load();
	if (current_state != State::kRunning) {
		static std::atomic<uint64_t> dropped_video_frames{0};
		const uint64_t total_frames = dropped_video_frames.fetch_add(1) + 1;
		if ((total_frames % 30) == 0) {
			ROS_WARN("onEncodedVideoFrame: dropping frame %lu, state=%s",
					 static_cast<unsigned long>(total_frames), stateToString(current_state));
		}
		return;
	}

	if (udp_module_) {
		udp_module_->sendH264Frame(data, size, timestamp_us, keyframe);
	}
}

void MainNode::onEncodedAudioPacket(const uint8_t *data, size_t size, uint64_t timestamp_ntp) {
	if (state_.load() != State::kRunning) {
		return;
	}
	if (!audio_module_ || !audio_module_->isConfigPublished()) {
		ROS_WARN_THROTTLE(5.0, "Dropping audio packet because AudioConfig is not published");
		return;
	}
	if (udp_module_) {
		udp_module_->sendAudioPacket(data, size, timestamp_ntp);
	}
}

bool MainNode::publishVideoConfig() {
	{
		std::lock_guard<std::mutex> lock(video_config_mutex_);
		if (video_config_sent_) {
			return true;
		}
	}
	std::vector<uint8_t> sps;
	std::vector<uint8_t> pps;
	std::vector<uint8_t> vps;
	if (!video_module_ || !video_module_->getSpsPps(sps, pps, vps)) {
		ROS_INFO_THROTTLE(5.0, "VideoConfig not ready: waiting for cached SPS/PPS");
		return false;
	}
	if (!grpc_module_) {
		ROS_WARN("GrpcModule not available, cannot send VideoConfig");
		return false;
	}
	const auto& vc = video_module_->config();
	const GrpcModule::Codec grpc_codec =
		(vc.codec == trb::video::VideoModule::Config::Codec::kH265)
			? GrpcModule::Codec::kH265
			: GrpcModule::Codec::kH264;
	bool has_fov = false;
	float hfov = 0.f, vfov = 0.f, dfov = 0.f;
	for (const auto& e : fov_table_) {
		if (e.width == vc.width && e.height == vc.height) {
			has_fov = true;
			hfov = e.hfov;
			vfov = e.vfov;
			dfov = e.dfov;
			break;
		}
	}
	if (!has_fov) {
		ROS_WARN_THROTTLE(10.0,
			"No FOV entry for %ux%u in video/fov_table; sending VideoConfig without fov",
			vc.width, vc.height);
	}
	if (!grpc_module_->publishVideoConfig(vc.width, vc.height, vc.fps,
	                                       grpc_codec, sps, pps, vps,
	                                       has_fov, hfov, vfov, dfov)) {
		return false;
	}
	{
		std::lock_guard<std::mutex> lock(video_config_mutex_);
		video_config_sent_ = true;
	}
	return true;
}

bool MainNode::publishAudioConfig() {
	if (direct_running_mode_) {
		if (audio_module_) audio_module_->markConfigPublished();
		return true;
	}
	if (!audio_module_ || !audio_module_->isEnabled() || !grpc_module_) {
		return false;
	}
	if (audio_module_->isConfigPublished()) {
		return true;
	}
	if (!grpc_module_->publishAudioConfig(audio_module_->config())) {
		return false;
	}
	audio_module_->markConfigPublished();
	return true;
}

void MainNode::tryAdvanceNegotiation() {
	if (state_.load() != State::kNegotiating) {
		return;
	}

	bool video_ready = false;
	{
		std::lock_guard<std::mutex> lock(video_config_mutex_);
		video_ready = video_config_sent_;
	}
	if (!video_ready && !publishVideoConfig()) {
		ensureNegotiationRetryTimer();
		return;
	}

	const bool audio_enabled = audio_module_ && audio_module_->isEnabled();
	if (audio_enabled && !audio_module_->isConfigPublished() && !publishAudioConfig()) {
		ensureNegotiationRetryTimer();
		return;
	}

	bool final_video_ready = false;
	{
		std::lock_guard<std::mutex> lock(video_config_mutex_);
		final_video_ready = video_config_sent_;
	}
	const bool final_audio_ready = !audio_enabled || audio_module_->isConfigPublished();
	if (!final_video_ready || !final_audio_ready) {
		ensureNegotiationRetryTimer();
		return;
	}

	stopNegotiationRetryTimer();
	setState(State::kRunning, "VideoConfig and AudioConfig ACK received");
	if (audio_module_) audio_module_->start();
}

void MainNode::startVideoAndNegotiate() {
	if (!video_module_) return;

	bool first_start = false;
	{
		std::lock_guard<std::mutex> lock(video_config_mutex_);
		if (!video_started_) {
			video_started_ = true;
			first_start = true;
		}
	}

	// VideoModule::start() is idempotent and will re-emit cached SPS/PPS
	// if already running (e.g. re-pair case).
	video_module_->start();

	if (!first_start) {
		// On re-pair the SPS/PPS callback (triggered from VideoModule::start)
		// already advances the state machine via onSpsPpsCaptured().
		// But audio config may still be pending - try advancing anyway.
		const bool audio_enabled = audio_module_ && audio_module_->isEnabled();
		bool vcs = false;
		{
			std::lock_guard<std::mutex> lock(video_config_mutex_);
			vcs = video_config_sent_;
		}
		if (state_.load() == State::kNegotiating && vcs &&
		    audio_enabled && !audio_module_->isConfigPublished()) {
			tryAdvanceNegotiation();
		}
	}
}

void MainNode::onSpsPpsCaptured(const std::vector<uint8_t> &sps,
                                const std::vector<uint8_t> &pps,
                                const std::vector<uint8_t> &vps) {
	ROS_INFO("SPS/PPS captured: sps=%zu bytes, pps=%zu bytes, vps=%zu bytes",
	         sps.size(), pps.size(), vps.size());

	const State current_state = state_.load();
	if (current_state != State::kNegotiating) {
		ROS_INFO("SPS/PPS cached, will send VideoConfig after negotiating state");
		return;
	}

	tryAdvanceNegotiation();
}

void MainNode::onGrpcRegistered() {
	stopNegotiationRetryTimer();
	setState(State::kRegistered, "grpc registered");

	// Start UdpModule with session id. If handshake is disabled, the
	// ready callback will fire synchronously inside start() and advance
	// us into pairing. Otherwise UdpModule polls until ready and fires.
	if (!udp_module_->start(grpc_module_->sessionId())) {
		ROS_WARN("UdpModule failed to start; staying in registered state");
	}
}

void MainNode::onUdpHandshakeReady() {
	enterPairingState();
}

void MainNode::onUdpPeerLost() {
	const State current = state_.load();
	if (current != State::kNegotiating && current != State::kRunning) {
		// Not in an active peer session: nothing to tear down.
		return;
	}
	teardownActiveSession("udp peer lost (no ack)", State::kPairing);
}

void MainNode::onGrpcHeartbeatFail() {
	teardownActiveSession("heartbeat failed", State::kConnecting);
}

void MainNode::onGrpcStreamEnd() {
	// This callback runs on GrpcManager's stream_thread_. We MUST NOT
	// synchronously call startEventStream() from here because that would
	// reassign stream_thread_ while it is still joinable (the very thread
	// executing this callback) -> std::terminate.
	// Defer the recovery work to the ROS main thread via a one-shot timer.
	grpc_stream_end_timer_ = nh_.createTimer(
		ros::Duration(0),
		[this](const ros::TimerEvent &) {
			// Stream is gone but heartbeat may still be fine. Drop back to
			// kRegistered (stop AV, keep UDP socket + gRPC registration),
			// then — if still registered — immediately re-subscribe and
			// re-enter pairing.
			teardownActiveSession("grpc stream ended", State::kRegistered);
			if (grpc_module_ && grpc_module_->isRegistered()) {
				grpc_module_->startEventStream();
				enterPairingState();
			}
			// else: heartbeat path will drive re-registration.
		},
		true /*oneshot*/,
		true /*autostart*/);
}

void MainNode::teardownActiveSession(const std::string &reason, State target_state) {
	stopNegotiationRetryTimer();

	if (video_module_) {
		video_module_->stop();
		video_module_->clearSpsPps();
	}
	if (audio_module_) {
		audio_module_->stop();
		audio_module_->resetConfigPublished();
	}

	{
		std::lock_guard<std::mutex> lock(video_config_mutex_);
		video_config_sent_ = false;
		video_started_ = false;
	}

	if (udp_module_) {
		switch (target_state) {
			case State::kPairing:
			case State::kRegistered:
				udp_module_->resetSession();
				break;
			case State::kConnecting:
				udp_module_->stop();
				break;
			default:
				break;
		}
	}

	setState(target_state, reason);
}

void MainNode::enterPairingState() {
	setState(State::kPairing, "waiting for pair request");
	if (grpc_module_) {
		grpc_module_->startEventStream();
	}
}

void MainNode::onSignalingEvent(const signaling::EventMessage &msg) {
	if (!msg.has_pair()) {
		return;
	}

	const auto &pair_event = msg.pair();
	const std::string peer_session_id =
		pair_event.has_peer() ? pair_event.peer().session_id() : std::string();
	switch (pair_event.op()) {
		case signaling::PairEvent::REQUEST: {
			if (peer_session_id.empty()) {
				ROS_WARN("Pair request missing peer.session_id, ignoring");
				break;
			}
			ROS_INFO("Pair request from %s, auto-accepting...", peer_session_id.c_str());
			if (grpc_module_ && grpc_module_->acceptPair(peer_session_id)) {
				setState(State::kNegotiating, "pair accepted");
				startVideoAndNegotiate();
			} else {
				ROS_WARN("Pair accept failed for %s", peer_session_id.c_str());
			}
			break;
		}
		case signaling::PairEvent::ACCEPT: {
			ROS_INFO("Pair accepted by %s", peer_session_id.c_str());
			setState(State::kNegotiating, "paired");
			startVideoAndNegotiate();
			break;
		}
		case signaling::PairEvent::REJECT: {
			ROS_WARN("Pair rejected by %s", peer_session_id.c_str());
			setState(State::kPairing, "pair rejected");
			break;
		}
		case signaling::PairEvent::UNPAIR: {
			ROS_INFO("Unpaired by %s", peer_session_id.c_str());
			teardownActiveSession("unpaired by peer", State::kPairing);
			break;
		}
		default:
			break;
	}
}

void MainNode::videoStatsTimerCallback(const ros::TimerEvent &event) {
	const double elapsed_sec = std::max(0.001, (event.current_real - event.last_real).toSec());

	uint64_t capture_frames = 0;
	uint64_t decode_frames = 0;
	uint64_t convert_frames = 0;
	uint64_t encode_frames = 0;
	uint64_t decoder_drops = 0;
	uint64_t converter_pool_drops = 0;
	uint64_t converter_failures = 0;
	uint64_t encoder_submit_failures = 0;
	uint64_t undistort_frames = 0;
	uint64_t undistort_pool_drops = 0;
	uint64_t undistort_failures = 0;
	uint64_t decode_us_total = 0;
	uint64_t transform_us_total = 0;
	uint64_t undistort_us_total = 0;
	uint64_t encode_us_total = 0;
	trb::udp::UdpManager::VideoStatsSnapshot udp_stats;
	bool have_video_module = false;
	bool have_udp_module = false;

	if (video_module_) {
		auto video_stats = video_module_->consumeStats();
		have_video_module = true;
		capture_frames = video_stats.capture_frames;
		decode_frames = video_stats.decode_frames;
		convert_frames = video_stats.convert_frames;
		encode_frames = video_stats.encode_frames;
		decoder_drops = video_stats.decoder_drops;
		converter_pool_drops = video_stats.converter_pool_drops;
		converter_failures = video_stats.converter_failures;
		encoder_submit_failures = video_stats.encoder_submit_failures;
		decode_us_total = video_stats.decode_us_total;
		transform_us_total = video_stats.transform_us_total;
		encode_us_total = video_stats.encode_us_total;
		undistort_frames = video_stats.undistort_frames;
		undistort_pool_drops = video_stats.undistort_pool_drops;
		undistort_failures = video_stats.undistort_failures;
		undistort_us_total = video_stats.undistort_us_total;
	}
	if (udp_module_ && udp_module_->isRunning()) {
		udp_stats = udp_module_->consumeVideoStats();
		have_udp_module = true;
	}

	if (!have_video_module && !have_udp_module) {
		return;
	}

	const uint64_t conv_drop_total = converter_pool_drops + converter_failures;
	const uint64_t und_drop_total = undistort_pool_drops + undistort_failures;
	const uint64_t udp_drop_total = udp_stats.input_drops + udp_stats.queue_drops;
	const bool has_activity =
		capture_frames > 0 ||
		decode_frames > 0 ||
		convert_frames > 0 ||
		undistort_frames > 0 ||
		encode_frames > 0 ||
		udp_stats.sent_frames > 0 ||
		udp_stats.queue_packets > 0 ||
		decoder_drops > 0 ||
		conv_drop_total > 0 ||
		und_drop_total > 0 ||
		encoder_submit_failures > 0 ||
		udp_drop_total > 0;
	if (!has_activity) {
		return;
	}

	const double cap_fps = static_cast<double>(capture_frames) / elapsed_sec;
	const double dec_fps = static_cast<double>(decode_frames) / elapsed_sec;
	const double conv_fps = static_cast<double>(convert_frames) / elapsed_sec;
	const double und_fps = static_cast<double>(undistort_frames) / elapsed_sec;
	const double enc_fps = static_cast<double>(encode_frames) / elapsed_sec;
	const double tx_fps = static_cast<double>(udp_stats.sent_frames) / elapsed_sec;
	const double tx_mbps = (static_cast<double>(udp_stats.sent_bytes) * 8.0 / 1000000.0) / elapsed_sec;

	const double dec_ms = decode_frames > 0
		? static_cast<double>(decode_us_total) / static_cast<double>(decode_frames) / 1000.0
		: 0.0;
	const double conv_ms = convert_frames > 0
		? static_cast<double>(transform_us_total) / static_cast<double>(convert_frames) / 1000.0
		: 0.0;
	const double und_ms = undistort_frames > 0
		? static_cast<double>(undistort_us_total) / static_cast<double>(undistort_frames) / 1000.0
		: 0.0;
	const double enc_ms = encode_frames > 0
		? static_cast<double>(encode_us_total) / static_cast<double>(encode_frames) / 1000.0
		: 0.0;
	const double cap2fec_ms = udp_stats.cap_to_fec_samples > 0
		? static_cast<double>(udp_stats.cap_to_fec_us_total) / static_cast<double>(udp_stats.cap_to_fec_samples) / 1000.0
		: 0.0;
	const double fec_wait_ms = udp_stats.fec_internal_wait_samples > 0
		? static_cast<double>(udp_stats.fec_internal_wait_us_total) / static_cast<double>(udp_stats.fec_internal_wait_samples) / 1000.0
		: 0.0;
	const double send_q_ms = udp_stats.send_queue_delay_samples > 0
		? static_cast<double>(udp_stats.send_queue_delay_us_total) / static_cast<double>(udp_stats.send_queue_delay_samples) / 1000.0
		: 0.0;
	const double send_us = udp_stats.sent_packets > 0
		? static_cast<double>(udp_stats.send_syscall_us_total) / static_cast<double>(udp_stats.sent_packets)
		: 0.0;
	const double e2e_ms = udp_stats.end_to_end_samples > 0
		? static_cast<double>(udp_stats.end_to_end_us_total) / static_cast<double>(udp_stats.end_to_end_samples) / 1000.0
		: 0.0;
	const double pacer_debt_ms = static_cast<double>(udp_stats.pacer_debt_us) / 1000.0;
	const double pacer_q_ms = static_cast<double>(udp_stats.pacer_expected_queue_us) / 1000.0;
	const double pacer_mbps = static_cast<double>(udp_stats.pacer_adjusted_bps) / 1000000.0;

	int running = video_module_ && video_module_->isRunning() ? 1 : 0;

	ROS_INFO("[VIDEO] cap=%.1ffps dec=%.1ffps conv=%.1ffps und=%.1ffps enc=%.1ffps tx=%.1ffps %.1fMbps drop=dec%lu conv%lu und%lu enc%lu udp%lu q=%zupkts/%.1fKB lat=dec%.2f conv%.2f und%.2f enc%.2f cap2fec%.2f fecwait%.2f sendq%.2f send%.1fus e2e%.2fms pacer=debt%.2f q%.2f rate%.1fMbps running=%d",
		cap_fps,
		dec_fps,
		conv_fps,
		und_fps,
		enc_fps,
		tx_fps,
		tx_mbps,
		static_cast<unsigned long>(decoder_drops),
		static_cast<unsigned long>(conv_drop_total),
		static_cast<unsigned long>(und_drop_total),
		static_cast<unsigned long>(encoder_submit_failures),
		static_cast<unsigned long>(udp_drop_total),
		udp_stats.queue_packets,
		static_cast<double>(udp_stats.queue_bytes) / 1024.0,
		dec_ms,
		conv_ms,
		und_ms,
		enc_ms,
		cap2fec_ms,
		fec_wait_ms,
		send_q_ms,
		send_us,
		e2e_ms,
		pacer_debt_ms,
		pacer_q_ms,
		pacer_mbps,
		running);
}

void MainNode::setState(State next, const std::string &reason) {
	if (state_.load() == next) {
		return;
	}
	const State prev = state_.load();
	state_.store(next);
	ROS_INFO("State transition: %s -> %s (%s)", stateToString(prev), stateToString(next), reason.c_str());
}

const char *MainNode::stateToString(State s) {
	switch (s) {
		case State::kConnecting:
			return "connecting";
		case State::kRegistered:
			return "registered";
		case State::kPairing:
			return "pairing";
		case State::kNegotiating:
			return "negotiating";
		case State::kRunning:
			return "running";
		default:
			return "unknown";
	}
}

void MainNode::loadFovTable() {
	fov_table_.clear();
	XmlRpc::XmlRpcValue list;
	if (!nh_.getParam("video/fov_table", list)) {
		ROS_WARN("video/fov_table parameter not found; VideoConfig will be sent without FOV");
		return;
	}
	if (list.getType() != XmlRpc::XmlRpcValue::TypeArray) {
		ROS_WARN("video/fov_table is not a list; ignoring");
		return;
	}
	auto getNum = [](XmlRpc::XmlRpcValue& v) -> double {
		if (v.getType() == XmlRpc::XmlRpcValue::TypeDouble) return static_cast<double>(v);
		if (v.getType() == XmlRpc::XmlRpcValue::TypeInt) return static_cast<int>(v);
		return 0.0;
	};
	for (int i = 0; i < list.size(); ++i) {
		XmlRpc::XmlRpcValue& e = list[i];
		if (e.getType() != XmlRpc::XmlRpcValue::TypeStruct) continue;
		if (!e.hasMember("width") || !e.hasMember("height") ||
		    !e.hasMember("hfov") || !e.hasMember("vfov") || !e.hasMember("dfov")) {
			ROS_WARN("video/fov_table[%d] missing fields; skipping", i);
			continue;
		}
		FovEntry fe;
		fe.width  = static_cast<uint32_t>(getNum(e["width"]));
		fe.height = static_cast<uint32_t>(getNum(e["height"]));
		fe.hfov   = static_cast<float>(getNum(e["hfov"]));
		fe.vfov   = static_cast<float>(getNum(e["vfov"]));
		fe.dfov   = static_cast<float>(getNum(e["dfov"]));
		fov_table_.push_back(fe);
	}
	ROS_INFO("Loaded %zu FOV entries from video/fov_table", fov_table_.size());
	for (const auto& e : fov_table_) {
		ROS_INFO("  %ux%u -> hfov=%.2f vfov=%.2f dfov=%.2f",
		         e.width, e.height, e.hfov, e.vfov, e.dfov);
	}
}

int main(int argc, char **argv) {
	ros::init(argc, argv, "teleop_robot_bridge");
	ros::NodeHandle nh;

	MainNode node(nh);
	ros::spin();
	return 0;
}


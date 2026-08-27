# 通用 StreamConfig：发布、拉取与生命周期

> 状态：已实施，本文与 2026-07-25 后端实现和 Proto 一致。

## 1. 职责

StreamConfig 保存某个在线发布者某条流的最新运行参数。它不是 UDP 数据流本身，不参与订阅关系，也不是网站端维护的配置范本。

运行时唯一键为 `(PublisherSessionId, Prefix)`：

* 同一发布者的一个 Prefix 最多保存一份最新配置。
* 不同发布者可以复用同一 Prefix，并分别保存自己的配置。
* 配置只保存在后端内存，不写 PostgreSQL。
* 后端不主动推送、不按配对或订阅回放；接收端主动拉取。

## 2. 配置协议归属

一条流只对应一种固定的配置 payload 协议。Manifest 的 `stream_code` 表达发布者定义的流语义，`protocol_code` 可选引用后端的 UDP 数据包协议模板；双方据此约定如何解析该流的配置 payload。


`schema_version` 保留，用于同一固定配置协议的结构演进。接收端遇到不支持的版本时应拒绝应用该配置，而不是猜测字段含义。

## 3. 当前 Proto

```proto
message PublishStreamConfigRequest {
  uint32 prefix = 1;
  uint32 schema_version = 3;
  bytes payload = 4; // 默认最大 64 KiB，由服务端配置限制
}

message GetStreamConfigRequest {
  string publisher_session_id = 1;
  uint32 prefix = 2;
}

message StreamConfigItem {
  string publisher_session_id = 1;
  uint32 prefix = 2;
  uint32 schema_version = 4;
  bytes payload = 5;
  string config_id = 6;
  uint64 version = 7;
  int64 updated_unix_time_ms = 8;
}

message StreamConfigMutationResponse {
  bool success = 1;
  string message = 2;
  StreamConfigItem item = 3;
}
```

删除的字段号保持空缺，不写 `reserved`，其他字段号不重排。

## 4. 发布规则

发布者必须使用当前已认证 Session 调用 PublishStreamConfig：


1. `prefix` 必须是 0-255 内的普通流 Prefix，不能使用后端 UDP 控制协议保留值。
2. 当前发布者必须已经在 Manifest 中声明该 Prefix。
3. `payload` 不能为空，默认最大 65,536 bytes；部署配置可以调整上限。
4. 再次发布同一 Prefix 会原子覆盖旧配置，并生成新的 `config_id`、内部版本和更新时间。

发布请求不携带 `publisher_session_id`，后端从已认证会话取得发布者身份，客户端不能替其他发布者写配置。

## 5. 主动拉取

接收端先调用 GetStreamManifest 获取目标发布者的流清单，再按 `PublisherSessionId + Prefix` 调用 GetStreamConfig。

可用入口：

* gRPC：`GetStreamConfig(GetStreamConfigRequest) -> StreamConfigItem`
* WebSocket + Protobuf：`WsEnvelope.get_stream_config` / `get_stream_config_response`
* HTTP：`GET /api/publishers/{publisherSessionId}/streams/{prefix}/config`

HTTP 和 gRPC/WS 返回同一组语义字段。配置不存在时返回 Not Found；这可能表示发布者尚未发布配置，或该流不需要额外配置。

## 6. 生命周期

* Manifest 的 `stream_code`、`stream_class_code` 或 `protocol_code` 发生身份变化时，旧配置被删除。
* DeleteStreamManifest 删除 Prefix 时，同步删除对应配置和订阅。
* 发布者 Session 注销时，删除该发布者的全部 Manifest 和配置。
* 服务进程重启后内存配置清空，发布者必须重新声明 Manifest 并重新发布必要配置。

## 7. 与配置范本的边界

网站端维护的 Video、Audio 等 StreamConfig 范本存放在 PostgreSQL，用于描述推荐字段、数据类型、单位和备注。范本不等于发布者实际配置，也不会自动生成或保存运行时 payload。

发布者可以参考范本构造固定协议 payload；真正在线使用的配置仍由发布者按 Prefix 发布并由接收端主动拉取。

## 8. 设备操作顺序


1. 发布者 Register 并取得 SessionId。
2. 硬件就绪后声明 Manifest。
3. 对需要参数的流发布 `prefix + schema_version + payload`。
4. 接收端拉取 Manifest，识别需要的 Prefix。
5. 接收端拉取 StreamConfig，校验 `schema_version` 后按该流固定协议解析 payload。
6. Manifest 身份变化或双方重连后，重新发布和重新拉取配置。

```
```
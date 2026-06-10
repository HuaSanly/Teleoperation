#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};


#[link(name = "teleop_robot_bridge__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__AgvBatteryState() -> *const std::ffi::c_void;
}

#[link(name = "teleop_robot_bridge__rosidl_generator_c")]
extern "C" {
    fn teleop_robot_bridge__msg__AgvBatteryState__init(msg: *mut AgvBatteryState) -> bool;
    fn teleop_robot_bridge__msg__AgvBatteryState__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<AgvBatteryState>, size: usize) -> bool;
    fn teleop_robot_bridge__msg__AgvBatteryState__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<AgvBatteryState>);
    fn teleop_robot_bridge__msg__AgvBatteryState__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<AgvBatteryState>, out_seq: *mut rosidl_runtime_rs::Sequence<AgvBatteryState>) -> bool;
}

// Corresponds to teleop_robot_bridge__msg__AgvBatteryState
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// AGV电池状态消息

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct AgvBatteryState {
    /// 电池状态（使用标准 BatteryState）
    pub battery_state: sensor_msgs::msg::rmw::BatteryState,

}



impl Default for AgvBatteryState {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !teleop_robot_bridge__msg__AgvBatteryState__init(&mut msg as *mut _) {
        panic!("Call to teleop_robot_bridge__msg__AgvBatteryState__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for AgvBatteryState {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__AgvBatteryState__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__AgvBatteryState__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__AgvBatteryState__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for AgvBatteryState {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for AgvBatteryState where Self: Sized {
  const TYPE_NAME: &'static str = "teleop_robot_bridge/msg/AgvBatteryState";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__AgvBatteryState() }
  }
}


#[link(name = "teleop_robot_bridge__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__AgvCmdVel() -> *const std::ffi::c_void;
}

#[link(name = "teleop_robot_bridge__rosidl_generator_c")]
extern "C" {
    fn teleop_robot_bridge__msg__AgvCmdVel__init(msg: *mut AgvCmdVel) -> bool;
    fn teleop_robot_bridge__msg__AgvCmdVel__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<AgvCmdVel>, size: usize) -> bool;
    fn teleop_robot_bridge__msg__AgvCmdVel__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<AgvCmdVel>);
    fn teleop_robot_bridge__msg__AgvCmdVel__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<AgvCmdVel>, out_seq: *mut rosidl_runtime_rs::Sequence<AgvCmdVel>) -> bool;
}

// Corresponds to teleop_robot_bridge__msg__AgvCmdVel
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// AGV 速度命令消息

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct AgvCmdVel {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,

    /// 线速度 (m/s)
    pub linear: geometry_msgs::msg::rmw::Vector3,

    /// 角速度 (rad/s)
    pub angular: geometry_msgs::msg::rmw::Vector3,

}



impl Default for AgvCmdVel {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !teleop_robot_bridge__msg__AgvCmdVel__init(&mut msg as *mut _) {
        panic!("Call to teleop_robot_bridge__msg__AgvCmdVel__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for AgvCmdVel {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__AgvCmdVel__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__AgvCmdVel__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__AgvCmdVel__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for AgvCmdVel {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for AgvCmdVel where Self: Sized {
  const TYPE_NAME: &'static str = "teleop_robot_bridge/msg/AgvCmdVel";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__AgvCmdVel() }
  }
}


#[link(name = "teleop_robot_bridge__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__AgvDeviceState() -> *const std::ffi::c_void;
}

#[link(name = "teleop_robot_bridge__rosidl_generator_c")]
extern "C" {
    fn teleop_robot_bridge__msg__AgvDeviceState__init(msg: *mut AgvDeviceState) -> bool;
    fn teleop_robot_bridge__msg__AgvDeviceState__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<AgvDeviceState>, size: usize) -> bool;
    fn teleop_robot_bridge__msg__AgvDeviceState__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<AgvDeviceState>);
    fn teleop_robot_bridge__msg__AgvDeviceState__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<AgvDeviceState>, out_seq: *mut rosidl_runtime_rs::Sequence<AgvDeviceState>) -> bool;
}

// Corresponds to teleop_robot_bridge__msg__AgvDeviceState
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// AGV设备状态消息（通用硬件状态）

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct AgvDeviceState {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,

    /// 设备健康状态
    pub health_status: u8,

    /// 错误域（单个错误代码）
    pub error_domain: u8,

    /// 操作模式
    pub operational_mode: u8,

    /// 电源状态
    pub power_state: u8,

    /// 连接状态
    pub connectivity_status: u8,

    /// 制造商名称
    pub manufacturer: rosidl_runtime_rs::String,

    /// 设备型号
    pub model: rosidl_runtime_rs::String,

    /// 固件版本
    pub firmware_version: rosidl_runtime_rs::String,

}

impl AgvDeviceState {
    /// --- Health Status Constants -------------------------------------
    pub const HEALTH_UNKNOWN: u8 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const HEALTH_OK: u8 = 1;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const HEALTH_DEGRADED: u8 = 2;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const HEALTH_WARNING: u8 = 3;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const HEALTH_ERROR: u8 = 4;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const HEALTH_FATAL: u8 = 5;

    /// --- Error Domain Constants --------------------------------------
    pub const ERROR_NONE: u8 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_UNKNOWN: u8 = 1;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_HW: u8 = 2;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_SW: u8 = 3;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_OVER_TRAVEL: u8 = 4;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const EMERGENCY_STOP_HW: u8 = 5;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const EMERGENCY_STOP_SW: u8 = 6;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const PROTECTIVE_STOP_HW: u8 = 7;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const PROTECTIVE_STOP_SW: u8 = 8;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const SAFETY_STOP: u8 = 9;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const CALIBRATION_REQUIRED: u8 = 10;

    /// --- Operational Mode Constants ----------------------------------
    pub const MODE_UNKNOWN: u8 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const MODE_MANUAL: u8 = 1;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const MODE_AUTO: u8 = 2;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const MODE_SAFE: u8 = 3;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const MODE_MAINTENANCE: u8 = 4;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const MODE_JOG_MANUAL: u8 = 5;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const MODE_ADMITTANCE: u8 = 6;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const MODE_MONITORED_STOP: u8 = 7;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const MODE_HOLD_TO_RUN: u8 = 8;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const MODE_CARTESIAN_TWIST: u8 = 9;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const MODE_CARTESIAN_POSE: u8 = 10;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const MODE_TRAJECTORY_FORWARDING: u8 = 11;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const MODE_TRAJECTORY_STREAMING: u8 = 12;

    /// --- Power State Constants ---------------------------------------
    pub const POWER_UNKNOWN: u8 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const POWER_OFF: u8 = 1;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const POWER_STANDBY: u8 = 2;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const POWER_ON: u8 = 3;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const POWER_SLEEP: u8 = 4;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const POWER_ERROR: u8 = 5;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const POWER_LEVEL_LOW: u8 = 6;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const POWER_LEVEL_CRITICAL: u8 = 7;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const POWER_CHARGING: u8 = 8;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const POWER_CHARGING_ERROR: u8 = 9;

    /// --- Connectivity Status Constants -------------------------------
    pub const CONNECT_UNKNOWN: u8 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const CONNECT_UP: u8 = 1;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const CONNECT_DOWN: u8 = 2;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const CONNECT_FAILURE: u8 = 3;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const CONNECTION_SLOW: u8 = 4;

}


impl Default for AgvDeviceState {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !teleop_robot_bridge__msg__AgvDeviceState__init(&mut msg as *mut _) {
        panic!("Call to teleop_robot_bridge__msg__AgvDeviceState__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for AgvDeviceState {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__AgvDeviceState__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__AgvDeviceState__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__AgvDeviceState__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for AgvDeviceState {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for AgvDeviceState where Self: Sized {
  const TYPE_NAME: &'static str = "teleop_robot_bridge/msg/AgvDeviceState";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__AgvDeviceState() }
  }
}


#[link(name = "teleop_robot_bridge__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__AgvImu() -> *const std::ffi::c_void;
}

#[link(name = "teleop_robot_bridge__rosidl_generator_c")]
extern "C" {
    fn teleop_robot_bridge__msg__AgvImu__init(msg: *mut AgvImu) -> bool;
    fn teleop_robot_bridge__msg__AgvImu__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<AgvImu>, size: usize) -> bool;
    fn teleop_robot_bridge__msg__AgvImu__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<AgvImu>);
    fn teleop_robot_bridge__msg__AgvImu__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<AgvImu>, out_seq: *mut rosidl_runtime_rs::Sequence<AgvImu>) -> bool;
}

// Corresponds to teleop_robot_bridge__msg__AgvImu
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// AGV IMU 消息

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct AgvImu {
    /// IMU数据（使用标准 Imu 消息）
    pub imu: sensor_msgs::msg::rmw::Imu,

    /// IMU磁场信息（使用标准 MagneticField 消息）
    pub magnetic_field: sensor_msgs::msg::rmw::MagneticField,

}



impl Default for AgvImu {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !teleop_robot_bridge__msg__AgvImu__init(&mut msg as *mut _) {
        panic!("Call to teleop_robot_bridge__msg__AgvImu__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for AgvImu {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__AgvImu__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__AgvImu__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__AgvImu__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for AgvImu {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for AgvImu where Self: Sized {
  const TYPE_NAME: &'static str = "teleop_robot_bridge/msg/AgvImu";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__AgvImu() }
  }
}


#[link(name = "teleop_robot_bridge__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__AgvJointFeedback() -> *const std::ffi::c_void;
}

#[link(name = "teleop_robot_bridge__rosidl_generator_c")]
extern "C" {
    fn teleop_robot_bridge__msg__AgvJointFeedback__init(msg: *mut AgvJointFeedback) -> bool;
    fn teleop_robot_bridge__msg__AgvJointFeedback__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<AgvJointFeedback>, size: usize) -> bool;
    fn teleop_robot_bridge__msg__AgvJointFeedback__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<AgvJointFeedback>);
    fn teleop_robot_bridge__msg__AgvJointFeedback__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<AgvJointFeedback>, out_seq: *mut rosidl_runtime_rs::Sequence<AgvJointFeedback>) -> bool;
}

// Corresponds to teleop_robot_bridge__msg__AgvJointFeedback
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// 底盘4个电机反馈

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct AgvJointFeedback {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,

    /// 关节名称
    pub name: [rosidl_runtime_rs::String; 4],

    /// 位置
    pub position: [f64; 4],

    /// 速度
    pub velocity: [f64; 4],

    /// 力矩
    pub effort: [f64; 4],

}



impl Default for AgvJointFeedback {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !teleop_robot_bridge__msg__AgvJointFeedback__init(&mut msg as *mut _) {
        panic!("Call to teleop_robot_bridge__msg__AgvJointFeedback__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for AgvJointFeedback {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__AgvJointFeedback__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__AgvJointFeedback__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__AgvJointFeedback__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for AgvJointFeedback {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for AgvJointFeedback where Self: Sized {
  const TYPE_NAME: &'static str = "teleop_robot_bridge/msg/AgvJointFeedback";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__AgvJointFeedback() }
  }
}


#[link(name = "teleop_robot_bridge__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__AgvJointStatus() -> *const std::ffi::c_void;
}

#[link(name = "teleop_robot_bridge__rosidl_generator_c")]
extern "C" {
    fn teleop_robot_bridge__msg__AgvJointStatus__init(msg: *mut AgvJointStatus) -> bool;
    fn teleop_robot_bridge__msg__AgvJointStatus__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<AgvJointStatus>, size: usize) -> bool;
    fn teleop_robot_bridge__msg__AgvJointStatus__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<AgvJointStatus>);
    fn teleop_robot_bridge__msg__AgvJointStatus__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<AgvJointStatus>, out_seq: *mut rosidl_runtime_rs::Sequence<AgvJointStatus>) -> bool;
}

// Corresponds to teleop_robot_bridge__msg__AgvJointStatus
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// AGV关节状态消息（4个执行器）

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct AgvJointStatus {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,

    /// 关节名称
    pub name: [rosidl_runtime_rs::String; 4],

    /// 4个关节的状态数组
    pub joint_status: [super::super::msg::rmw::JointStatus; 4],

}



impl Default for AgvJointStatus {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !teleop_robot_bridge__msg__AgvJointStatus__init(&mut msg as *mut _) {
        panic!("Call to teleop_robot_bridge__msg__AgvJointStatus__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for AgvJointStatus {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__AgvJointStatus__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__AgvJointStatus__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__AgvJointStatus__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for AgvJointStatus {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for AgvJointStatus where Self: Sized {
  const TYPE_NAME: &'static str = "teleop_robot_bridge/msg/AgvJointStatus";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__AgvJointStatus() }
  }
}


#[link(name = "teleop_robot_bridge__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__AgvMotionCtrl() -> *const std::ffi::c_void;
}

#[link(name = "teleop_robot_bridge__rosidl_generator_c")]
extern "C" {
    fn teleop_robot_bridge__msg__AgvMotionCtrl__init(msg: *mut AgvMotionCtrl) -> bool;
    fn teleop_robot_bridge__msg__AgvMotionCtrl__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<AgvMotionCtrl>, size: usize) -> bool;
    fn teleop_robot_bridge__msg__AgvMotionCtrl__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<AgvMotionCtrl>);
    fn teleop_robot_bridge__msg__AgvMotionCtrl__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<AgvMotionCtrl>, out_seq: *mut rosidl_runtime_rs::Sequence<AgvMotionCtrl>) -> bool;
}

// Corresponds to teleop_robot_bridge__msg__AgvMotionCtrl
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// 控制4个电机的使能/失能状态
/// 前4个元素依次对应左轮毂、右轮毂、左转向、右转向，第5个为全部使能/失能

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct AgvMotionCtrl {

    // This member is not documented.
    #[allow(missing_docs)]
    pub enable_states: [bool; 5],

}



impl Default for AgvMotionCtrl {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !teleop_robot_bridge__msg__AgvMotionCtrl__init(&mut msg as *mut _) {
        panic!("Call to teleop_robot_bridge__msg__AgvMotionCtrl__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for AgvMotionCtrl {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__AgvMotionCtrl__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__AgvMotionCtrl__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__AgvMotionCtrl__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for AgvMotionCtrl {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for AgvMotionCtrl where Self: Sized {
  const TYPE_NAME: &'static str = "teleop_robot_bridge/msg/AgvMotionCtrl";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__AgvMotionCtrl() }
  }
}


#[link(name = "teleop_robot_bridge__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__AgvUltrasonic() -> *const std::ffi::c_void;
}

#[link(name = "teleop_robot_bridge__rosidl_generator_c")]
extern "C" {
    fn teleop_robot_bridge__msg__AgvUltrasonic__init(msg: *mut AgvUltrasonic) -> bool;
    fn teleop_robot_bridge__msg__AgvUltrasonic__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<AgvUltrasonic>, size: usize) -> bool;
    fn teleop_robot_bridge__msg__AgvUltrasonic__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<AgvUltrasonic>);
    fn teleop_robot_bridge__msg__AgvUltrasonic__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<AgvUltrasonic>, out_seq: *mut rosidl_runtime_rs::Sequence<AgvUltrasonic>) -> bool;
}

// Corresponds to teleop_robot_bridge__msg__AgvUltrasonic
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// AGV 超声波传感器消息（多个传感器）

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct AgvUltrasonic {
    /// 超声波传感器数据数组（8个传感器，固定长度）
    pub ranges: [sensor_msgs::msg::rmw::Range; 8],

}



impl Default for AgvUltrasonic {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !teleop_robot_bridge__msg__AgvUltrasonic__init(&mut msg as *mut _) {
        panic!("Call to teleop_robot_bridge__msg__AgvUltrasonic__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for AgvUltrasonic {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__AgvUltrasonic__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__AgvUltrasonic__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__AgvUltrasonic__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for AgvUltrasonic {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for AgvUltrasonic where Self: Sized {
  const TYPE_NAME: &'static str = "teleop_robot_bridge/msg/AgvUltrasonic";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__AgvUltrasonic() }
  }
}


#[link(name = "teleop_robot_bridge__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__AgvVda5050State() -> *const std::ffi::c_void;
}

#[link(name = "teleop_robot_bridge__rosidl_generator_c")]
extern "C" {
    fn teleop_robot_bridge__msg__AgvVda5050State__init(msg: *mut AgvVda5050State) -> bool;
    fn teleop_robot_bridge__msg__AgvVda5050State__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<AgvVda5050State>, size: usize) -> bool;
    fn teleop_robot_bridge__msg__AgvVda5050State__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<AgvVda5050State>);
    fn teleop_robot_bridge__msg__AgvVda5050State__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<AgvVda5050State>, out_seq: *mut rosidl_runtime_rs::Sequence<AgvVda5050State>) -> bool;
}

// Corresponds to teleop_robot_bridge__msg__AgvVda5050State
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// AGV设备状态消息

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct AgvVda5050State {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,

    /// 命令ID
    pub order_id: rosidl_runtime_rs::String,

    /// 动作状态
    pub action_status: rosidl_runtime_rs::String,

    /// 最后节点ID
    pub last_node_id: i32,

    /// 是否正在行驶
    pub driving: bool,

    /// 电池电量 (%)
    pub battery_charge: f32,

    /// 操作模式
    pub operating_mode: rosidl_runtime_rs::String,

    /// 错误类型
    pub error_type: rosidl_runtime_rs::String,

    /// 错误描述
    pub error_description: rosidl_runtime_rs::String,

}

impl AgvVda5050State {
    /// --- Action Status Constants ---------------------------------------
    ///  action execution states
    /// Action is waiting to be executed
    pub const ACTION_WAITING: &'static str = "WAITING";

    /// Action is being initialized
    pub const ACTION_INITIALIZING: &'static str = "INITIALIZING";

    /// Action is currently executing
    pub const ACTION_RUNNING: &'static str = "RUNNING";

    /// Action execution is paused
    pub const ACTION_PAUSED: &'static str = "PAUSED";

    /// Action completed successfully
    pub const ACTION_FINISHED: &'static str = "FINISHED";

    /// Action execution failed
    pub const ACTION_FAILED: &'static str = "FAILED";

    /// --- Operating Mode Constants -------------------------------------
    ///  vehicle operating modes
    /// Vehicle operates autonomously
    pub const MODE_AUTOMATIC: &'static str = "AUTOMATIC";

    /// Vehicle requires operator confirmation
    pub const MODE_SEMI_AUTOMATIC: &'static str = "SEMIAUTOMATIC";

    /// Vehicle is under manual control
    pub const MODE_MANUAL: &'static str = "MANUAL";

    /// Vehicle is in service/maintenance mode
    pub const MODE_SERVICE: &'static str = "SERVICE";

    /// Vehicle is in emergency mode
    pub const MODE_EMERGENCY: &'static str = "EMERGENCY";

    /// Vehicle is in teach-in mode for route learning
    pub const MODE_TEACHIN: &'static str = "TEACHIN";

}


impl Default for AgvVda5050State {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !teleop_robot_bridge__msg__AgvVda5050State__init(&mut msg as *mut _) {
        panic!("Call to teleop_robot_bridge__msg__AgvVda5050State__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for AgvVda5050State {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__AgvVda5050State__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__AgvVda5050State__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__AgvVda5050State__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for AgvVda5050State {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for AgvVda5050State where Self: Sized {
  const TYPE_NAME: &'static str = "teleop_robot_bridge/msg/AgvVda5050State";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__AgvVda5050State() }
  }
}


#[link(name = "teleop_robot_bridge__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__AgvVel() -> *const std::ffi::c_void;
}

#[link(name = "teleop_robot_bridge__rosidl_generator_c")]
extern "C" {
    fn teleop_robot_bridge__msg__AgvVel__init(msg: *mut AgvVel) -> bool;
    fn teleop_robot_bridge__msg__AgvVel__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<AgvVel>, size: usize) -> bool;
    fn teleop_robot_bridge__msg__AgvVel__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<AgvVel>);
    fn teleop_robot_bridge__msg__AgvVel__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<AgvVel>, out_seq: *mut rosidl_runtime_rs::Sequence<AgvVel>) -> bool;
}

// Corresponds to teleop_robot_bridge__msg__AgvVel
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// AGV速度消息

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct AgvVel {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,

    /// 线速度 (m/s)
    pub linear: geometry_msgs::msg::rmw::Vector3,

    /// 角速度 (rad/s)
    pub angular: geometry_msgs::msg::rmw::Vector3,

}



impl Default for AgvVel {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !teleop_robot_bridge__msg__AgvVel__init(&mut msg as *mut _) {
        panic!("Call to teleop_robot_bridge__msg__AgvVel__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for AgvVel {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__AgvVel__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__AgvVel__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__AgvVel__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for AgvVel {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for AgvVel where Self: Sized {
  const TYPE_NAME: &'static str = "teleop_robot_bridge/msg/AgvVel";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__AgvVel() }
  }
}


#[link(name = "teleop_robot_bridge__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__ArmJointCommand() -> *const std::ffi::c_void;
}

#[link(name = "teleop_robot_bridge__rosidl_generator_c")]
extern "C" {
    fn teleop_robot_bridge__msg__ArmJointCommand__init(msg: *mut ArmJointCommand) -> bool;
    fn teleop_robot_bridge__msg__ArmJointCommand__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ArmJointCommand>, size: usize) -> bool;
    fn teleop_robot_bridge__msg__ArmJointCommand__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ArmJointCommand>);
    fn teleop_robot_bridge__msg__ArmJointCommand__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ArmJointCommand>, out_seq: *mut rosidl_runtime_rs::Sequence<ArmJointCommand>) -> bool;
}

// Corresponds to teleop_robot_bridge__msg__ArmJointCommand
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// 机械臂14个电机命令消息

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ArmJointCommand {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,

    /// 关节名称
    pub name: [rosidl_runtime_rs::String; 14],

    /// 位置
    pub position: [f64; 14],

    /// 速度
    pub velocity: [f64; 14],

    /// 力矩
    pub effort: [f64; 14],

}



impl Default for ArmJointCommand {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !teleop_robot_bridge__msg__ArmJointCommand__init(&mut msg as *mut _) {
        panic!("Call to teleop_robot_bridge__msg__ArmJointCommand__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ArmJointCommand {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__ArmJointCommand__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__ArmJointCommand__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__ArmJointCommand__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ArmJointCommand {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ArmJointCommand where Self: Sized {
  const TYPE_NAME: &'static str = "teleop_robot_bridge/msg/ArmJointCommand";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__ArmJointCommand() }
  }
}


#[link(name = "teleop_robot_bridge__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__ArmJointFeedback() -> *const std::ffi::c_void;
}

#[link(name = "teleop_robot_bridge__rosidl_generator_c")]
extern "C" {
    fn teleop_robot_bridge__msg__ArmJointFeedback__init(msg: *mut ArmJointFeedback) -> bool;
    fn teleop_robot_bridge__msg__ArmJointFeedback__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ArmJointFeedback>, size: usize) -> bool;
    fn teleop_robot_bridge__msg__ArmJointFeedback__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ArmJointFeedback>);
    fn teleop_robot_bridge__msg__ArmJointFeedback__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ArmJointFeedback>, out_seq: *mut rosidl_runtime_rs::Sequence<ArmJointFeedback>) -> bool;
}

// Corresponds to teleop_robot_bridge__msg__ArmJointFeedback
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// 机械臂14个电机反馈

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ArmJointFeedback {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,

    /// 关节名称
    pub name: [rosidl_runtime_rs::String; 14],

    /// 位置
    pub position: [f64; 14],

    /// 速度
    pub velocity: [f64; 14],

    /// 力矩
    pub effort: [f64; 14],

}



impl Default for ArmJointFeedback {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !teleop_robot_bridge__msg__ArmJointFeedback__init(&mut msg as *mut _) {
        panic!("Call to teleop_robot_bridge__msg__ArmJointFeedback__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ArmJointFeedback {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__ArmJointFeedback__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__ArmJointFeedback__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__ArmJointFeedback__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ArmJointFeedback {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ArmJointFeedback where Self: Sized {
  const TYPE_NAME: &'static str = "teleop_robot_bridge/msg/ArmJointFeedback";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__ArmJointFeedback() }
  }
}


#[link(name = "teleop_robot_bridge__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__ArmJointStatus() -> *const std::ffi::c_void;
}

#[link(name = "teleop_robot_bridge__rosidl_generator_c")]
extern "C" {
    fn teleop_robot_bridge__msg__ArmJointStatus__init(msg: *mut ArmJointStatus) -> bool;
    fn teleop_robot_bridge__msg__ArmJointStatus__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ArmJointStatus>, size: usize) -> bool;
    fn teleop_robot_bridge__msg__ArmJointStatus__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ArmJointStatus>);
    fn teleop_robot_bridge__msg__ArmJointStatus__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ArmJointStatus>, out_seq: *mut rosidl_runtime_rs::Sequence<ArmJointStatus>) -> bool;
}

// Corresponds to teleop_robot_bridge__msg__ArmJointStatus
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// Arm关节状态消息（14个执行器）

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ArmJointStatus {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,

    /// 关节名称
    pub name: [rosidl_runtime_rs::String; 14],

    /// 14个关节的状态数组
    pub joint_status: [super::super::msg::rmw::JointStatus; 14],

}



impl Default for ArmJointStatus {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !teleop_robot_bridge__msg__ArmJointStatus__init(&mut msg as *mut _) {
        panic!("Call to teleop_robot_bridge__msg__ArmJointStatus__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ArmJointStatus {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__ArmJointStatus__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__ArmJointStatus__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__ArmJointStatus__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ArmJointStatus {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ArmJointStatus where Self: Sized {
  const TYPE_NAME: &'static str = "teleop_robot_bridge/msg/ArmJointStatus";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__ArmJointStatus() }
  }
}


#[link(name = "teleop_robot_bridge__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__ArmMotionCtrl() -> *const std::ffi::c_void;
}

#[link(name = "teleop_robot_bridge__rosidl_generator_c")]
extern "C" {
    fn teleop_robot_bridge__msg__ArmMotionCtrl__init(msg: *mut ArmMotionCtrl) -> bool;
    fn teleop_robot_bridge__msg__ArmMotionCtrl__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ArmMotionCtrl>, size: usize) -> bool;
    fn teleop_robot_bridge__msg__ArmMotionCtrl__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ArmMotionCtrl>);
    fn teleop_robot_bridge__msg__ArmMotionCtrl__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ArmMotionCtrl>, out_seq: *mut rosidl_runtime_rs::Sequence<ArmMotionCtrl>) -> bool;
}

// Corresponds to teleop_robot_bridge__msg__ArmMotionCtrl
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// 控制14个电机的使能/失能状态
/// 每个元素对应一个电机（索引0~13），true表示使能，false表示失能,14为true表示全部使能,false表示全部失能

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ArmMotionCtrl {

    // This member is not documented.
    #[allow(missing_docs)]
    pub enable_states: [bool; 15],

}



impl Default for ArmMotionCtrl {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !teleop_robot_bridge__msg__ArmMotionCtrl__init(&mut msg as *mut _) {
        panic!("Call to teleop_robot_bridge__msg__ArmMotionCtrl__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ArmMotionCtrl {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__ArmMotionCtrl__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__ArmMotionCtrl__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__ArmMotionCtrl__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ArmMotionCtrl {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ArmMotionCtrl where Self: Sized {
  const TYPE_NAME: &'static str = "teleop_robot_bridge/msg/ArmMotionCtrl";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__ArmMotionCtrl() }
  }
}


#[link(name = "teleop_robot_bridge__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__EeTcpCommand() -> *const std::ffi::c_void;
}

#[link(name = "teleop_robot_bridge__rosidl_generator_c")]
extern "C" {
    fn teleop_robot_bridge__msg__EeTcpCommand__init(msg: *mut EeTcpCommand) -> bool;
    fn teleop_robot_bridge__msg__EeTcpCommand__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<EeTcpCommand>, size: usize) -> bool;
    fn teleop_robot_bridge__msg__EeTcpCommand__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<EeTcpCommand>);
    fn teleop_robot_bridge__msg__EeTcpCommand__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<EeTcpCommand>, out_seq: *mut rosidl_runtime_rs::Sequence<EeTcpCommand>) -> bool;
}

// Corresponds to teleop_robot_bridge__msg__EeTcpCommand
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// 双末端 TCP 位姿命令消息

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct EeTcpCommand {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub name: [rosidl_runtime_rs::String; 2],

    /// 前3个为name[0]的xyz，后3个为name[1]的xyz
    pub position: [f64; 6],

    /// 前3个为name[0]的欧拉角[roll, pitch, yaw]，后3个为name[1]的欧拉角[roll, pitch, yaw]
    pub euler: [f64; 6],

    /// 前4个为name[0]的四元数[x, y, z, w]，后4个为name[1]的四元数[x, y, z, w]
    pub quat: [f64; 8],

}



impl Default for EeTcpCommand {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !teleop_robot_bridge__msg__EeTcpCommand__init(&mut msg as *mut _) {
        panic!("Call to teleop_robot_bridge__msg__EeTcpCommand__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for EeTcpCommand {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__EeTcpCommand__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__EeTcpCommand__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__EeTcpCommand__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for EeTcpCommand {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for EeTcpCommand where Self: Sized {
  const TYPE_NAME: &'static str = "teleop_robot_bridge/msg/EeTcpCommand";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__EeTcpCommand() }
  }
}


#[link(name = "teleop_robot_bridge__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__GripperDeviceState() -> *const std::ffi::c_void;
}

#[link(name = "teleop_robot_bridge__rosidl_generator_c")]
extern "C" {
    fn teleop_robot_bridge__msg__GripperDeviceState__init(msg: *mut GripperDeviceState) -> bool;
    fn teleop_robot_bridge__msg__GripperDeviceState__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<GripperDeviceState>, size: usize) -> bool;
    fn teleop_robot_bridge__msg__GripperDeviceState__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<GripperDeviceState>);
    fn teleop_robot_bridge__msg__GripperDeviceState__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<GripperDeviceState>, out_seq: *mut rosidl_runtime_rs::Sequence<GripperDeviceState>) -> bool;
}

// Corresponds to teleop_robot_bridge__msg__GripperDeviceState
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// 抓手设备状态消息（支持多个设备）

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GripperDeviceState {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,

    /// 设备状态数组
    pub devices: [super::super::msg::rmw::SingleDeviceState; 2],

}



impl Default for GripperDeviceState {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !teleop_robot_bridge__msg__GripperDeviceState__init(&mut msg as *mut _) {
        panic!("Call to teleop_robot_bridge__msg__GripperDeviceState__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for GripperDeviceState {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__GripperDeviceState__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__GripperDeviceState__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__GripperDeviceState__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for GripperDeviceState {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for GripperDeviceState where Self: Sized {
  const TYPE_NAME: &'static str = "teleop_robot_bridge/msg/GripperDeviceState";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__GripperDeviceState() }
  }
}


#[link(name = "teleop_robot_bridge__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__GripperMove() -> *const std::ffi::c_void;
}

#[link(name = "teleop_robot_bridge__rosidl_generator_c")]
extern "C" {
    fn teleop_robot_bridge__msg__GripperMove__init(msg: *mut GripperMove) -> bool;
    fn teleop_robot_bridge__msg__GripperMove__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<GripperMove>, size: usize) -> bool;
    fn teleop_robot_bridge__msg__GripperMove__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<GripperMove>);
    fn teleop_robot_bridge__msg__GripperMove__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<GripperMove>, out_seq: *mut rosidl_runtime_rs::Sequence<GripperMove>) -> bool;
}

// Corresponds to teleop_robot_bridge__msg__GripperMove
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// 抓手移动命令消息（支持多个抓手）

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GripperMove {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,

    /// 抓手命令数组
    pub grippers: rosidl_runtime_rs::Sequence<super::super::msg::rmw::SingleGripperMove>,

}



impl Default for GripperMove {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !teleop_robot_bridge__msg__GripperMove__init(&mut msg as *mut _) {
        panic!("Call to teleop_robot_bridge__msg__GripperMove__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for GripperMove {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__GripperMove__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__GripperMove__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__GripperMove__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for GripperMove {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for GripperMove where Self: Sized {
  const TYPE_NAME: &'static str = "teleop_robot_bridge/msg/GripperMove";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__GripperMove() }
  }
}


#[link(name = "teleop_robot_bridge__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__GripperStatus() -> *const std::ffi::c_void;
}

#[link(name = "teleop_robot_bridge__rosidl_generator_c")]
extern "C" {
    fn teleop_robot_bridge__msg__GripperStatus__init(msg: *mut GripperStatus) -> bool;
    fn teleop_robot_bridge__msg__GripperStatus__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<GripperStatus>, size: usize) -> bool;
    fn teleop_robot_bridge__msg__GripperStatus__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<GripperStatus>);
    fn teleop_robot_bridge__msg__GripperStatus__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<GripperStatus>, out_seq: *mut rosidl_runtime_rs::Sequence<GripperStatus>) -> bool;
}

// Corresponds to teleop_robot_bridge__msg__GripperStatus
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// 抓手状态消息

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GripperStatus {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,

    /// 抓手状态数组（2个）
    pub grippers: [super::super::msg::rmw::SingleGripperStatus; 2],

}



impl Default for GripperStatus {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !teleop_robot_bridge__msg__GripperStatus__init(&mut msg as *mut _) {
        panic!("Call to teleop_robot_bridge__msg__GripperStatus__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for GripperStatus {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__GripperStatus__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__GripperStatus__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__GripperStatus__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for GripperStatus {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for GripperStatus where Self: Sized {
  const TYPE_NAME: &'static str = "teleop_robot_bridge/msg/GripperStatus";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__GripperStatus() }
  }
}


#[link(name = "teleop_robot_bridge__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__GripperTactile() -> *const std::ffi::c_void;
}

#[link(name = "teleop_robot_bridge__rosidl_generator_c")]
extern "C" {
    fn teleop_robot_bridge__msg__GripperTactile__init(msg: *mut GripperTactile) -> bool;
    fn teleop_robot_bridge__msg__GripperTactile__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<GripperTactile>, size: usize) -> bool;
    fn teleop_robot_bridge__msg__GripperTactile__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<GripperTactile>);
    fn teleop_robot_bridge__msg__GripperTactile__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<GripperTactile>, out_seq: *mut rosidl_runtime_rs::Sequence<GripperTactile>) -> bool;
}

// Corresponds to teleop_robot_bridge__msg__GripperTactile
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// 抓手触觉传感器消息（左右手）

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GripperTactile {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,

    /// 左手触觉数据
    pub left: super::super::msg::rmw::HandTactile,

    /// 右手触觉数据
    pub right: super::super::msg::rmw::HandTactile,

}



impl Default for GripperTactile {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !teleop_robot_bridge__msg__GripperTactile__init(&mut msg as *mut _) {
        panic!("Call to teleop_robot_bridge__msg__GripperTactile__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for GripperTactile {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__GripperTactile__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__GripperTactile__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__GripperTactile__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for GripperTactile {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for GripperTactile where Self: Sized {
  const TYPE_NAME: &'static str = "teleop_robot_bridge/msg/GripperTactile";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__GripperTactile() }
  }
}


#[link(name = "teleop_robot_bridge__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__HandTactile() -> *const std::ffi::c_void;
}

#[link(name = "teleop_robot_bridge__rosidl_generator_c")]
extern "C" {
    fn teleop_robot_bridge__msg__HandTactile__init(msg: *mut HandTactile) -> bool;
    fn teleop_robot_bridge__msg__HandTactile__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<HandTactile>, size: usize) -> bool;
    fn teleop_robot_bridge__msg__HandTactile__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<HandTactile>);
    fn teleop_robot_bridge__msg__HandTactile__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<HandTactile>, out_seq: *mut rosidl_runtime_rs::Sequence<HandTactile>) -> bool;
}

// Corresponds to teleop_robot_bridge__msg__HandTactile
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// 单只手的触觉传感器数据

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct HandTactile {
    /// 手指触觉传感器数据（4个传感器）
    pub finger: [i32; 4],

    /// 拇指触觉传感器数据（4个传感器）
    pub thumb: [i32; 4],

}



impl Default for HandTactile {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !teleop_robot_bridge__msg__HandTactile__init(&mut msg as *mut _) {
        panic!("Call to teleop_robot_bridge__msg__HandTactile__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for HandTactile {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__HandTactile__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__HandTactile__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__HandTactile__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for HandTactile {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for HandTactile where Self: Sized {
  const TYPE_NAME: &'static str = "teleop_robot_bridge/msg/HandTactile";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__HandTactile() }
  }
}


#[link(name = "teleop_robot_bridge__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__HeadJointCommand() -> *const std::ffi::c_void;
}

#[link(name = "teleop_robot_bridge__rosidl_generator_c")]
extern "C" {
    fn teleop_robot_bridge__msg__HeadJointCommand__init(msg: *mut HeadJointCommand) -> bool;
    fn teleop_robot_bridge__msg__HeadJointCommand__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<HeadJointCommand>, size: usize) -> bool;
    fn teleop_robot_bridge__msg__HeadJointCommand__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<HeadJointCommand>);
    fn teleop_robot_bridge__msg__HeadJointCommand__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<HeadJointCommand>, out_seq: *mut rosidl_runtime_rs::Sequence<HeadJointCommand>) -> bool;
}

// Corresponds to teleop_robot_bridge__msg__HeadJointCommand
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// 头部2个电机命令消息

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct HeadJointCommand {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,

    /// 关节名称
    pub name: [rosidl_runtime_rs::String; 2],

    /// 位置
    pub position: [f64; 2],

    /// 速度
    pub velocity: [f64; 2],

    /// 力矩
    pub effort: [f64; 2],

}



impl Default for HeadJointCommand {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !teleop_robot_bridge__msg__HeadJointCommand__init(&mut msg as *mut _) {
        panic!("Call to teleop_robot_bridge__msg__HeadJointCommand__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for HeadJointCommand {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__HeadJointCommand__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__HeadJointCommand__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__HeadJointCommand__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for HeadJointCommand {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for HeadJointCommand where Self: Sized {
  const TYPE_NAME: &'static str = "teleop_robot_bridge/msg/HeadJointCommand";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__HeadJointCommand() }
  }
}


#[link(name = "teleop_robot_bridge__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__HeadJointFeedback() -> *const std::ffi::c_void;
}

#[link(name = "teleop_robot_bridge__rosidl_generator_c")]
extern "C" {
    fn teleop_robot_bridge__msg__HeadJointFeedback__init(msg: *mut HeadJointFeedback) -> bool;
    fn teleop_robot_bridge__msg__HeadJointFeedback__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<HeadJointFeedback>, size: usize) -> bool;
    fn teleop_robot_bridge__msg__HeadJointFeedback__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<HeadJointFeedback>);
    fn teleop_robot_bridge__msg__HeadJointFeedback__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<HeadJointFeedback>, out_seq: *mut rosidl_runtime_rs::Sequence<HeadJointFeedback>) -> bool;
}

// Corresponds to teleop_robot_bridge__msg__HeadJointFeedback
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// 头部2个电机反馈

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct HeadJointFeedback {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,

    /// 关节名称
    pub name: [rosidl_runtime_rs::String; 2],

    /// 位置
    pub position: [f64; 2],

    /// 速度
    pub velocity: [f64; 2],

    /// 力矩
    pub effort: [f64; 2],

}



impl Default for HeadJointFeedback {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !teleop_robot_bridge__msg__HeadJointFeedback__init(&mut msg as *mut _) {
        panic!("Call to teleop_robot_bridge__msg__HeadJointFeedback__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for HeadJointFeedback {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__HeadJointFeedback__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__HeadJointFeedback__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__HeadJointFeedback__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for HeadJointFeedback {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for HeadJointFeedback where Self: Sized {
  const TYPE_NAME: &'static str = "teleop_robot_bridge/msg/HeadJointFeedback";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__HeadJointFeedback() }
  }
}


#[link(name = "teleop_robot_bridge__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__HeadJointStatus() -> *const std::ffi::c_void;
}

#[link(name = "teleop_robot_bridge__rosidl_generator_c")]
extern "C" {
    fn teleop_robot_bridge__msg__HeadJointStatus__init(msg: *mut HeadJointStatus) -> bool;
    fn teleop_robot_bridge__msg__HeadJointStatus__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<HeadJointStatus>, size: usize) -> bool;
    fn teleop_robot_bridge__msg__HeadJointStatus__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<HeadJointStatus>);
    fn teleop_robot_bridge__msg__HeadJointStatus__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<HeadJointStatus>, out_seq: *mut rosidl_runtime_rs::Sequence<HeadJointStatus>) -> bool;
}

// Corresponds to teleop_robot_bridge__msg__HeadJointStatus
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// 头部关节状态消息（2个执行器）

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct HeadJointStatus {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,

    /// 关节名称
    pub name: [rosidl_runtime_rs::String; 2],

    /// 4个关节的状态数组
    pub joint_status: [super::super::msg::rmw::JointStatus; 2],

}



impl Default for HeadJointStatus {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !teleop_robot_bridge__msg__HeadJointStatus__init(&mut msg as *mut _) {
        panic!("Call to teleop_robot_bridge__msg__HeadJointStatus__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for HeadJointStatus {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__HeadJointStatus__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__HeadJointStatus__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__HeadJointStatus__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for HeadJointStatus {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for HeadJointStatus where Self: Sized {
  const TYPE_NAME: &'static str = "teleop_robot_bridge/msg/HeadJointStatus";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__HeadJointStatus() }
  }
}


#[link(name = "teleop_robot_bridge__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__HeadMotionCtrl() -> *const std::ffi::c_void;
}

#[link(name = "teleop_robot_bridge__rosidl_generator_c")]
extern "C" {
    fn teleop_robot_bridge__msg__HeadMotionCtrl__init(msg: *mut HeadMotionCtrl) -> bool;
    fn teleop_robot_bridge__msg__HeadMotionCtrl__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<HeadMotionCtrl>, size: usize) -> bool;
    fn teleop_robot_bridge__msg__HeadMotionCtrl__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<HeadMotionCtrl>);
    fn teleop_robot_bridge__msg__HeadMotionCtrl__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<HeadMotionCtrl>, out_seq: *mut rosidl_runtime_rs::Sequence<HeadMotionCtrl>) -> bool;
}

// Corresponds to teleop_robot_bridge__msg__HeadMotionCtrl
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// 控制2个电机的使能/失能状态
/// 每个元素对应一个电机（索引0~1），true表示使能，false表示失能,2为true表示全部使能,false表示全部失能

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct HeadMotionCtrl {

    // This member is not documented.
    #[allow(missing_docs)]
    pub enable_states: [bool; 3],

}



impl Default for HeadMotionCtrl {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !teleop_robot_bridge__msg__HeadMotionCtrl__init(&mut msg as *mut _) {
        panic!("Call to teleop_robot_bridge__msg__HeadMotionCtrl__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for HeadMotionCtrl {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__HeadMotionCtrl__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__HeadMotionCtrl__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__HeadMotionCtrl__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for HeadMotionCtrl {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for HeadMotionCtrl where Self: Sized {
  const TYPE_NAME: &'static str = "teleop_robot_bridge/msg/HeadMotionCtrl";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__HeadMotionCtrl() }
  }
}


#[link(name = "teleop_robot_bridge__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__JointStatus() -> *const std::ffi::c_void;
}

#[link(name = "teleop_robot_bridge__rosidl_generator_c")]
extern "C" {
    fn teleop_robot_bridge__msg__JointStatus__init(msg: *mut JointStatus) -> bool;
    fn teleop_robot_bridge__msg__JointStatus__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<JointStatus>, size: usize) -> bool;
    fn teleop_robot_bridge__msg__JointStatus__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<JointStatus>);
    fn teleop_robot_bridge__msg__JointStatus__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<JointStatus>, out_seq: *mut rosidl_runtime_rs::Sequence<JointStatus>) -> bool;
}

// Corresponds to teleop_robot_bridge__msg__JointStatus
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// 单个执行器（电机+驱动器）状态

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct JointStatus {
    /// 驱动器信息
    /// 驱动器电压 (V)
    pub driver_voltage: f32,

    /// 驱动器温度 (°C)
    pub driver_temperature: f32,

    /// 驱动器状态码
    pub driver_state: u8,

    /// 电机信息
    /// 电机温度 (°C)
    pub motor_temperature: f32,

    /// 转速 (转/分钟)
    pub rpm: i32,

    /// 电流 (A)
    pub current: f32,

    /// 脉冲计数
    pub pulse_count: i64,

    /// 电机角度
    pub motor_angles: i32,

    /// 电机速度
    pub motor_speeds: i32,

    /// 电机负载
    pub motor_loads: i32,

}



impl Default for JointStatus {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !teleop_robot_bridge__msg__JointStatus__init(&mut msg as *mut _) {
        panic!("Call to teleop_robot_bridge__msg__JointStatus__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for JointStatus {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__JointStatus__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__JointStatus__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__JointStatus__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for JointStatus {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for JointStatus where Self: Sized {
  const TYPE_NAME: &'static str = "teleop_robot_bridge/msg/JointStatus";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__JointStatus() }
  }
}


#[link(name = "teleop_robot_bridge__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__JoyState() -> *const std::ffi::c_void;
}

#[link(name = "teleop_robot_bridge__rosidl_generator_c")]
extern "C" {
    fn teleop_robot_bridge__msg__JoyState__init(msg: *mut JoyState) -> bool;
    fn teleop_robot_bridge__msg__JoyState__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<JoyState>, size: usize) -> bool;
    fn teleop_robot_bridge__msg__JoyState__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<JoyState>);
    fn teleop_robot_bridge__msg__JoyState__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<JoyState>, out_seq: *mut rosidl_runtime_rs::Sequence<JoyState>) -> bool;
}

// Corresponds to teleop_robot_bridge__msg__JoyState
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// 手柄状态消息

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct JoyState {
    /// 手柄数据（使用标准 Joy 消息）
    pub joy: sensor_msgs::msg::rmw::Joy,

}



impl Default for JoyState {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !teleop_robot_bridge__msg__JoyState__init(&mut msg as *mut _) {
        panic!("Call to teleop_robot_bridge__msg__JoyState__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for JoyState {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__JoyState__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__JoyState__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__JoyState__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for JoyState {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for JoyState where Self: Sized {
  const TYPE_NAME: &'static str = "teleop_robot_bridge/msg/JoyState";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__JoyState() }
  }
}


#[link(name = "teleop_robot_bridge__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__SingleDeviceState() -> *const std::ffi::c_void;
}

#[link(name = "teleop_robot_bridge__rosidl_generator_c")]
extern "C" {
    fn teleop_robot_bridge__msg__SingleDeviceState__init(msg: *mut SingleDeviceState) -> bool;
    fn teleop_robot_bridge__msg__SingleDeviceState__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<SingleDeviceState>, size: usize) -> bool;
    fn teleop_robot_bridge__msg__SingleDeviceState__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<SingleDeviceState>);
    fn teleop_robot_bridge__msg__SingleDeviceState__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<SingleDeviceState>, out_seq: *mut rosidl_runtime_rs::Sequence<SingleDeviceState>) -> bool;
}

// Corresponds to teleop_robot_bridge__msg__SingleDeviceState
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// 设备健康状态

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SingleDeviceState {

    // This member is not documented.
    #[allow(missing_docs)]
    pub health_status: u8,

    /// 错误域列表
    pub error_domain: rosidl_runtime_rs::Sequence<u8>,

    /// --- Operational State -------------------------------------------
    /// Current operational mode of the device, see ModeStatus constants below
    pub operational_mode: u8,

    /// Current power state of the device, see PowerState constants below
    pub power_state: u8,

    /// Current connectivity status of the device, see ConnectivityStatus constants below
    pub connectivity_status: u8,

    /// --- Vendor & Version Info ----------------------------------------
    /// Device manufacturer name, e.g. "Bosch"
    pub manufacturer: rosidl_runtime_rs::String,

    /// Device model identifier, e.g. "Lidar-XYZ-v2"
    pub model: rosidl_runtime_rs::String,

    /// Current firmware version, e.g. "1.2.3"
    pub firmware_version: rosidl_runtime_rs::String,

}

impl SingleDeviceState {
    /// --- Health Status Constants -------------------------------------
    /// High-level health indicators
    pub const HEALTH_UNKNOWN: u8 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const HEALTH_OK: u8 = 1;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const HEALTH_DEGRADED: u8 = 2;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const HEALTH_WARNING: u8 = 3;

    /// Hardware stops publishing state when it returns ERROR/FATAL, how are these set/updated?
    pub const HEALTH_ERROR: u8 = 4;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const HEALTH_FATAL: u8 = 5;

    /// --- Error Domain Constants --------------------------------------
    /// Error categories
    pub const ERROR_NONE: u8 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_UNKNOWN: u8 = 1;

    /// generic hardware fault/error
    pub const ERROR_HW: u8 = 2;

    /// generic software fault/error
    pub const ERROR_SW: u8 = 3;

    /// Hardware stopped motion because position is over limits
    pub const ERROR_OVER_TRAVEL: u8 = 4;

    /// Hardware/Software emergency and safety states
    /// state of the emergency stop hardware (i.e. e-stop button state)
    pub const EMERGENCY_STOP_HW: u8 = 5;

    /// state of the emergency stop software system (over travel, pinch point)
    pub const EMERGENCY_STOP_SW: u8 = 6;

    /// state of the protective stop hardware (i.e. safety field state)
    pub const PROTECTIVE_STOP_HW: u8 = 7;

    /// state of the software protective stop
    pub const PROTECTIVE_STOP_SW: u8 = 8;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const SAFETY_STOP: u8 = 9;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const CALIBRATION_REQUIRED: u8 = 10;

    /// --- Operational Mode Constants ----------------------------------
    /// Mode of operation
    pub const MODE_UNKNOWN: u8 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const MODE_MANUAL: u8 = 1;

    /// automatic mode when the driver is remote controlling the hardware
    pub const MODE_AUTO: u8 = 2;

    /// what is the expected use case for this mode?
    pub const MODE_SAFE: u8 = 3;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const MODE_MAINTENANCE: u8 = 4;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const MODE_JOG_MANUAL: u8 = 5;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const MODE_ADMITTANCE: u8 = 6;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const MODE_MONITORED_STOP: u8 = 7;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const MODE_HOLD_TO_RUN: u8 = 8;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const MODE_CARTESIAN_TWIST: u8 = 9;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const MODE_CARTESIAN_POSE: u8 = 10;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const MODE_TRAJECTORY_FORWARDING: u8 = 11;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const MODE_TRAJECTORY_STREAMING: u8 = 12;

    /// --- Power State Constants ---------------------------------------
    /// Power states
    pub const POWER_UNKNOWN: u8 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const POWER_OFF: u8 = 1;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const POWER_STANDBY: u8 = 2;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const POWER_ON: u8 = 3;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const POWER_SLEEP: u8 = 4;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const POWER_ERROR: u8 = 5;

    /// Battery power states see BatteryState.msg
    pub const POWER_LEVEL_LOW: u8 = 6;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const POWER_LEVEL_CRITICAL: u8 = 7;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const POWER_CHARGING: u8 = 8;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const POWER_CHARGING_ERROR: u8 = 9;

    /// --- Connectivity Status Constants -------------------------------
    /// Connectivity states
    pub const CONNECT_UNKNOWN: u8 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const CONNECT_UP: u8 = 1;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const CONNECT_DOWN: u8 = 2;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const CONNECT_FAILURE: u8 = 3;

    /// to tell the controlling system it is struggling to communicate at rate
    pub const CONNECTION_SLOW: u8 = 4;

}


impl Default for SingleDeviceState {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !teleop_robot_bridge__msg__SingleDeviceState__init(&mut msg as *mut _) {
        panic!("Call to teleop_robot_bridge__msg__SingleDeviceState__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for SingleDeviceState {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__SingleDeviceState__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__SingleDeviceState__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__SingleDeviceState__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for SingleDeviceState {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for SingleDeviceState where Self: Sized {
  const TYPE_NAME: &'static str = "teleop_robot_bridge/msg/SingleDeviceState";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__SingleDeviceState() }
  }
}


#[link(name = "teleop_robot_bridge__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__SingleGripperMove() -> *const std::ffi::c_void;
}

#[link(name = "teleop_robot_bridge__rosidl_generator_c")]
extern "C" {
    fn teleop_robot_bridge__msg__SingleGripperMove__init(msg: *mut SingleGripperMove) -> bool;
    fn teleop_robot_bridge__msg__SingleGripperMove__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<SingleGripperMove>, size: usize) -> bool;
    fn teleop_robot_bridge__msg__SingleGripperMove__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<SingleGripperMove>);
    fn teleop_robot_bridge__msg__SingleGripperMove__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<SingleGripperMove>, out_seq: *mut rosidl_runtime_rs::Sequence<SingleGripperMove>) -> bool;
}

// Corresponds to teleop_robot_bridge__msg__SingleGripperMove
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// 单个抓手移动命令

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SingleGripperMove {
    /// 紧急释放标志
    pub emergency_release: bool,

    /// 紧急释放方向
    pub emergency_release_dir: u8,

    /// 停止标志
    pub stop: bool,

    /// 目标位置
    pub position: i32,

    /// 速度
    pub speed: i32,

    /// 力度
    pub force: i32,

}



impl Default for SingleGripperMove {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !teleop_robot_bridge__msg__SingleGripperMove__init(&mut msg as *mut _) {
        panic!("Call to teleop_robot_bridge__msg__SingleGripperMove__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for SingleGripperMove {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__SingleGripperMove__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__SingleGripperMove__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__SingleGripperMove__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for SingleGripperMove {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for SingleGripperMove where Self: Sized {
  const TYPE_NAME: &'static str = "teleop_robot_bridge/msg/SingleGripperMove";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__SingleGripperMove() }
  }
}


#[link(name = "teleop_robot_bridge__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__SingleGripperStatus() -> *const std::ffi::c_void;
}

#[link(name = "teleop_robot_bridge__rosidl_generator_c")]
extern "C" {
    fn teleop_robot_bridge__msg__SingleGripperStatus__init(msg: *mut SingleGripperStatus) -> bool;
    fn teleop_robot_bridge__msg__SingleGripperStatus__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<SingleGripperStatus>, size: usize) -> bool;
    fn teleop_robot_bridge__msg__SingleGripperStatus__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<SingleGripperStatus>);
    fn teleop_robot_bridge__msg__SingleGripperStatus__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<SingleGripperStatus>, out_seq: *mut rosidl_runtime_rs::Sequence<SingleGripperStatus>) -> bool;
}

// Corresponds to teleop_robot_bridge__msg__SingleGripperStatus
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// 单个抓手状态消息

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SingleGripperStatus {
    /// 状态标志
    /// 是否就绪
    pub is_ready: bool,

    /// 是否复位
    pub is_reset: bool,

    /// 是否运动中
    pub is_moving: bool,

    /// 是否检测到物体
    pub obj_detected: bool,

    /// 故障状态码
    pub fault_status: u8,

    /// 位置信息
    /// 当前位置
    pub position: i32,

    /// 目标位置
    pub requested_position: i32,

    /// 电流信息
    /// 电流 (A)
    pub current: f32,

}



impl Default for SingleGripperStatus {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !teleop_robot_bridge__msg__SingleGripperStatus__init(&mut msg as *mut _) {
        panic!("Call to teleop_robot_bridge__msg__SingleGripperStatus__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for SingleGripperStatus {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__SingleGripperStatus__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__SingleGripperStatus__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__SingleGripperStatus__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for SingleGripperStatus {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for SingleGripperStatus where Self: Sized {
  const TYPE_NAME: &'static str = "teleop_robot_bridge/msg/SingleGripperStatus";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__SingleGripperStatus() }
  }
}


#[link(name = "teleop_robot_bridge__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__Temperature() -> *const std::ffi::c_void;
}

#[link(name = "teleop_robot_bridge__rosidl_generator_c")]
extern "C" {
    fn teleop_robot_bridge__msg__Temperature__init(msg: *mut Temperature) -> bool;
    fn teleop_robot_bridge__msg__Temperature__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<Temperature>, size: usize) -> bool;
    fn teleop_robot_bridge__msg__Temperature__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<Temperature>);
    fn teleop_robot_bridge__msg__Temperature__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<Temperature>, out_seq: *mut rosidl_runtime_rs::Sequence<Temperature>) -> bool;
}

// Corresponds to teleop_robot_bridge__msg__Temperature
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// 温度传感器消息

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Temperature {
    /// 温度数据（使用标准 Temperature 消息）
    pub temperature: sensor_msgs::msg::rmw::Temperature,

}



impl Default for Temperature {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !teleop_robot_bridge__msg__Temperature__init(&mut msg as *mut _) {
        panic!("Call to teleop_robot_bridge__msg__Temperature__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for Temperature {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__Temperature__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__Temperature__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__Temperature__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for Temperature {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for Temperature where Self: Sized {
  const TYPE_NAME: &'static str = "teleop_robot_bridge/msg/Temperature";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__Temperature() }
  }
}


#[link(name = "teleop_robot_bridge__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__UpperBodyDeviceState() -> *const std::ffi::c_void;
}

#[link(name = "teleop_robot_bridge__rosidl_generator_c")]
extern "C" {
    fn teleop_robot_bridge__msg__UpperBodyDeviceState__init(msg: *mut UpperBodyDeviceState) -> bool;
    fn teleop_robot_bridge__msg__UpperBodyDeviceState__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<UpperBodyDeviceState>, size: usize) -> bool;
    fn teleop_robot_bridge__msg__UpperBodyDeviceState__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<UpperBodyDeviceState>);
    fn teleop_robot_bridge__msg__UpperBodyDeviceState__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<UpperBodyDeviceState>, out_seq: *mut rosidl_runtime_rs::Sequence<UpperBodyDeviceState>) -> bool;
}

// Corresponds to teleop_robot_bridge__msg__UpperBodyDeviceState
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// 上半身设备状态消息

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct UpperBodyDeviceState {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,

    /// 单个设备状态
    pub device_state: super::super::msg::rmw::SingleDeviceState,

}



impl Default for UpperBodyDeviceState {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !teleop_robot_bridge__msg__UpperBodyDeviceState__init(&mut msg as *mut _) {
        panic!("Call to teleop_robot_bridge__msg__UpperBodyDeviceState__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for UpperBodyDeviceState {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__UpperBodyDeviceState__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__UpperBodyDeviceState__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__UpperBodyDeviceState__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for UpperBodyDeviceState {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for UpperBodyDeviceState where Self: Sized {
  const TYPE_NAME: &'static str = "teleop_robot_bridge/msg/UpperBodyDeviceState";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__UpperBodyDeviceState() }
  }
}


#[link(name = "teleop_robot_bridge__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__WaistJointCommand() -> *const std::ffi::c_void;
}

#[link(name = "teleop_robot_bridge__rosidl_generator_c")]
extern "C" {
    fn teleop_robot_bridge__msg__WaistJointCommand__init(msg: *mut WaistJointCommand) -> bool;
    fn teleop_robot_bridge__msg__WaistJointCommand__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<WaistJointCommand>, size: usize) -> bool;
    fn teleop_robot_bridge__msg__WaistJointCommand__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<WaistJointCommand>);
    fn teleop_robot_bridge__msg__WaistJointCommand__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<WaistJointCommand>, out_seq: *mut rosidl_runtime_rs::Sequence<WaistJointCommand>) -> bool;
}

// Corresponds to teleop_robot_bridge__msg__WaistJointCommand
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// 腰部3个电机命令消息

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct WaistJointCommand {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,

    /// 关节名称
    pub name: [rosidl_runtime_rs::String; 3],

    /// 位置
    pub position: [f64; 3],

    /// 速度
    pub velocity: [f64; 3],

    /// 力矩
    pub effort: [f64; 3],

}



impl Default for WaistJointCommand {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !teleop_robot_bridge__msg__WaistJointCommand__init(&mut msg as *mut _) {
        panic!("Call to teleop_robot_bridge__msg__WaistJointCommand__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for WaistJointCommand {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__WaistJointCommand__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__WaistJointCommand__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__WaistJointCommand__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for WaistJointCommand {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for WaistJointCommand where Self: Sized {
  const TYPE_NAME: &'static str = "teleop_robot_bridge/msg/WaistJointCommand";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__WaistJointCommand() }
  }
}


#[link(name = "teleop_robot_bridge__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__WaistJointFeedback() -> *const std::ffi::c_void;
}

#[link(name = "teleop_robot_bridge__rosidl_generator_c")]
extern "C" {
    fn teleop_robot_bridge__msg__WaistJointFeedback__init(msg: *mut WaistJointFeedback) -> bool;
    fn teleop_robot_bridge__msg__WaistJointFeedback__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<WaistJointFeedback>, size: usize) -> bool;
    fn teleop_robot_bridge__msg__WaistJointFeedback__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<WaistJointFeedback>);
    fn teleop_robot_bridge__msg__WaistJointFeedback__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<WaistJointFeedback>, out_seq: *mut rosidl_runtime_rs::Sequence<WaistJointFeedback>) -> bool;
}

// Corresponds to teleop_robot_bridge__msg__WaistJointFeedback
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// 腰部3个电机反馈

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct WaistJointFeedback {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,

    /// 关节名称
    pub name: [rosidl_runtime_rs::String; 3],

    /// 位置
    pub position: [f64; 3],

    /// 速度
    pub velocity: [f64; 3],

    /// 力矩
    pub effort: [f64; 3],

}



impl Default for WaistJointFeedback {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !teleop_robot_bridge__msg__WaistJointFeedback__init(&mut msg as *mut _) {
        panic!("Call to teleop_robot_bridge__msg__WaistJointFeedback__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for WaistJointFeedback {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__WaistJointFeedback__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__WaistJointFeedback__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__WaistJointFeedback__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for WaistJointFeedback {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for WaistJointFeedback where Self: Sized {
  const TYPE_NAME: &'static str = "teleop_robot_bridge/msg/WaistJointFeedback";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__WaistJointFeedback() }
  }
}


#[link(name = "teleop_robot_bridge__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__WaistJointStatus() -> *const std::ffi::c_void;
}

#[link(name = "teleop_robot_bridge__rosidl_generator_c")]
extern "C" {
    fn teleop_robot_bridge__msg__WaistJointStatus__init(msg: *mut WaistJointStatus) -> bool;
    fn teleop_robot_bridge__msg__WaistJointStatus__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<WaistJointStatus>, size: usize) -> bool;
    fn teleop_robot_bridge__msg__WaistJointStatus__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<WaistJointStatus>);
    fn teleop_robot_bridge__msg__WaistJointStatus__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<WaistJointStatus>, out_seq: *mut rosidl_runtime_rs::Sequence<WaistJointStatus>) -> bool;
}

// Corresponds to teleop_robot_bridge__msg__WaistJointStatus
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// 腰部关节状态消息（3个执行器）

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct WaistJointStatus {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,

    /// 关节名称
    pub name: [rosidl_runtime_rs::String; 3],

    /// 4个关节的状态数组
    pub joint_status: [super::super::msg::rmw::JointStatus; 3],

}



impl Default for WaistJointStatus {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !teleop_robot_bridge__msg__WaistJointStatus__init(&mut msg as *mut _) {
        panic!("Call to teleop_robot_bridge__msg__WaistJointStatus__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for WaistJointStatus {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__WaistJointStatus__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__WaistJointStatus__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__WaistJointStatus__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for WaistJointStatus {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for WaistJointStatus where Self: Sized {
  const TYPE_NAME: &'static str = "teleop_robot_bridge/msg/WaistJointStatus";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__WaistJointStatus() }
  }
}


#[link(name = "teleop_robot_bridge__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__WaistMotionCtrl() -> *const std::ffi::c_void;
}

#[link(name = "teleop_robot_bridge__rosidl_generator_c")]
extern "C" {
    fn teleop_robot_bridge__msg__WaistMotionCtrl__init(msg: *mut WaistMotionCtrl) -> bool;
    fn teleop_robot_bridge__msg__WaistMotionCtrl__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<WaistMotionCtrl>, size: usize) -> bool;
    fn teleop_robot_bridge__msg__WaistMotionCtrl__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<WaistMotionCtrl>);
    fn teleop_robot_bridge__msg__WaistMotionCtrl__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<WaistMotionCtrl>, out_seq: *mut rosidl_runtime_rs::Sequence<WaistMotionCtrl>) -> bool;
}

// Corresponds to teleop_robot_bridge__msg__WaistMotionCtrl
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// 控制3个电机的使能/失能状态
/// 每个元素对应一个电机（索引0~2），true表示使能，false表示失能,3为true表示全部使能,false表示全部失能

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct WaistMotionCtrl {

    // This member is not documented.
    #[allow(missing_docs)]
    pub enable_states: [bool; 4],

}



impl Default for WaistMotionCtrl {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !teleop_robot_bridge__msg__WaistMotionCtrl__init(&mut msg as *mut _) {
        panic!("Call to teleop_robot_bridge__msg__WaistMotionCtrl__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for WaistMotionCtrl {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__WaistMotionCtrl__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__WaistMotionCtrl__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__WaistMotionCtrl__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for WaistMotionCtrl {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for WaistMotionCtrl where Self: Sized {
  const TYPE_NAME: &'static str = "teleop_robot_bridge/msg/WaistMotionCtrl";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__WaistMotionCtrl() }
  }
}


#[link(name = "teleop_robot_bridge__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__WaistTcpCommand() -> *const std::ffi::c_void;
}

#[link(name = "teleop_robot_bridge__rosidl_generator_c")]
extern "C" {
    fn teleop_robot_bridge__msg__WaistTcpCommand__init(msg: *mut WaistTcpCommand) -> bool;
    fn teleop_robot_bridge__msg__WaistTcpCommand__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<WaistTcpCommand>, size: usize) -> bool;
    fn teleop_robot_bridge__msg__WaistTcpCommand__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<WaistTcpCommand>);
    fn teleop_robot_bridge__msg__WaistTcpCommand__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<WaistTcpCommand>, out_seq: *mut rosidl_runtime_rs::Sequence<WaistTcpCommand>) -> bool;
}

// Corresponds to teleop_robot_bridge__msg__WaistTcpCommand
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// 腰部 TCP 位姿命令消息

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct WaistTcpCommand {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub name: [rosidl_runtime_rs::String; 1],


    // This member is not documented.
    #[allow(missing_docs)]
    pub position: [f64; 3],

    /// 欧拉角顺序为[roll, pitch, yaw]
    pub euler: [f64; 3],

    /// 四元数顺序为[x, y, z, w]
    pub quat: [f64; 4],

}



impl Default for WaistTcpCommand {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !teleop_robot_bridge__msg__WaistTcpCommand__init(&mut msg as *mut _) {
        panic!("Call to teleop_robot_bridge__msg__WaistTcpCommand__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for WaistTcpCommand {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__WaistTcpCommand__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__WaistTcpCommand__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { teleop_robot_bridge__msg__WaistTcpCommand__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for WaistTcpCommand {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for WaistTcpCommand where Self: Sized {
  const TYPE_NAME: &'static str = "teleop_robot_bridge/msg/WaistTcpCommand";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__teleop_robot_bridge__msg__WaistTcpCommand() }
  }
}



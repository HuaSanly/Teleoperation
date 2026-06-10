#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



// Corresponds to teleop_robot_bridge__msg__AgvBatteryState
/// AGV电池状态消息

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct AgvBatteryState {
    /// 电池状态（使用标准 BatteryState）
    pub battery_state: sensor_msgs::msg::BatteryState,

}



impl Default for AgvBatteryState {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::AgvBatteryState::default())
  }
}

impl rosidl_runtime_rs::Message for AgvBatteryState {
  type RmwMsg = super::msg::rmw::AgvBatteryState;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        battery_state: sensor_msgs::msg::BatteryState::into_rmw_message(std::borrow::Cow::Owned(msg.battery_state)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        battery_state: sensor_msgs::msg::BatteryState::into_rmw_message(std::borrow::Cow::Borrowed(&msg.battery_state)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      battery_state: sensor_msgs::msg::BatteryState::from_rmw_message(msg.battery_state),
    }
  }
}


// Corresponds to teleop_robot_bridge__msg__AgvCmdVel
/// AGV 速度命令消息

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct AgvCmdVel {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,

    /// 线速度 (m/s)
    pub linear: geometry_msgs::msg::Vector3,

    /// 角速度 (rad/s)
    pub angular: geometry_msgs::msg::Vector3,

}



impl Default for AgvCmdVel {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::AgvCmdVel::default())
  }
}

impl rosidl_runtime_rs::Message for AgvCmdVel {
  type RmwMsg = super::msg::rmw::AgvCmdVel;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        linear: geometry_msgs::msg::Vector3::into_rmw_message(std::borrow::Cow::Owned(msg.linear)).into_owned(),
        angular: geometry_msgs::msg::Vector3::into_rmw_message(std::borrow::Cow::Owned(msg.angular)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
        linear: geometry_msgs::msg::Vector3::into_rmw_message(std::borrow::Cow::Borrowed(&msg.linear)).into_owned(),
        angular: geometry_msgs::msg::Vector3::into_rmw_message(std::borrow::Cow::Borrowed(&msg.angular)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      linear: geometry_msgs::msg::Vector3::from_rmw_message(msg.linear),
      angular: geometry_msgs::msg::Vector3::from_rmw_message(msg.angular),
    }
  }
}


// Corresponds to teleop_robot_bridge__msg__AgvDeviceState
/// AGV设备状态消息（通用硬件状态）

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct AgvDeviceState {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,

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
    pub manufacturer: std::string::String,

    /// 设备型号
    pub model: std::string::String,

    /// 固件版本
    pub firmware_version: std::string::String,

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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::AgvDeviceState::default())
  }
}

impl rosidl_runtime_rs::Message for AgvDeviceState {
  type RmwMsg = super::msg::rmw::AgvDeviceState;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        health_status: msg.health_status,
        error_domain: msg.error_domain,
        operational_mode: msg.operational_mode,
        power_state: msg.power_state,
        connectivity_status: msg.connectivity_status,
        manufacturer: msg.manufacturer.as_str().into(),
        model: msg.model.as_str().into(),
        firmware_version: msg.firmware_version.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
      health_status: msg.health_status,
      error_domain: msg.error_domain,
      operational_mode: msg.operational_mode,
      power_state: msg.power_state,
      connectivity_status: msg.connectivity_status,
        manufacturer: msg.manufacturer.as_str().into(),
        model: msg.model.as_str().into(),
        firmware_version: msg.firmware_version.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      health_status: msg.health_status,
      error_domain: msg.error_domain,
      operational_mode: msg.operational_mode,
      power_state: msg.power_state,
      connectivity_status: msg.connectivity_status,
      manufacturer: msg.manufacturer.to_string(),
      model: msg.model.to_string(),
      firmware_version: msg.firmware_version.to_string(),
    }
  }
}


// Corresponds to teleop_robot_bridge__msg__AgvImu
/// AGV IMU 消息

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct AgvImu {
    /// IMU数据（使用标准 Imu 消息）
    pub imu: sensor_msgs::msg::Imu,

    /// IMU磁场信息（使用标准 MagneticField 消息）
    pub magnetic_field: sensor_msgs::msg::MagneticField,

}



impl Default for AgvImu {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::AgvImu::default())
  }
}

impl rosidl_runtime_rs::Message for AgvImu {
  type RmwMsg = super::msg::rmw::AgvImu;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        imu: sensor_msgs::msg::Imu::into_rmw_message(std::borrow::Cow::Owned(msg.imu)).into_owned(),
        magnetic_field: sensor_msgs::msg::MagneticField::into_rmw_message(std::borrow::Cow::Owned(msg.magnetic_field)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        imu: sensor_msgs::msg::Imu::into_rmw_message(std::borrow::Cow::Borrowed(&msg.imu)).into_owned(),
        magnetic_field: sensor_msgs::msg::MagneticField::into_rmw_message(std::borrow::Cow::Borrowed(&msg.magnetic_field)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      imu: sensor_msgs::msg::Imu::from_rmw_message(msg.imu),
      magnetic_field: sensor_msgs::msg::MagneticField::from_rmw_message(msg.magnetic_field),
    }
  }
}


// Corresponds to teleop_robot_bridge__msg__AgvJointFeedback
/// 底盘4个电机反馈

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct AgvJointFeedback {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,

    /// 关节名称
    pub name: [std::string::String; 4],

    /// 位置
    pub position: [f64; 4],

    /// 速度
    pub velocity: [f64; 4],

    /// 力矩
    pub effort: [f64; 4],

}



impl Default for AgvJointFeedback {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::AgvJointFeedback::default())
  }
}

impl rosidl_runtime_rs::Message for AgvJointFeedback {
  type RmwMsg = super::msg::rmw::AgvJointFeedback;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        name: msg.name
          .map(|elem| elem.as_str().into()),
        position: msg.position,
        velocity: msg.velocity,
        effort: msg.effort,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
        name: msg.name
          .iter()
          .map(|elem| elem.as_str().into())
          .collect::<Vec<_>>()
          .try_into()
          .unwrap(),
        position: msg.position,
        velocity: msg.velocity,
        effort: msg.effort,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      name: msg.name
        .map(|elem| elem.to_string()),
      position: msg.position,
      velocity: msg.velocity,
      effort: msg.effort,
    }
  }
}


// Corresponds to teleop_robot_bridge__msg__AgvJointStatus
/// AGV关节状态消息（4个执行器）

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct AgvJointStatus {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,

    /// 关节名称
    pub name: [std::string::String; 4],

    /// 4个关节的状态数组
    pub joint_status: [super::msg::JointStatus; 4],

}



impl Default for AgvJointStatus {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::AgvJointStatus::default())
  }
}

impl rosidl_runtime_rs::Message for AgvJointStatus {
  type RmwMsg = super::msg::rmw::AgvJointStatus;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        name: msg.name
          .map(|elem| elem.as_str().into()),
        joint_status: msg.joint_status
          .map(|elem| super::msg::JointStatus::into_rmw_message(std::borrow::Cow::Owned(elem)).into_owned()),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
        name: msg.name
          .iter()
          .map(|elem| elem.as_str().into())
          .collect::<Vec<_>>()
          .try_into()
          .unwrap(),
        joint_status: msg.joint_status
          .iter()
          .map(|elem| super::msg::JointStatus::into_rmw_message(std::borrow::Cow::Borrowed(elem)).into_owned())
          .collect::<Vec<_>>()
          .try_into()
          .unwrap(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      name: msg.name
        .map(|elem| elem.to_string()),
      joint_status: msg.joint_status
        .map(super::msg::JointStatus::from_rmw_message),
    }
  }
}


// Corresponds to teleop_robot_bridge__msg__AgvMotionCtrl
/// 控制4个电机的使能/失能状态
/// 前4个元素依次对应左轮毂、右轮毂、左转向、右转向，第5个为全部使能/失能

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct AgvMotionCtrl {

    // This member is not documented.
    #[allow(missing_docs)]
    pub enable_states: [bool; 5],

}



impl Default for AgvMotionCtrl {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::AgvMotionCtrl::default())
  }
}

impl rosidl_runtime_rs::Message for AgvMotionCtrl {
  type RmwMsg = super::msg::rmw::AgvMotionCtrl;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        enable_states: msg.enable_states,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        enable_states: msg.enable_states,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      enable_states: msg.enable_states,
    }
  }
}


// Corresponds to teleop_robot_bridge__msg__AgvUltrasonic
/// AGV 超声波传感器消息（多个传感器）

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct AgvUltrasonic {
    /// 超声波传感器数据数组（8个传感器，固定长度）
    pub ranges: [sensor_msgs::msg::Range; 8],

}



impl Default for AgvUltrasonic {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::AgvUltrasonic::default())
  }
}

impl rosidl_runtime_rs::Message for AgvUltrasonic {
  type RmwMsg = super::msg::rmw::AgvUltrasonic;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        ranges: msg.ranges
          .map(|elem| sensor_msgs::msg::Range::into_rmw_message(std::borrow::Cow::Owned(elem)).into_owned()),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        ranges: msg.ranges
          .iter()
          .map(|elem| sensor_msgs::msg::Range::into_rmw_message(std::borrow::Cow::Borrowed(elem)).into_owned())
          .collect::<Vec<_>>()
          .try_into()
          .unwrap(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      ranges: msg.ranges
        .map(sensor_msgs::msg::Range::from_rmw_message),
    }
  }
}


// Corresponds to teleop_robot_bridge__msg__AgvVda5050State
/// AGV设备状态消息

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct AgvVda5050State {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,

    /// 命令ID
    pub order_id: std::string::String,

    /// 动作状态
    pub action_status: std::string::String,

    /// 最后节点ID
    pub last_node_id: i32,

    /// 是否正在行驶
    pub driving: bool,

    /// 电池电量 (%)
    pub battery_charge: f32,

    /// 操作模式
    pub operating_mode: std::string::String,

    /// 错误类型
    pub error_type: std::string::String,

    /// 错误描述
    pub error_description: std::string::String,

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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::AgvVda5050State::default())
  }
}

impl rosidl_runtime_rs::Message for AgvVda5050State {
  type RmwMsg = super::msg::rmw::AgvVda5050State;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        order_id: msg.order_id.as_str().into(),
        action_status: msg.action_status.as_str().into(),
        last_node_id: msg.last_node_id,
        driving: msg.driving,
        battery_charge: msg.battery_charge,
        operating_mode: msg.operating_mode.as_str().into(),
        error_type: msg.error_type.as_str().into(),
        error_description: msg.error_description.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
        order_id: msg.order_id.as_str().into(),
        action_status: msg.action_status.as_str().into(),
      last_node_id: msg.last_node_id,
      driving: msg.driving,
      battery_charge: msg.battery_charge,
        operating_mode: msg.operating_mode.as_str().into(),
        error_type: msg.error_type.as_str().into(),
        error_description: msg.error_description.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      order_id: msg.order_id.to_string(),
      action_status: msg.action_status.to_string(),
      last_node_id: msg.last_node_id,
      driving: msg.driving,
      battery_charge: msg.battery_charge,
      operating_mode: msg.operating_mode.to_string(),
      error_type: msg.error_type.to_string(),
      error_description: msg.error_description.to_string(),
    }
  }
}


// Corresponds to teleop_robot_bridge__msg__AgvVel
/// AGV速度消息

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct AgvVel {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,

    /// 线速度 (m/s)
    pub linear: geometry_msgs::msg::Vector3,

    /// 角速度 (rad/s)
    pub angular: geometry_msgs::msg::Vector3,

}



impl Default for AgvVel {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::AgvVel::default())
  }
}

impl rosidl_runtime_rs::Message for AgvVel {
  type RmwMsg = super::msg::rmw::AgvVel;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        linear: geometry_msgs::msg::Vector3::into_rmw_message(std::borrow::Cow::Owned(msg.linear)).into_owned(),
        angular: geometry_msgs::msg::Vector3::into_rmw_message(std::borrow::Cow::Owned(msg.angular)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
        linear: geometry_msgs::msg::Vector3::into_rmw_message(std::borrow::Cow::Borrowed(&msg.linear)).into_owned(),
        angular: geometry_msgs::msg::Vector3::into_rmw_message(std::borrow::Cow::Borrowed(&msg.angular)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      linear: geometry_msgs::msg::Vector3::from_rmw_message(msg.linear),
      angular: geometry_msgs::msg::Vector3::from_rmw_message(msg.angular),
    }
  }
}


// Corresponds to teleop_robot_bridge__msg__ArmJointCommand
/// 机械臂14个电机命令消息

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ArmJointCommand {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,

    /// 关节名称
    pub name: [std::string::String; 14],

    /// 位置
    pub position: [f64; 14],

    /// 速度
    pub velocity: [f64; 14],

    /// 力矩
    pub effort: [f64; 14],

}



impl Default for ArmJointCommand {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::ArmJointCommand::default())
  }
}

impl rosidl_runtime_rs::Message for ArmJointCommand {
  type RmwMsg = super::msg::rmw::ArmJointCommand;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        name: msg.name
          .map(|elem| elem.as_str().into()),
        position: msg.position,
        velocity: msg.velocity,
        effort: msg.effort,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
        name: msg.name
          .iter()
          .map(|elem| elem.as_str().into())
          .collect::<Vec<_>>()
          .try_into()
          .unwrap(),
        position: msg.position,
        velocity: msg.velocity,
        effort: msg.effort,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      name: msg.name
        .map(|elem| elem.to_string()),
      position: msg.position,
      velocity: msg.velocity,
      effort: msg.effort,
    }
  }
}


// Corresponds to teleop_robot_bridge__msg__ArmJointFeedback
/// 机械臂14个电机反馈

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ArmJointFeedback {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,

    /// 关节名称
    pub name: [std::string::String; 14],

    /// 位置
    pub position: [f64; 14],

    /// 速度
    pub velocity: [f64; 14],

    /// 力矩
    pub effort: [f64; 14],

}



impl Default for ArmJointFeedback {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::ArmJointFeedback::default())
  }
}

impl rosidl_runtime_rs::Message for ArmJointFeedback {
  type RmwMsg = super::msg::rmw::ArmJointFeedback;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        name: msg.name
          .map(|elem| elem.as_str().into()),
        position: msg.position,
        velocity: msg.velocity,
        effort: msg.effort,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
        name: msg.name
          .iter()
          .map(|elem| elem.as_str().into())
          .collect::<Vec<_>>()
          .try_into()
          .unwrap(),
        position: msg.position,
        velocity: msg.velocity,
        effort: msg.effort,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      name: msg.name
        .map(|elem| elem.to_string()),
      position: msg.position,
      velocity: msg.velocity,
      effort: msg.effort,
    }
  }
}


// Corresponds to teleop_robot_bridge__msg__ArmJointStatus
/// Arm关节状态消息（14个执行器）

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ArmJointStatus {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,

    /// 关节名称
    pub name: [std::string::String; 14],

    /// 14个关节的状态数组
    pub joint_status: [super::msg::JointStatus; 14],

}



impl Default for ArmJointStatus {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::ArmJointStatus::default())
  }
}

impl rosidl_runtime_rs::Message for ArmJointStatus {
  type RmwMsg = super::msg::rmw::ArmJointStatus;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        name: msg.name
          .map(|elem| elem.as_str().into()),
        joint_status: msg.joint_status
          .map(|elem| super::msg::JointStatus::into_rmw_message(std::borrow::Cow::Owned(elem)).into_owned()),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
        name: msg.name
          .iter()
          .map(|elem| elem.as_str().into())
          .collect::<Vec<_>>()
          .try_into()
          .unwrap(),
        joint_status: msg.joint_status
          .iter()
          .map(|elem| super::msg::JointStatus::into_rmw_message(std::borrow::Cow::Borrowed(elem)).into_owned())
          .collect::<Vec<_>>()
          .try_into()
          .unwrap(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      name: msg.name
        .map(|elem| elem.to_string()),
      joint_status: msg.joint_status
        .map(super::msg::JointStatus::from_rmw_message),
    }
  }
}


// Corresponds to teleop_robot_bridge__msg__ArmMotionCtrl
/// 控制14个电机的使能/失能状态
/// 每个元素对应一个电机（索引0~13），true表示使能，false表示失能,14为true表示全部使能,false表示全部失能

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ArmMotionCtrl {

    // This member is not documented.
    #[allow(missing_docs)]
    pub enable_states: [bool; 15],

}



impl Default for ArmMotionCtrl {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::ArmMotionCtrl::default())
  }
}

impl rosidl_runtime_rs::Message for ArmMotionCtrl {
  type RmwMsg = super::msg::rmw::ArmMotionCtrl;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        enable_states: msg.enable_states,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        enable_states: msg.enable_states,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      enable_states: msg.enable_states,
    }
  }
}


// Corresponds to teleop_robot_bridge__msg__EeTcpCommand
/// 双末端 TCP 位姿命令消息

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct EeTcpCommand {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub name: [std::string::String; 2],

    /// 前3个为name[0]的xyz，后3个为name[1]的xyz
    pub position: [f64; 6],

    /// 前3个为name[0]的欧拉角[roll, pitch, yaw]，后3个为name[1]的欧拉角[roll, pitch, yaw]
    pub euler: [f64; 6],

    /// 前4个为name[0]的四元数[x, y, z, w]，后4个为name[1]的四元数[x, y, z, w]
    pub quat: [f64; 8],

}



impl Default for EeTcpCommand {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::EeTcpCommand::default())
  }
}

impl rosidl_runtime_rs::Message for EeTcpCommand {
  type RmwMsg = super::msg::rmw::EeTcpCommand;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        name: msg.name
          .map(|elem| elem.as_str().into()),
        position: msg.position,
        euler: msg.euler,
        quat: msg.quat,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
        name: msg.name
          .iter()
          .map(|elem| elem.as_str().into())
          .collect::<Vec<_>>()
          .try_into()
          .unwrap(),
        position: msg.position,
        euler: msg.euler,
        quat: msg.quat,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      name: msg.name
        .map(|elem| elem.to_string()),
      position: msg.position,
      euler: msg.euler,
      quat: msg.quat,
    }
  }
}


// Corresponds to teleop_robot_bridge__msg__GripperDeviceState
/// 抓手设备状态消息（支持多个设备）

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GripperDeviceState {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,

    /// 设备状态数组
    pub devices: [super::msg::SingleDeviceState; 2],

}



impl Default for GripperDeviceState {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::GripperDeviceState::default())
  }
}

impl rosidl_runtime_rs::Message for GripperDeviceState {
  type RmwMsg = super::msg::rmw::GripperDeviceState;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        devices: msg.devices
          .map(|elem| super::msg::SingleDeviceState::into_rmw_message(std::borrow::Cow::Owned(elem)).into_owned()),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
        devices: msg.devices
          .iter()
          .map(|elem| super::msg::SingleDeviceState::into_rmw_message(std::borrow::Cow::Borrowed(elem)).into_owned())
          .collect::<Vec<_>>()
          .try_into()
          .unwrap(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      devices: msg.devices
        .map(super::msg::SingleDeviceState::from_rmw_message),
    }
  }
}


// Corresponds to teleop_robot_bridge__msg__GripperMove
/// 抓手移动命令消息（支持多个抓手）

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GripperMove {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,

    /// 抓手命令数组
    pub grippers: Vec<super::msg::SingleGripperMove>,

}



impl Default for GripperMove {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::GripperMove::default())
  }
}

impl rosidl_runtime_rs::Message for GripperMove {
  type RmwMsg = super::msg::rmw::GripperMove;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        grippers: msg.grippers
          .into_iter()
          .map(|elem| super::msg::SingleGripperMove::into_rmw_message(std::borrow::Cow::Owned(elem)).into_owned())
          .collect(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
        grippers: msg.grippers
          .iter()
          .map(|elem| super::msg::SingleGripperMove::into_rmw_message(std::borrow::Cow::Borrowed(elem)).into_owned())
          .collect(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      grippers: msg.grippers
          .into_iter()
          .map(super::msg::SingleGripperMove::from_rmw_message)
          .collect(),
    }
  }
}


// Corresponds to teleop_robot_bridge__msg__GripperStatus
/// 抓手状态消息

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GripperStatus {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,

    /// 抓手状态数组（2个）
    pub grippers: [super::msg::SingleGripperStatus; 2],

}



impl Default for GripperStatus {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::GripperStatus::default())
  }
}

impl rosidl_runtime_rs::Message for GripperStatus {
  type RmwMsg = super::msg::rmw::GripperStatus;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        grippers: msg.grippers
          .map(|elem| super::msg::SingleGripperStatus::into_rmw_message(std::borrow::Cow::Owned(elem)).into_owned()),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
        grippers: msg.grippers
          .iter()
          .map(|elem| super::msg::SingleGripperStatus::into_rmw_message(std::borrow::Cow::Borrowed(elem)).into_owned())
          .collect::<Vec<_>>()
          .try_into()
          .unwrap(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      grippers: msg.grippers
        .map(super::msg::SingleGripperStatus::from_rmw_message),
    }
  }
}


// Corresponds to teleop_robot_bridge__msg__GripperTactile
/// 抓手触觉传感器消息（左右手）

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GripperTactile {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,

    /// 左手触觉数据
    pub left: super::msg::HandTactile,

    /// 右手触觉数据
    pub right: super::msg::HandTactile,

}



impl Default for GripperTactile {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::GripperTactile::default())
  }
}

impl rosidl_runtime_rs::Message for GripperTactile {
  type RmwMsg = super::msg::rmw::GripperTactile;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        left: super::msg::HandTactile::into_rmw_message(std::borrow::Cow::Owned(msg.left)).into_owned(),
        right: super::msg::HandTactile::into_rmw_message(std::borrow::Cow::Owned(msg.right)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
        left: super::msg::HandTactile::into_rmw_message(std::borrow::Cow::Borrowed(&msg.left)).into_owned(),
        right: super::msg::HandTactile::into_rmw_message(std::borrow::Cow::Borrowed(&msg.right)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      left: super::msg::HandTactile::from_rmw_message(msg.left),
      right: super::msg::HandTactile::from_rmw_message(msg.right),
    }
  }
}


// Corresponds to teleop_robot_bridge__msg__HandTactile
/// 单只手的触觉传感器数据

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct HandTactile {
    /// 手指触觉传感器数据（4个传感器）
    pub finger: [i32; 4],

    /// 拇指触觉传感器数据（4个传感器）
    pub thumb: [i32; 4],

}



impl Default for HandTactile {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::HandTactile::default())
  }
}

impl rosidl_runtime_rs::Message for HandTactile {
  type RmwMsg = super::msg::rmw::HandTactile;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        finger: msg.finger,
        thumb: msg.thumb,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        finger: msg.finger,
        thumb: msg.thumb,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      finger: msg.finger,
      thumb: msg.thumb,
    }
  }
}


// Corresponds to teleop_robot_bridge__msg__HeadJointCommand
/// 头部2个电机命令消息

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct HeadJointCommand {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,

    /// 关节名称
    pub name: [std::string::String; 2],

    /// 位置
    pub position: [f64; 2],

    /// 速度
    pub velocity: [f64; 2],

    /// 力矩
    pub effort: [f64; 2],

}



impl Default for HeadJointCommand {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::HeadJointCommand::default())
  }
}

impl rosidl_runtime_rs::Message for HeadJointCommand {
  type RmwMsg = super::msg::rmw::HeadJointCommand;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        name: msg.name
          .map(|elem| elem.as_str().into()),
        position: msg.position,
        velocity: msg.velocity,
        effort: msg.effort,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
        name: msg.name
          .iter()
          .map(|elem| elem.as_str().into())
          .collect::<Vec<_>>()
          .try_into()
          .unwrap(),
        position: msg.position,
        velocity: msg.velocity,
        effort: msg.effort,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      name: msg.name
        .map(|elem| elem.to_string()),
      position: msg.position,
      velocity: msg.velocity,
      effort: msg.effort,
    }
  }
}


// Corresponds to teleop_robot_bridge__msg__HeadJointFeedback
/// 头部2个电机反馈

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct HeadJointFeedback {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,

    /// 关节名称
    pub name: [std::string::String; 2],

    /// 位置
    pub position: [f64; 2],

    /// 速度
    pub velocity: [f64; 2],

    /// 力矩
    pub effort: [f64; 2],

}



impl Default for HeadJointFeedback {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::HeadJointFeedback::default())
  }
}

impl rosidl_runtime_rs::Message for HeadJointFeedback {
  type RmwMsg = super::msg::rmw::HeadJointFeedback;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        name: msg.name
          .map(|elem| elem.as_str().into()),
        position: msg.position,
        velocity: msg.velocity,
        effort: msg.effort,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
        name: msg.name
          .iter()
          .map(|elem| elem.as_str().into())
          .collect::<Vec<_>>()
          .try_into()
          .unwrap(),
        position: msg.position,
        velocity: msg.velocity,
        effort: msg.effort,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      name: msg.name
        .map(|elem| elem.to_string()),
      position: msg.position,
      velocity: msg.velocity,
      effort: msg.effort,
    }
  }
}


// Corresponds to teleop_robot_bridge__msg__HeadJointStatus
/// 头部关节状态消息（2个执行器）

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct HeadJointStatus {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,

    /// 关节名称
    pub name: [std::string::String; 2],

    /// 4个关节的状态数组
    pub joint_status: [super::msg::JointStatus; 2],

}



impl Default for HeadJointStatus {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::HeadJointStatus::default())
  }
}

impl rosidl_runtime_rs::Message for HeadJointStatus {
  type RmwMsg = super::msg::rmw::HeadJointStatus;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        name: msg.name
          .map(|elem| elem.as_str().into()),
        joint_status: msg.joint_status
          .map(|elem| super::msg::JointStatus::into_rmw_message(std::borrow::Cow::Owned(elem)).into_owned()),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
        name: msg.name
          .iter()
          .map(|elem| elem.as_str().into())
          .collect::<Vec<_>>()
          .try_into()
          .unwrap(),
        joint_status: msg.joint_status
          .iter()
          .map(|elem| super::msg::JointStatus::into_rmw_message(std::borrow::Cow::Borrowed(elem)).into_owned())
          .collect::<Vec<_>>()
          .try_into()
          .unwrap(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      name: msg.name
        .map(|elem| elem.to_string()),
      joint_status: msg.joint_status
        .map(super::msg::JointStatus::from_rmw_message),
    }
  }
}


// Corresponds to teleop_robot_bridge__msg__HeadMotionCtrl
/// 控制2个电机的使能/失能状态
/// 每个元素对应一个电机（索引0~1），true表示使能，false表示失能,2为true表示全部使能,false表示全部失能

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct HeadMotionCtrl {

    // This member is not documented.
    #[allow(missing_docs)]
    pub enable_states: [bool; 3],

}



impl Default for HeadMotionCtrl {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::HeadMotionCtrl::default())
  }
}

impl rosidl_runtime_rs::Message for HeadMotionCtrl {
  type RmwMsg = super::msg::rmw::HeadMotionCtrl;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        enable_states: msg.enable_states,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        enable_states: msg.enable_states,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      enable_states: msg.enable_states,
    }
  }
}


// Corresponds to teleop_robot_bridge__msg__JointStatus
/// 单个执行器（电机+驱动器）状态

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::JointStatus::default())
  }
}

impl rosidl_runtime_rs::Message for JointStatus {
  type RmwMsg = super::msg::rmw::JointStatus;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        driver_voltage: msg.driver_voltage,
        driver_temperature: msg.driver_temperature,
        driver_state: msg.driver_state,
        motor_temperature: msg.motor_temperature,
        rpm: msg.rpm,
        current: msg.current,
        pulse_count: msg.pulse_count,
        motor_angles: msg.motor_angles,
        motor_speeds: msg.motor_speeds,
        motor_loads: msg.motor_loads,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      driver_voltage: msg.driver_voltage,
      driver_temperature: msg.driver_temperature,
      driver_state: msg.driver_state,
      motor_temperature: msg.motor_temperature,
      rpm: msg.rpm,
      current: msg.current,
      pulse_count: msg.pulse_count,
      motor_angles: msg.motor_angles,
      motor_speeds: msg.motor_speeds,
      motor_loads: msg.motor_loads,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      driver_voltage: msg.driver_voltage,
      driver_temperature: msg.driver_temperature,
      driver_state: msg.driver_state,
      motor_temperature: msg.motor_temperature,
      rpm: msg.rpm,
      current: msg.current,
      pulse_count: msg.pulse_count,
      motor_angles: msg.motor_angles,
      motor_speeds: msg.motor_speeds,
      motor_loads: msg.motor_loads,
    }
  }
}


// Corresponds to teleop_robot_bridge__msg__JoyState
/// 手柄状态消息

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct JoyState {
    /// 手柄数据（使用标准 Joy 消息）
    pub joy: sensor_msgs::msg::Joy,

}



impl Default for JoyState {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::JoyState::default())
  }
}

impl rosidl_runtime_rs::Message for JoyState {
  type RmwMsg = super::msg::rmw::JoyState;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        joy: sensor_msgs::msg::Joy::into_rmw_message(std::borrow::Cow::Owned(msg.joy)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        joy: sensor_msgs::msg::Joy::into_rmw_message(std::borrow::Cow::Borrowed(&msg.joy)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      joy: sensor_msgs::msg::Joy::from_rmw_message(msg.joy),
    }
  }
}


// Corresponds to teleop_robot_bridge__msg__SingleDeviceState
/// 设备健康状态

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SingleDeviceState {

    // This member is not documented.
    #[allow(missing_docs)]
    pub health_status: u8,

    /// 错误域列表
    pub error_domain: Vec<u8>,

    /// --- Operational State -------------------------------------------
    /// Current operational mode of the device, see ModeStatus constants below
    pub operational_mode: u8,

    /// Current power state of the device, see PowerState constants below
    pub power_state: u8,

    /// Current connectivity status of the device, see ConnectivityStatus constants below
    pub connectivity_status: u8,

    /// --- Vendor & Version Info ----------------------------------------
    /// Device manufacturer name, e.g. "Bosch"
    pub manufacturer: std::string::String,

    /// Device model identifier, e.g. "Lidar-XYZ-v2"
    pub model: std::string::String,

    /// Current firmware version, e.g. "1.2.3"
    pub firmware_version: std::string::String,

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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::SingleDeviceState::default())
  }
}

impl rosidl_runtime_rs::Message for SingleDeviceState {
  type RmwMsg = super::msg::rmw::SingleDeviceState;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        health_status: msg.health_status,
        error_domain: msg.error_domain.into(),
        operational_mode: msg.operational_mode,
        power_state: msg.power_state,
        connectivity_status: msg.connectivity_status,
        manufacturer: msg.manufacturer.as_str().into(),
        model: msg.model.as_str().into(),
        firmware_version: msg.firmware_version.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      health_status: msg.health_status,
        error_domain: msg.error_domain.as_slice().into(),
      operational_mode: msg.operational_mode,
      power_state: msg.power_state,
      connectivity_status: msg.connectivity_status,
        manufacturer: msg.manufacturer.as_str().into(),
        model: msg.model.as_str().into(),
        firmware_version: msg.firmware_version.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      health_status: msg.health_status,
      error_domain: msg.error_domain
          .into_iter()
          .collect(),
      operational_mode: msg.operational_mode,
      power_state: msg.power_state,
      connectivity_status: msg.connectivity_status,
      manufacturer: msg.manufacturer.to_string(),
      model: msg.model.to_string(),
      firmware_version: msg.firmware_version.to_string(),
    }
  }
}


// Corresponds to teleop_robot_bridge__msg__SingleGripperMove
/// 单个抓手移动命令

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::SingleGripperMove::default())
  }
}

impl rosidl_runtime_rs::Message for SingleGripperMove {
  type RmwMsg = super::msg::rmw::SingleGripperMove;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        emergency_release: msg.emergency_release,
        emergency_release_dir: msg.emergency_release_dir,
        stop: msg.stop,
        position: msg.position,
        speed: msg.speed,
        force: msg.force,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      emergency_release: msg.emergency_release,
      emergency_release_dir: msg.emergency_release_dir,
      stop: msg.stop,
      position: msg.position,
      speed: msg.speed,
      force: msg.force,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      emergency_release: msg.emergency_release,
      emergency_release_dir: msg.emergency_release_dir,
      stop: msg.stop,
      position: msg.position,
      speed: msg.speed,
      force: msg.force,
    }
  }
}


// Corresponds to teleop_robot_bridge__msg__SingleGripperStatus
/// 单个抓手状态消息

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::SingleGripperStatus::default())
  }
}

impl rosidl_runtime_rs::Message for SingleGripperStatus {
  type RmwMsg = super::msg::rmw::SingleGripperStatus;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        is_ready: msg.is_ready,
        is_reset: msg.is_reset,
        is_moving: msg.is_moving,
        obj_detected: msg.obj_detected,
        fault_status: msg.fault_status,
        position: msg.position,
        requested_position: msg.requested_position,
        current: msg.current,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      is_ready: msg.is_ready,
      is_reset: msg.is_reset,
      is_moving: msg.is_moving,
      obj_detected: msg.obj_detected,
      fault_status: msg.fault_status,
      position: msg.position,
      requested_position: msg.requested_position,
      current: msg.current,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      is_ready: msg.is_ready,
      is_reset: msg.is_reset,
      is_moving: msg.is_moving,
      obj_detected: msg.obj_detected,
      fault_status: msg.fault_status,
      position: msg.position,
      requested_position: msg.requested_position,
      current: msg.current,
    }
  }
}


// Corresponds to teleop_robot_bridge__msg__Temperature
/// 温度传感器消息

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Temperature {
    /// 温度数据（使用标准 Temperature 消息）
    pub temperature: sensor_msgs::msg::Temperature,

}



impl Default for Temperature {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::Temperature::default())
  }
}

impl rosidl_runtime_rs::Message for Temperature {
  type RmwMsg = super::msg::rmw::Temperature;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        temperature: sensor_msgs::msg::Temperature::into_rmw_message(std::borrow::Cow::Owned(msg.temperature)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        temperature: sensor_msgs::msg::Temperature::into_rmw_message(std::borrow::Cow::Borrowed(&msg.temperature)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      temperature: sensor_msgs::msg::Temperature::from_rmw_message(msg.temperature),
    }
  }
}


// Corresponds to teleop_robot_bridge__msg__UpperBodyDeviceState
/// 上半身设备状态消息

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct UpperBodyDeviceState {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,

    /// 单个设备状态
    pub device_state: super::msg::SingleDeviceState,

}



impl Default for UpperBodyDeviceState {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::UpperBodyDeviceState::default())
  }
}

impl rosidl_runtime_rs::Message for UpperBodyDeviceState {
  type RmwMsg = super::msg::rmw::UpperBodyDeviceState;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        device_state: super::msg::SingleDeviceState::into_rmw_message(std::borrow::Cow::Owned(msg.device_state)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
        device_state: super::msg::SingleDeviceState::into_rmw_message(std::borrow::Cow::Borrowed(&msg.device_state)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      device_state: super::msg::SingleDeviceState::from_rmw_message(msg.device_state),
    }
  }
}


// Corresponds to teleop_robot_bridge__msg__WaistJointCommand
/// 腰部3个电机命令消息

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct WaistJointCommand {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,

    /// 关节名称
    pub name: [std::string::String; 3],

    /// 位置
    pub position: [f64; 3],

    /// 速度
    pub velocity: [f64; 3],

    /// 力矩
    pub effort: [f64; 3],

}



impl Default for WaistJointCommand {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::WaistJointCommand::default())
  }
}

impl rosidl_runtime_rs::Message for WaistJointCommand {
  type RmwMsg = super::msg::rmw::WaistJointCommand;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        name: msg.name
          .map(|elem| elem.as_str().into()),
        position: msg.position,
        velocity: msg.velocity,
        effort: msg.effort,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
        name: msg.name
          .iter()
          .map(|elem| elem.as_str().into())
          .collect::<Vec<_>>()
          .try_into()
          .unwrap(),
        position: msg.position,
        velocity: msg.velocity,
        effort: msg.effort,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      name: msg.name
        .map(|elem| elem.to_string()),
      position: msg.position,
      velocity: msg.velocity,
      effort: msg.effort,
    }
  }
}


// Corresponds to teleop_robot_bridge__msg__WaistJointFeedback
/// 腰部3个电机反馈

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct WaistJointFeedback {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,

    /// 关节名称
    pub name: [std::string::String; 3],

    /// 位置
    pub position: [f64; 3],

    /// 速度
    pub velocity: [f64; 3],

    /// 力矩
    pub effort: [f64; 3],

}



impl Default for WaistJointFeedback {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::WaistJointFeedback::default())
  }
}

impl rosidl_runtime_rs::Message for WaistJointFeedback {
  type RmwMsg = super::msg::rmw::WaistJointFeedback;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        name: msg.name
          .map(|elem| elem.as_str().into()),
        position: msg.position,
        velocity: msg.velocity,
        effort: msg.effort,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
        name: msg.name
          .iter()
          .map(|elem| elem.as_str().into())
          .collect::<Vec<_>>()
          .try_into()
          .unwrap(),
        position: msg.position,
        velocity: msg.velocity,
        effort: msg.effort,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      name: msg.name
        .map(|elem| elem.to_string()),
      position: msg.position,
      velocity: msg.velocity,
      effort: msg.effort,
    }
  }
}


// Corresponds to teleop_robot_bridge__msg__WaistJointStatus
/// 腰部关节状态消息（3个执行器）

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct WaistJointStatus {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,

    /// 关节名称
    pub name: [std::string::String; 3],

    /// 4个关节的状态数组
    pub joint_status: [super::msg::JointStatus; 3],

}



impl Default for WaistJointStatus {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::WaistJointStatus::default())
  }
}

impl rosidl_runtime_rs::Message for WaistJointStatus {
  type RmwMsg = super::msg::rmw::WaistJointStatus;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        name: msg.name
          .map(|elem| elem.as_str().into()),
        joint_status: msg.joint_status
          .map(|elem| super::msg::JointStatus::into_rmw_message(std::borrow::Cow::Owned(elem)).into_owned()),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
        name: msg.name
          .iter()
          .map(|elem| elem.as_str().into())
          .collect::<Vec<_>>()
          .try_into()
          .unwrap(),
        joint_status: msg.joint_status
          .iter()
          .map(|elem| super::msg::JointStatus::into_rmw_message(std::borrow::Cow::Borrowed(elem)).into_owned())
          .collect::<Vec<_>>()
          .try_into()
          .unwrap(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      name: msg.name
        .map(|elem| elem.to_string()),
      joint_status: msg.joint_status
        .map(super::msg::JointStatus::from_rmw_message),
    }
  }
}


// Corresponds to teleop_robot_bridge__msg__WaistMotionCtrl
/// 控制3个电机的使能/失能状态
/// 每个元素对应一个电机（索引0~2），true表示使能，false表示失能,3为true表示全部使能,false表示全部失能

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct WaistMotionCtrl {

    // This member is not documented.
    #[allow(missing_docs)]
    pub enable_states: [bool; 4],

}



impl Default for WaistMotionCtrl {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::WaistMotionCtrl::default())
  }
}

impl rosidl_runtime_rs::Message for WaistMotionCtrl {
  type RmwMsg = super::msg::rmw::WaistMotionCtrl;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        enable_states: msg.enable_states,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        enable_states: msg.enable_states,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      enable_states: msg.enable_states,
    }
  }
}


// Corresponds to teleop_robot_bridge__msg__WaistTcpCommand
/// 腰部 TCP 位姿命令消息

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct WaistTcpCommand {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub name: [std::string::String; 1],


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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::WaistTcpCommand::default())
  }
}

impl rosidl_runtime_rs::Message for WaistTcpCommand {
  type RmwMsg = super::msg::rmw::WaistTcpCommand;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        name: msg.name
          .map(|elem| elem.as_str().into()),
        position: msg.position,
        euler: msg.euler,
        quat: msg.quat,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
        name: msg.name
          .iter()
          .map(|elem| elem.as_str().into())
          .collect::<Vec<_>>()
          .try_into()
          .unwrap(),
        position: msg.position,
        euler: msg.euler,
        quat: msg.quat,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      name: msg.name
        .map(|elem| elem.to_string()),
      position: msg.position,
      euler: msg.euler,
      quat: msg.quat,
    }
  }
}



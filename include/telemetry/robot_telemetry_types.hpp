#pragma once

#include <cstdint>
#include <limits>
#include <string>
#include <vector>

namespace trb::telemetry
{

    constexpr uint8_t kRobotTelemetryPayloadVersion = 1;
    constexpr uint8_t kRobotJointTelemetryPayloadVersion = 1;
    constexpr uint16_t kRobotJointTelemetrySchemaId = 2;

    struct RobotTelemetrySnapshot
    {
        uint8_t version{kRobotTelemetryPayloadVersion};
        uint16_t battery_voltage_mv{0xFFFF};
        int16_t battery_current_ma{std::numeric_limits<int16_t>::min()};
        int16_t battery_temperature_deci_c{std::numeric_limits<int16_t>::min()};
        std::string fault_code;
        std::string network_quality;
        std::string model;
        std::string firmware_version;
    };

    struct RobotJointStateSample
    {
        float position_rad{0.0f};
        float velocity_rad_s{0.0f};
        float effort_nm{0.0f};
        bool valid{false};
    };

    struct RobotJointTelemetrySnapshot
    {
        uint8_t version{kRobotJointTelemetryPayloadVersion};
        uint16_t schema_id{kRobotJointTelemetrySchemaId};
        uint64_t sample_timestamp_ms{0};
        std::vector<RobotJointStateSample> joints;
    };

} // namespace trb::telemetry

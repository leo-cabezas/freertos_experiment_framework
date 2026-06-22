#pragma once

#include <array>

namespace Earendil_Experimental {
    static constexpr size_t DATA_LOG_SIZE = 1000;

    struct ExecutionData {
        uint32_t    exec_time_us;
        bool        deadline_missed;
        TickType_t  expected_wake_tick;
        TickType_t  actual_wake_tick;
        TickType_t  wake_tick_difference;
    };

    typedef struct Experimental_SharedData {
        volatile bool                               experiment_ongoing          = false;
        
        bool                                        collect_altimeter_logs      = false;
        uint32_t                                    altimeter_logs_idx          = 0;
        std::array<ExecutionData, DATA_LOG_SIZE>    altimeter_logs;

        bool                                        collect_magnetometer_logs   = false;
        uint32_t                                    magnetometer_logs_idx       = 0;
        std::array<ExecutionData, DATA_LOG_SIZE>    magnetometer_logs;

        bool                                        collect_accelgyro_logs   = false;
        uint32_t                                    accelgyro_logs_idx       = 0;
        std::array<ExecutionData, DATA_LOG_SIZE>    accelgyro_logs;

    } Experimental_SharedData_t;
}
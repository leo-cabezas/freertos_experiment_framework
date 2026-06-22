#pragma once

// FreeRTOS libraries
#include <FreeRTOS.h>
#include <task.h>

namespace Earendil_Experimental {
    typedef struct Experimental_TaskHandles {
        TaskHandle_t task_vExperimentSupervisor;
        TaskHandle_t task_vI2CBusHog;
        TaskHandle_t task_vMemThrash;
    } Experimental_TaskHandles_t;
}
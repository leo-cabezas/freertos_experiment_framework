#pragma once    // To prevent duplicate library imports.

// --- DEPENDENCIES // FreeRTOS-Kernel ---
#include <FreeRTOS.h>           // For pdMS_TO_TICKS(), etc. Needed for task.h, semphr.h, etc.
#include <task.h>               // For vTaskDelay(), etc.
#include <semphr.h>             // For SemaphoreHandle_t, xSemaphoreTake(), xSemaphoreGive(), etc.

// --- DEPENDENCIES // pico-sdk ---
#include <pico/stdlib.h>        // For gpio_init(), gpio_set_dir(), gpio_put(), I/O with printf(), etc.
#include <pico/multicore.h>     // Enable as needed. Not needed at the moment

// --- DEPENDENCIES // EARENDIL LIBRARIES ---
#include <Earendil_TaskHandles.h>
#include <Earendil_SharedData.h>
#include <Earendil_Mutexes.h>

// --- OTHER DEPENDENCIES ---
#include <cmath>
#include <stdio.h>

#define EXPERIMENT_DURATION_MS      30000
#define DELAY_AFTER_EXPERIMENT_MS   3000

namespace Earendil_Experimental {
    // --------------------------------- TASKS ---------------------------------
    extern Earendil::Earendil_TaskHandles_t*    Earendil_Handles;
    extern Earendil::Earendil_SharedData_t*     Earendil_Data;
    extern Earendil::Earendil_Mutexes_t*        Earendil_Mutexes;
    
    void linkSharedStructs(
        Earendil::Earendil_TaskHandles_t*   global_Earendil_Handles,
        Earendil::Earendil_SharedData_t*    global_Earendil_Data,
        Earendil::Earendil_Mutexes_t*       global_Earendil_Mutexes
    );

    void createTasks(void);

    void createTask_vExperimentSupervisor(void);
    void vExperimentSupervisor(void* pvParameters);

    void createTask_vI2CBusHog(void);
    void vI2CBusHog(void* pvParameters);

    void createTask_vMemThrash(void);
    void vMemThrash(void* pvParameters);

    // --------------------------------- UTILS ---------------------------------
    void setup(void);

    void dumpLogs(
        const char* name,
        const std::array<ExecutionData, DATA_LOG_SIZE>& logs,
        size_t idx
    );

}
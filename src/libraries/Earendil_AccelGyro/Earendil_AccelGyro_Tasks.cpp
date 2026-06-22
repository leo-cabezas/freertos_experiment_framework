#include <Earendil_AccelGyro.h> // ATTENTION: Add all library dependencies to this header.

namespace Earendil_AccelGyro {
    Earendil::Earendil_TaskHandles_t*   Earendil_Handles    = nullptr; 
    Earendil::Earendil_SharedData_t*    Earendil_Data       = nullptr;
    Earendil::Earendil_Mutexes_t*       Earendil_Mutexes    = nullptr;

    void linkSharedStructs(
        Earendil::Earendil_TaskHandles_t*   global_Earendil_Handles,
        Earendil::Earendil_SharedData_t*    global_Earendil_Data,
        Earendil::Earendil_Mutexes_t*       global_Earendil_Mutexes
    ){
        Earendil_Handles    = global_Earendil_Handles;
        Earendil_Data       = global_Earendil_Data;
        Earendil_Mutexes    = global_Earendil_Mutexes;
    }
    
    void createTasks(void){    
        createTask_vAccelGyro();
    }

    // =======================================================================================
    // vAccelGyro
    // =======================================================================================

    void createTask_vAccelGyro(void){
        TaskHandle_t* task_handle_ptr = &Earendil_Handles->AccelGyro_Handles.task_vAccelGyro;
        xTaskCreate(
            vAccelGyro,                                     // Task function
            "vAccelGyro",                                   // Task name (for debugging)
            512,                                            // Task stack depth (in words, NOT bytes!)
            NULL,                                           // Task parameters at creation
            2,                                              // Real-time task priority
            task_handle_ptr                                 // Task handle
        );
        vTaskCoreAffinitySet(*task_handle_ptr, 1 << 
            0                                               // Assigned core (options: 0, 1)
        );
    }  

    void vAccelGyro(void* pvParameters){
        (void) pvParameters;
        
        (void)pvParameters;     // Parameters unused.
        
        TickType_t xLastWakeTime = xTaskGetTickCount();
        const TickType_t xFrequency = pdMS_TO_TICKS(PERIOD_VACCELGYRO_MS);
        BaseType_t xWasDelayed;
        
        while (Earendil_Data->Experimental_Data.experiment_ongoing){
            TickType_t expected_wake_tick = xLastWakeTime + xFrequency;
            xWasDelayed = xTaskDelayUntil(&xLastWakeTime, xFrequency);  
            TickType_t actual_wake_tick = xTaskGetTickCount();

            uint64_t start_task_us = time_us_64();

            xSemaphoreTake(Earendil_Mutexes->i2c_mutex, portMAX_DELAY);
            gyroReading();                                              // Task execution
            xSemaphoreGive(Earendil_Mutexes->i2c_mutex);

            uint32_t task_exec_time_us = (uint32_t)(time_us_64() - start_task_us);

            if (Earendil_Data->Experimental_Data.collect_accelgyro_logs){
                auto& log_array     = Earendil_Data->Experimental_Data.accelgyro_logs;
                auto& log_array_idx = Earendil_Data->Experimental_Data.accelgyro_logs_idx;

                if (log_array_idx < Earendil_Experimental::DATA_LOG_SIZE){
                    log_array[log_array_idx].exec_time_us           = task_exec_time_us;
                    log_array[log_array_idx].deadline_missed        = (xWasDelayed == pdFALSE);
                    log_array[log_array_idx].expected_wake_tick     = expected_wake_tick; 
                    log_array[log_array_idx].actual_wake_tick       = actual_wake_tick;
                    log_array[log_array_idx].wake_tick_difference   = actual_wake_tick - expected_wake_tick;
                    log_array_idx++;
                }
            }                      
        }

        vTaskDelete(NULL);
    }

}
#include <Earendil_Experimental.h>  // ATTENTION: Add all library dependencies to this header.

namespace Earendil_Experimental {

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

    void createTasks(){
        createTask_vExperimentSupervisor();
        // createTask_vI2CBusHog();
        createTask_vMemThrash();
    }

    // =======================================================================================
    // vExperimentSupervisor
    // =======================================================================================

    void createTask_vExperimentSupervisor(){
        TaskHandle_t* task_handle_ptr = &Earendil_Handles->Experimental_Handles.task_vExperimentSupervisor;
        xTaskCreate(
            vExperimentSupervisor,                          // Task function
            "vExperimentSupervisor",                        // Task name (for debugging)
            512,                                            // Task stack depth (in words, NOT bytes!)
            NULL,                                           // Task parameters at creation
            30,                                             // Real-time task priority
            task_handle_ptr                                 // Task handle
        );
        vTaskCoreAffinitySet(*task_handle_ptr, 1 << 
            0                                               // Assigned core (options: 0, 1)
        );
    }

    void vExperimentSupervisor(void* pvParameters){
        (void)pvParameters;
        
        Earendil_Data->Experimental_Data.collect_magnetometer_logs  = true; // Enable Earendil_Magnetometer logs.
        Earendil_Data->Experimental_Data.collect_accelgyro_logs     = false; // Enable Earendil_AccelGyro logs.
        Earendil_Data->Experimental_Data.collect_altimeter_logs     = false;  // Enable Earendil_Altimeter logs.
        
        Earendil_Data->Experimental_Data.experiment_ongoing = true;     // Start experiment.
        vTaskDelay(pdMS_TO_TICKS(EXPERIMENT_DURATION_MS));              // Wait for experiment to conclude.

        Earendil_Data->Experimental_Data.experiment_ongoing = false;    // Stop experiment.
        vTaskDelay(pdMS_TO_TICKS(DELAY_AFTER_EXPERIMENT_MS));           // Wait a bit for all tasks to stop.

        if (Earendil_Data->Experimental_Data.collect_magnetometer_logs){
            dumpLogs(
                "magnetometer",
                Earendil_Data->Experimental_Data.magnetometer_logs,
                Earendil_Data->Experimental_Data.magnetometer_logs_idx
            );  // Dump Earendil_Magnetometer logs to USB serial via printf.
        }
        if (Earendil_Data->Experimental_Data.collect_accelgyro_logs){
            dumpLogs(
                "accelgyro",
                Earendil_Data->Experimental_Data.accelgyro_logs,
                Earendil_Data->Experimental_Data.accelgyro_logs_idx
            );  // Dump Earendil_AccelGyro logs to USB serial via printf.
        }
        if (Earendil_Data->Experimental_Data.collect_altimeter_logs){
            dumpLogs(
                "altimeter",
                Earendil_Data->Experimental_Data.altimeter_logs,
                Earendil_Data->Experimental_Data.altimeter_logs_idx
            );  // Dump Earendil_Altimeter logs to USB serial via printf.
        }
        
        vTaskDelete(NULL);
    }

    // =======================================================================================
    // vI2CBusHog
    // =======================================================================================

    void createTask_vI2CBusHog(){
        TaskHandle_t* task_handle_ptr = &Earendil_Handles->Experimental_Handles.task_vI2CBusHog;
        xTaskCreate(
            vI2CBusHog,                                     // Task function
            "vI2CBusHog",                                   // Task name (for debugging)
            512,                                            // Task stack depth (in words, NOT bytes!)
            NULL,                                           // Task parameters at creation
            0,                                              // Real-time task priority
            task_handle_ptr                                 // Task handle
        );
        vTaskCoreAffinitySet(*task_handle_ptr, 1 << 
            1                                               // Assigned core (options: 0, 1)
        );
    }

    void vI2CBusHog(void* pvParameters){
        (void)pvParameters;

        volatile uint32_t x = 0;

        while (1){
            xSemaphoreTake(Earendil_Mutexes->i2c_mutex, portMAX_DELAY);
            // Hold the mutex for a while
            for (int i = 0; i < 400000; i++){
                x += i;
            }
            xSemaphoreGive(Earendil_Mutexes->i2c_mutex);
        }
    }

    // =======================================================================================
    // vMemThrash
    // =======================================================================================

    void createTask_vMemThrash(){
        TaskHandle_t* task_handle_ptr = &Earendil_Handles->Experimental_Handles.task_vMemThrash;
        xTaskCreate(
            vMemThrash,                                     // Task function
            "vMemThrash",                                   // Task name (for debugging)
            512,                                            // Task stack depth (in words, NOT bytes!)
            NULL,                                           // Task parameters at creation
            1,                                              // Real-time task priority
            task_handle_ptr                                 // Task handle
        );
        vTaskCoreAffinitySet(*task_handle_ptr, 1 << 
            1                                               // Assigned core (options: 0, 1)
        );
    }

    void vMemThrash(void* pvParameters){
        (void)pvParameters;
        constexpr uint32_t size = 30050;
        static volatile uint32_t buffer[size];

        while (1){
            for (int i = 0; i < size; i++){
                buffer[i] += i;
            }

            for (int i = size - 1; i >= 0; i--){
                buffer[i] ^= i;
            }
        }
    }
}
#include <Experiment.h>

// ---------------------------------------------- Required by FreeRTOS ----------------------------------------------
void vApplicationTickHook(void) {
    // Debug print (CAREFUL: Printing every tick will flood UART).
}

void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName) {
    (void) pcTaskName;
    puts("ERROR: Stack overflow");
    while(1);
}

// Called if a pvPortMalloc fails
void vApplicationMallocFailedHook(void) {
    puts("ERROR: Malloc failed!\n");
    while(1);
}
// -----------------------------------------------------------------------------------------------------------------

namespace Earendil {
    
    void setup(){
        #ifdef EARENDIL_EXPERIMENTAL_ENABLED
            Earendil_Experimental::setup();
        #endif
        #ifdef EARENDIL_ACCELGYRO_ENABLED       // Defined in Earendil_AccelGyro.cmake, when linked to CMakeLists.txt.
            Earendil_AccelGyro::setup();
        #endif
        #ifdef EARENDIL_ALTIMETER_ENABLED       // Defined in Earendil_Altimeter.cmake, when linked to CMakeLists.txt.
            Earendil_Altimeter::setup();
        #endif
        #ifdef EARENDIL_MAGNETOMETER_ENABLED    // Defined in Earendil_Magnetometer.cmake, when linked to CMakeLists.txt.
            Earendil_Magnetometer::setup();
        #endif
    }

    void createTasks(){
        static Earendil_TaskHandles_t   Earendil_Handles; // MAYBE BETTER AS AN EXTERNED GLOBAL??? Something like Earendil_Radio::Earendil_Handles = Earendil::Earendil_Handles;
        static Earendil_SharedData_t    Earendil_Data;
        
        static Earendil_Mutexes_t       Earendil_Mutexes;
        Earendil_Mutexes.spi_mutex = xSemaphoreCreateMutex();
        Earendil_Mutexes.i2c_mutex = xSemaphoreCreateMutex();

        #ifdef EARENDIL_EXPERIMENTAL_ENABLED
            Earendil_Experimental::linkSharedStructs(
                &Earendil_Handles,
                &Earendil_Data,
                &Earendil_Mutexes
            );
            Earendil_Experimental::createTasks();
        #endif
        #ifdef EARENDIL_ACCELGYRO_ENABLED       // Defined in Earendil_AccelGyro.cmake, when linked to CMakeLists.txt.
            Earendil_AccelGyro::linkSharedStructs(
                &Earendil_Handles,
                &Earendil_Data,
                &Earendil_Mutexes
            );
            Earendil_AccelGyro::createTasks();
        #endif
        #ifdef EARENDIL_ALTIMETER_ENABLED       // Defined in Earendil_Altimeter.cmake, when linked to CMakeLists.txt.
            Earendil_Altimeter::linkSharedStructs(
                &Earendil_Handles,
                &Earendil_Data,
                &Earendil_Mutexes
            );
            Earendil_Altimeter::createTasks();
        #endif
        #ifdef EARENDIL_MAGNETOMETER_ENABLED    // Defined in Earendil_Magnetometer.cmake, when linked to CMakeLists.txt.
            Earendil_Magnetometer::linkSharedStructs(
                &Earendil_Handles,
                &Earendil_Data,
                &Earendil_Mutexes
            );
            Earendil_Magnetometer::createTasks();
        #endif
    }
}

int main() {
    stdio_init_all();

    Earendil::setup();
    Earendil::createTasks();
    
    vTaskStartScheduler();

    while(1); // Must not return from main() in FreeRTOS.
}
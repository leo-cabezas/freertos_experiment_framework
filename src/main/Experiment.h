#pragma once

// FreeRTOS libraries
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
// pico-sdk libraries
#include <pico/stdlib.h>
#include <pico/multicore.h>

#ifdef EARENDIL_ALTIMETER_ENABLED       // Defined in Earendil_Altimeter.cmake, when linked to CMakeLists.txt.
    #include <Earendil_Altimeter.h>
#endif
#ifdef EARENDIL_ACCELGYRO_ENABLED       // Defined in Earendil_AccelGyro.cmake, when linked to CMakeLists.txt.
    #include <Earendil_AccelGyro.h>
#endif
#ifdef EARENDIL_MAGNETOMETER_ENABLED    // Defined in Earendil_Magnetometer.cmake, when linked to CMakeLists.txt.
    #include <Earendil_Magnetometer.h>
#endif
#ifdef EARENDIL_EXPERIMENTAL_ENABLED
    #include <Earendil_Experimental.h>
#endif

#include <Earendil_TaskHandles.h>
#include <Earendil_SharedData.h>
#include <Earendil_Mutexes.h>

namespace Earendil {

    void setup(void);
    void createTasks(void);
    
}


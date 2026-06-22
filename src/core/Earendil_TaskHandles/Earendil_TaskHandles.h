#pragma once

#include <Earendil_Experimental_TaskHandles.h>
#include <Earendil_AccelGyro_TaskHandles.h>
#include <Earendil_Altimeter_TaskHandles.h>
#include <Earendil_Magnetometer_TaskHandles.h>

namespace Earendil {
    typedef struct Earendil_TaskHandles {
        Earendil_Experimental::Experimental_TaskHandles_t   Experimental_Handles;
        Earendil_AccelGyro::AccelGyro_TaskHandles_t         AccelGyro_Handles;
        Earendil_Altimeter::Altimeter_TaskHandles_t         Altimeter_Handles;
        Earendil_Magnetometer::Magnetometer_TaskHandles_t   Magnetometer_Handles;
    } Earendil_TaskHandles_t;
}

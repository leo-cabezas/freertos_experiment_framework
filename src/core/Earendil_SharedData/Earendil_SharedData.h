#pragma once

#include <Earendil_Experimental_SharedData.h>
#include <Earendil_AccelGyro_SharedData.h>
#include <Earendil_Altimeter_SharedData.h>
#include <Earendil_Magnetometer_SharedData.h>

namespace Earendil {
    typedef struct Earendil_SharedData {
        Earendil_Experimental::Experimental_SharedData_t    Experimental_Data;
        Earendil_AccelGyro::AccelGyro_SharedData_t          AccelGyro_Data;
        Earendil_Altimeter::Altimeter_SharedData_t          Altimeter_Data;
        Earendil_Magnetometer::Magnetometer_SharedData_t    Magnetometer_Data;
    } Earendil_SharedData_t;
}
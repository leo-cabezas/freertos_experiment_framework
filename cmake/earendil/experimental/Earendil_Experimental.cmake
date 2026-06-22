# ---------------------------------------------------------------------------------------------------------------
# EARENDIL // SCHEDULABILITY EXPERIMENTS:
# ---> Name: Earendil_Experimental
# ---> Metadata:
#         * 
# ---> Dependencies:
#         *
# ---> Dependency of:
#         * 

include_guard()

add_library(Earendil_Experimental STATIC
        ./src/experimental/Earendil_Experimental/Earendil_Experimental_Tasks.cpp
        ./src/experimental/Earendil_Experimental/Earendil_Experimental_Utils.cpp
)
target_compile_definitions(Earendil_Experimental PUBLIC
        EARENDIL_EXPERIMENTAL_ENABLED           # Compile definition to enable Earendil_GPS within the source code.
) 
target_link_libraries(Earendil_Experimental PUBLIC      # Link all pico-sdk / FreeRTOS-Kernel dependencies.
        FreeRTOS-Kernel
        FreeRTOS-Kernel-Heap4
        pico_stdlib             # Includes hardware_divider, hardware_gpio, hardware_uart, pico_runtime, pico_platform, pico_stdio, pico_time, and pico_util.
)
target_link_libraries(Earendil_Experimental PUBLIC      # Link all non-(pico-sdk / FreeRTOS-Kernel) dependencies.
        # cmake/earendil/core
        Earendil_TaskHandles
        Earendil_SharedData
        Earendil_Mutexes
)
target_include_directories(Earendil_Experimental PUBLIC
        ./src/experimental/Earendil_Experimental
        # Comprehensive header list for documentation purposes:
        # ./src/libraries/Earendil_Experimental.h
)

# ---------------------------------------------------------------------------------------------------------------

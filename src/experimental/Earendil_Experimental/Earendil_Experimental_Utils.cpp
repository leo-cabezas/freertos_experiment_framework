#include <Earendil_Experimental.h>  // ATTENTION: Add all library dependencies to this header.

namespace Earendil_Experimental {

    void setup(){
        ;
    }

    void dumpLogs(
        const char*                                     name,
        const std::array<ExecutionData, DATA_LOG_SIZE>& log_array,
        size_t                                          log_idx
    ){
        printf("%s,index,exec_time_us,deadline_missed,expected_wake_tick,actual_wake_tick,wake_tick_difference\n", name);
        for (size_t i = 0; i < log_idx; i++){
            printf("%s,%zu,%u,%d,%ld,%ld,%ld\n",
                name,
                i,
                log_array[i].exec_time_us,
                log_array[i].deadline_missed,
                (long)log_array[i].expected_wake_tick,
                (long)log_array[i].actual_wake_tick,
                (long)log_array[i].wake_tick_difference
            );
        }
        printf("\n");
    }

}
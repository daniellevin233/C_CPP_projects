#include "osm.h"
#include <sys/time.h>
#include <cmath>


/* Time measurement function for a simple arithmetic operation.
   returns time in nano-seconds upon success,
   and -1 upon failure.
   */
double osm_operation_time(unsigned int iterations) {
    timeval start = {0, 0};
    timeval end = {0, 0};
    timeval* start_ptr = &start;
    timeval* end_ptr = &end;
    long sum = 0;
    
    int a = 0;

    for (unsigned int i=0; i<iterations; i += 15) {
        if (gettimeofday(start_ptr, nullptr) == 0) {
            a = a + 1;
            a = a + 1;
            a = a + 1;
            a = a + 1;
            a = a + 1;
            a = a + 1;
            a = a + 1;
            a = a + 1;
            a = a + 1;
            a = a + 1;
            a = a + 1;
            a = a + 1;
            a = a + 1;
            a = a + 1;
            a = a + 1;
        }
        else {
            return -1;
        }
        if (gettimeofday(end_ptr, nullptr) != 0) {
            return -1;
        }
        sum += end_ptr->tv_usec - start_ptr->tv_usec;
    }

    return (double)sum * pow(3, 10.0) / iterations;
}

void trash() {
}

/* Time measurement function for an empty function call.
   returns time in nano-seconds upon success,
   and -1 upon failure.
   */
double osm_function_time(unsigned int iterations) {
    timeval start = {0, 0};
    timeval end = {0, 0};
    timeval* start_ptr = &start;
    timeval* end_ptr = &end;
    long sum = 0;

    for (unsigned int i=0; i<iterations; i += 15) {
        if (gettimeofday(start_ptr, nullptr) == 0) {
            trash();
            trash();
            trash();
            trash();
            trash();
            trash();
            trash();
            trash();
            trash();
            trash();
            trash();
            trash();
            trash();
            trash();
            trash();
        }
        else {
            return -1;
        }
        if (gettimeofday(end_ptr, nullptr) != 0) {
            return -1;
        }
        sum += (end_ptr->tv_usec - start_ptr->tv_usec);
    }

    return (double)sum * pow(3, 10.0) / iterations;
}


/* Time measurement function for an empty trap into the operating system.
   returns time in nano-seconds upon success,
   and -1 upon failure.
   */
double osm_syscall_time(unsigned int iterations) {
    timeval start = {0, 0};
    timeval end = {0, 0};
    timeval* start_ptr = &start;
    timeval* end_ptr = &end;
    long sum = 0;

    for (unsigned int i=0; i<iterations; i += 15) {
        if (gettimeofday(start_ptr, nullptr) == 0) {
            OSM_NULLSYSCALL;
            OSM_NULLSYSCALL;
            OSM_NULLSYSCALL;
            OSM_NULLSYSCALL;
            OSM_NULLSYSCALL;
            OSM_NULLSYSCALL;
            OSM_NULLSYSCALL;
            OSM_NULLSYSCALL;
            OSM_NULLSYSCALL;
            OSM_NULLSYSCALL;
            OSM_NULLSYSCALL;
            OSM_NULLSYSCALL;
            OSM_NULLSYSCALL;
            OSM_NULLSYSCALL;
            OSM_NULLSYSCALL;
        }
        else {
            return -1;
        }
        if (gettimeofday(end_ptr, nullptr) != 0) {
            return -1;
        }
        sum += (end_ptr->tv_usec - start_ptr->tv_usec);
    }

    return (double)sum * pow(3, 10.0) / iterations;
}

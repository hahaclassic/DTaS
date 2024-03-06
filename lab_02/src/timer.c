#include "timer.h"

int microseconds_now(unsigned long long *time)
{
    struct timeval val;

    if (gettimeofday(&val, NULL) < 0)
    {
        return ERR_TIMER;
    }
    *time = val.tv_sec * 1000000ULL + val.tv_usec;

    //return val.tv_sec * 1000000ULL + val.tv_usec / 1000ULL;
    return STATUS_OK;
}

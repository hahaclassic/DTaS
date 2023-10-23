#include <stdlib.h>
#include "sparse_matrix.h"
#include "std_matrix.h"

#ifndef STATS_T
#define STATS_T

typedef struct stats_t
{
    unsigned long long std_matrix_time;
    unsigned long long sparse_matrix_time;
    int std_matrix_mem;
    int sparse_matrix_mem;
} stats_t;
#endif


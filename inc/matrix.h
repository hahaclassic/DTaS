#include <stdlib.h>
#include "errors.h"

#define MAX_COUNT 1000

#ifndef MATRIX_T
#define MATRIX_T
typedef struct 
{
    double nums[MAX_COUNT][MAX_COUNT];
    size_t rows; // number of rows
    size_t columns; // number of columns
} std_matrix_t;

typedef struct 
{
    double nums[MAX_COUNT * MAX_COUNT];
    double idx[MAX_COUNT * MAX_COUNT];
    double start[MAX];
    size_t rows; // number of rows
    size_t columns; // number of columns
} vec_matrix_t;
#endif

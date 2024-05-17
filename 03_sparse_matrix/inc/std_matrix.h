#include "errors.h"
#include <stdlib.h>
#include <math.h>

#define EPS 1.0e-7

#ifndef STD_MATRIX_T
#define STD_MATRIX_T
typedef struct std_matrix_t
{
    double **ptrs;
    size_t rows; // number of rows
    size_t columns; // number of columns
    size_t n_nz; // number of non-zero elems
} std_matrix_t;
#endif

double **allocate_std_matrix(size_t num_of_rows, size_t num_of_columns);

int set_std_matrix(std_matrix_t *matrix, size_t num_of_rows, size_t num_of_columns);

void free_std_matrix(std_matrix_t *matrix);

#include "matrix.h"
#include <math.h>

#define EPS 1.0e-7

void sum(matrix_t *matrix1, matrix_t *matrix2, matrix_t *result);

void multiply(vec_matrix_t *matrix1, vec_matrix_t *matrix2, vec_matrix_t *result);

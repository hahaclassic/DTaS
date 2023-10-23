#include <stdio.h>
#include "std_matrix.h"
#include "sparse_matrix.h"
#include "errors.h"

void write_sparse_matrix(FILE *file, sparse_matrix_t *matrix);

int write_sparse_matrix_file(char *file_name, sparse_matrix_t *matrix);

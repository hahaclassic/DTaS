#include <stdio.h>
#include "errors.h"
#include "sparse_matrix.h"

#define MAX_SIZE 1000
#ifndef STDIN 
#define STDIN 1
#endif

int get_sizes(FILE *file, size_t *num_of_rows, size_t *num_of_columns);

int get_elements(FILE *stream, sparse_matrix_t *sparse, std_matrix_t *std);

int read_matrix(FILE *file, sparse_matrix_t *sparse, std_matrix_t *std);

int read_matrix_file(char *file_name, sparse_matrix_t *sparse, std_matrix_t *std);

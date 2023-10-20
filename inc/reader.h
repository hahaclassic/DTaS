#include <stdio.h>
#include <stdlib.h>
#include "errors.h"
#include "matrix.h"

int get_sizes(FILE *file, size_t *num_of_rows, size_t *num_of_columns);

int get_elements(FILE *file, matrix_t *matrix);

int read_matrix(char *file_name, matrix_t *matrix);

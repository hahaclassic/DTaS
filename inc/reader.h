#include <stdio.h>
#include "errors.h"
#include "std_matrix.h"

int get_sizes(FILE *file, size_t *num_of_rows, size_t *num_of_columns);

int get_elements(FILE *file, std_matrix_t *matrix);

int read_matrix(FILE *file, std_matrix_t *matrix);

int read_matrix_file(char *file_name, std_matrix_t *matrix);

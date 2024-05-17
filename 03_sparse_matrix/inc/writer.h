#include <stdio.h>
#include "std_matrix.h"
#include "sparse_matrix.h"
#include "errors.h"
#include "timer.h"
#include "stats.h"

void write_sparse_matrix(FILE *file, sparse_matrix_t *matrix);

int write_sparse_matrix_file(char *file_name, sparse_matrix_t *matrix);

bool print_matrix();

void print_stats(stats_t *stats, sparse_matrix_t *csr, sparse_matrix_t *csc);

void show_menu();

int write_std_matrix(FILE *file, std_matrix_t *matrix);
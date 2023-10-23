#include "errors.h"
#include <stdlib.h>
#include "std_matrix.h"
#include <stdbool.h>


/*
    Если матрица представлена в виде:
        - nums: ненулевые элементы
        - idx: индексы столбцов, в которых находятся соответствующие элементы
        - start: индексы элементов в nums, с которых начинаются строки
    То длина массива start будет определяться переменной rows

    Если матрица представлена в виде:
        - nums: ненулевые элементы
        - idx: индексы строк, в которых находятся соответствующие элементы
        - start: индексы элементов в nums, с которых начинаются столбцы
    То длина массива start будет определяться переменной columns
*/

#define CSR false
#define CSC true

#define EPS 1.0e-7

#ifndef SPARSE_MATRIX_T
#define SPARSE_MATRIX_T
typedef struct sparse_matrix_t
{
    double *nums;
    size_t *idx;
    size_t *start; // Длина массива start совпадает с кол-вом строк или кол-вом столбцов.
    size_t n_rows; // number of rows
    size_t n_cols; // number of columns
    size_t n_nz; // Количество ненулевых элементов
    bool type;
} sparse_matrix_t;
#endif

int set_sparse_matrix(sparse_matrix_t *matrix, size_t n_rows, size_t n_cols, size_t n_nz, bool type);

void free_sparse_matrix(sparse_matrix_t *matrix);

void init_sparse_matrix(sparse_matrix_t *dest, std_matrix_t *src);

size_t max(size_t a, size_t b);

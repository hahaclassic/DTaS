#include "std_matrix.h"


double **allocate_std_matrix(size_t num_of_rows, size_t num_of_columns)
{
    double **ptrs = NULL, *data = NULL;

    ptrs = malloc(num_of_rows * sizeof(double*));
    if (!ptrs)
    {
        return NULL;
    }

    data = malloc(num_of_rows * num_of_columns * sizeof(double));
    if (!data)
    {
        free(ptrs);
        return NULL;
    }

    for (size_t i = 0; i < num_of_rows; i++)
    {
        ptrs[i] = data + i * num_of_columns;
    }
    
    return ptrs;
}

int set_std_matrix(std_matrix_t *matrix, size_t num_of_rows, size_t num_of_columns)
{
    if (num_of_rows < 1 || num_of_columns < 1)
    {
        return ERR_INCORRECT_MATRIX_SIZES;
    }

    matrix->rows = num_of_rows;
    matrix->columns = num_of_columns;
    matrix->ptrs = allocate_std_matrix(num_of_rows, num_of_columns);

    if (!matrix->ptrs)
    {
        return ERR_MEMORY_ALLOCATION;
    }

    return STATUS_OK;
}

void free_std_matrix(std_matrix_t *matrix)
{
    // Находим наименьший указатель - начало области памяти, выделенной для элементов матрицы.

    double *min = matrix->ptrs[0];
    for (size_t i = 1; i < matrix->rows; i++)
    {
        if (matrix->ptrs[i] < min)
        {
            min = matrix->ptrs[i];
        }
    }

    free(min);
    free(matrix->ptrs);
}

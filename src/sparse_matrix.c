#include "sparse_matrix.h"


int set_sparse_matrix(sparse_matrix_t *matrix, size_t n_rows, size_t n_cols, size_t n_nz, bool type)
{
    if (n_rows < 1 || n_cols < 1)
    {
        return ERR_INCORRECT_MATRIX_SIZES;
    }

    matrix->n_rows = n_rows;
    matrix->n_cols = n_cols;
    matrix->n_nz = n_nz;
    matrix->type = type;

    matrix->nums = NULL;
    matrix->nums = malloc(matrix->n_nz * sizeof(double));
    if (!matrix->nums)
    {
        return ERR_MEMORY_ALLOCATION;
    }

    matrix->idx = NULL;
    matrix->idx = malloc(matrix->n_nz * sizeof(size_t));
    if (!matrix->idx)
    {
        free(matrix->nums);
        return ERR_MEMORY_ALLOCATION;
    }

    matrix->start = NULL;
    
    if (type == CSR)
    {
        matrix->start = malloc((n_rows + 1) * sizeof(size_t));
    }
    else
    {
        matrix->start = calloc(n_cols + 1, sizeof(size_t));
    }
   
    if (!matrix->start)
    {
        free(matrix->nums);
        free(matrix->idx);
        return ERR_MEMORY_ALLOCATION;
    }

    if (type == CSR)
    {
        matrix->start[n_rows] = n_nz;
    }
    else
    {
        matrix->start[n_cols] = n_nz;
    }


    return STATUS_OK;
}

void free_sparse_matrix(sparse_matrix_t *matrix)
{
    free(matrix->nums);
    free(matrix->idx);
    free(matrix->start);
}


void init_sparse_matrix(sparse_matrix_t *dest, std_matrix_t *src)
{
    size_t n = src->rows, m = src->columns;
    if (dest->type == CSC)
    {
        n = src->columns;
        m = src->rows;
    }

    size_t k = 0;
    dest->start[0] = 0;
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            if (dest->type == CSR && (fabs(src->ptrs[i][j]) > EPS))
            {
                dest->nums[k] = src->ptrs[i][j];
                dest->idx[k] = j;
                k++;
            }
            else if (dest->type == CSC && fabs(src->ptrs[j][i]) > EPS)
            {
                dest->nums[k] = src->ptrs[j][i];
                dest->idx[k] = j;
                k++;
            }
        }
        dest->start[i + 1] = k;
    }
}

size_t max(size_t a, size_t b)
{
    if (a > b)
    {
        return a;
    }
    return b;
}

#include "multiplication.h"


void std_matrix_multiply(std_matrix_t *matrix1, std_matrix_t *matrix2, std_matrix_t *result)
{
    for (size_t i = 0; i < matrix1->rows; i++)
    {
        for (size_t j = 0; j < matrix2->columns; j++)
        {
            result->ptrs[i][j] = 0;
            for (size_t k = 0; k < matrix1->columns; k++)
            {
                result->ptrs[i][j] += matrix1->ptrs[i][k] * matrix2->ptrs[k][j];
            }
        }
    }
}

double get_num(size_t row_start, size_t row_end, size_t col_start, size_t col_end, 
    sparse_matrix_t *m1, sparse_matrix_t *m2)
{
    double result = 0;
   
    for (size_t k = row_start; k < row_end; k++)
    {
        for (size_t col_idx = col_start; col_idx < col_end; col_idx++)
        {
            if (m1->idx[k] == m2->idx[col_idx])
            {
                //printf("%lf %lf %zu\n", m1->nums[k], m2->nums[col_idx], col_idx);
                result += m1->nums[k] * m2->nums[col_idx];
                break;
            }
        }
    }

    return result;
}

void sparse_matrix_multiply(sparse_matrix_t *matrix1, sparse_matrix_t *matrix2, sparse_matrix_t *result)
{
    size_t row_start, row_end, col_start, col_end;
    
    size_t n_nz = 0;
    result->start[0] = 0;

    for (size_t i = 0; i < matrix1->n_rows; i++)
    {
        row_start = matrix1->start[i];
        row_end = matrix1->start[i + 1];

        for (size_t j = 0; j < matrix2->n_cols; j++)
        {
            col_start = matrix2->start[j];
            col_end = matrix2->start[j + 1];
            
            result->nums[n_nz] = get_num(row_start, row_end, col_start, col_end, matrix1, matrix2);

            if (fabs(result->nums[n_nz]) > EPS) 
            {
                result->idx[n_nz] = j;
                n_nz++;
            }
        }
        result->start[i + 1] = n_nz;
    }

    result->n_nz = n_nz;
}

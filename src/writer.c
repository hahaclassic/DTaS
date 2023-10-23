#include "writer.h"

int write_std_matrix(FILE *file, std_matrix_t *matrix)
{
    //int input;
    fprintf(file, "%zu %zu\n", matrix->rows, matrix->columns);

    for (size_t i = 0; i < matrix->rows; i++)
    {
        for (size_t j = 0; j < matrix->columns; j++)
        {
            fprintf(file, "%lf ", matrix->ptrs[i][j]);
        }
        fprintf(file, "\n");
    }

    return STATUS_OK;
}


int write_std_matrix_file(char *file_name, std_matrix_t *matrix)
{
    FILE *file = fopen(file_name, "w");
    if (file == NULL)
    {
        return ERR_FILE_OPEN;
    }

    int err = write_std_matrix(file, matrix);
    fclose(file);
    if (err)
    {
        return err;
    }

    return STATUS_OK;
}

void write_sparse_matrix(FILE *file, sparse_matrix_t *matrix)
{
    fprintf(file, "%zu %zu\n", matrix->n_rows, matrix->n_cols);

    size_t k = 0;
    for (size_t i = 0; i < matrix->n_rows; i++)
    {
        for (size_t j = 0; j < matrix->n_cols; j++)
        {
            if (matrix->idx[k] == j && k >= matrix->start[i] && k < matrix->start[i + 1])
            {
                fprintf(file, "%lf ", matrix->nums[k]);
                k++;
            }
            else
            {
                fprintf(file, "%lf ", 0.0);
            }
        }
        fprintf(file, "\n");
    }
}

int write_sparse_matrix_file(char *file_name, sparse_matrix_t *matrix)
{
    FILE *file = fopen(file_name, "w");
    if (file == NULL)
    {
        return ERR_FILE_OPEN;
    }

    write_sparse_matrix(file, matrix);
    fclose(file);

    return STATUS_OK;
}

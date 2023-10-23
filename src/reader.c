#include "reader.h"

int get_sizes(FILE *file, size_t *num_of_rows, size_t *num_of_columns) 
{
    int input, n, m;
    input = fscanf(file, "%d %d", &n, &m);
    if (input != 2)
    {
        return ERR_READ_DATA;
    }
    if (n < 1 || m < 1)
    {
        return ERR_INCORRECT_MATRIX_SIZES;
    }

    *num_of_rows = (size_t) n;
    *num_of_columns = (size_t) m;

    return STATUS_OK;
}


int get_elements(FILE *file, std_matrix_t *matrix)
{
    int input;
    size_t count = 0;
    matrix->n_nz = 0;

    for (size_t i = 0; i < matrix->rows; i++)
    {
        for (size_t j = 0; j < matrix->columns; j++)
        {
            input = fscanf(file, "%lf", &matrix->ptrs[i][j]);
            if (input != 1)
            {
                break;
            } 
            if (fabs(matrix->ptrs[i][j]) > EPS)
            {
                matrix->n_nz++;
            }
            count++;
        }
    }

    if (!feof(file) && count < matrix->rows * matrix->columns)
    {
        return ERR_READ_DATA;
    } 
    else if (count < matrix->rows * matrix->columns)
    {
        return ERR_NOT_ENOUGH_ELEMENTS;
    }

    return STATUS_OK;
}

int read_matrix(FILE *file, std_matrix_t *matrix)
{
    if (file == stdin)
    {
        printf("Введите размеры матрицы: ");
    }
   
    int err = get_sizes(file, &matrix->rows, &matrix->columns);
    if (err)
    {
        return err;
    }

    matrix->ptrs = allocate_std_matrix(matrix->rows, matrix->columns);
    if (!matrix->ptrs)
    {
        return ERR_MEMORY_ALLOCATION;
    }

    if (file == stdin)
    {
        printf("Введите элементы матрицы %zu на %zu: \n", matrix->rows, matrix->columns);
    }
    err = get_elements(file, matrix);

    if (err)
    {   
        free_std_matrix(matrix);
        return err;
    }

    return STATUS_OK;
}

int read_matrix_file(char *file_name, std_matrix_t *matrix)
{
    int err;
    FILE *file = fopen(file_name, "r");
    if (!file)
    {
        return ERR_FILE_OPEN;
    }

    err = read_matrix(file, matrix);
    fclose(file);
    if (err)
    {
        return err;
    }

    return STATUS_OK;
}

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


int get_elements(FILE *file, matrix_t *matrix)
{
    int input;
    size_t count = 0;

    for (size_t i = 0; i < matrix->rows; i++)
    {
        for (size_t j = 0; j < matrix->columns; j++)
        {
            input = fscanf(file, "%lf", &matrix->ptrs[i][j]);
            if (input != 1)
            {
                break;
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

    double check_eof;
    if (!feof(file) && fscanf(file, "%lf", &check_eof) == 1)
    {
        return ERR_TOO_MANY_ELEMENTS;
    } 

    return STATUS_OK;
}


int read_matrix(char *file_name, matrix_t *matrix)
{
    int err;
    FILE *file = fopen(file_name, "r");
    if (!file)
    {
        return ERR_FILE_OPEN;
    }

    err = get_sizes(file, &matrix->rows, &matrix->columns);
    if (err)
    {
        fclose(file);
        return err;
    }

    matrix->ptrs = allocate_matrix(matrix->rows, matrix->columns);
    if (!matrix->ptrs)
    {
        fclose(file);
        return ERR_MEMORY_ALLOCATION;
    }

    err = get_elements(file, matrix);
    fclose(file);

    if (err)
    {   
        free_matrix(matrix);
        return err;
    }

    return STATUS_OK;
}

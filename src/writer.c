#include "writer.h"

int write_data(char *file_name, matrix_t *matrix)
{
    FILE *file = fopen(file_name, "w");
    if (file == NULL)
    {
        return ERR_FILE_OPEN;
    }

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

    fclose(file);

    return STATUS_OK;
}

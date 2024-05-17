#include "reader.h"

error_t read_matrix(FILE *file, adjacency_matrix_t *matrix)
{
    int num_of_vertices;
    int input;

    input = fscanf(file, "%d\n", &num_of_vertices);
    if (input != 1)
    {
        return ERR_READ_DATA;
    }
    if (num_of_vertices <= 0 || num_of_vertices > MAX_NUM_OF_VERTICES)
    {
        return ERR_INCORRECT_NUM_OF_VERTICES;
    }

    matrix->num_of_vertices = (size_t) num_of_vertices;

    for (int i = 0; i < num_of_vertices; i++)
    {   
        for (int j = 0; j < num_of_vertices; j++)
        {
            input = fscanf(file, "%d", &matrix->dist[i][j]);
            if (input != 1)
            {
                return ERR_READ_DATA;
            }

            if (matrix->dist[i][j] < 0 || matrix->dist[i][j] > MAX_DIST)
            {
                return ERR_INVALID_DATA;
            }
        }
    }

    return STATUS_OK;
}

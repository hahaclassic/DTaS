#include "writer.h"

void export_to_dot(char *file_name, adjacency_matrix_t *matrix)
{
    FILE *file = fopen(file_name, "w");
    if (file == NULL)
    {
        return;
    }

    fprintf(file, "digraph d {\n");
    for (size_t i = 0; i < matrix->num_of_vertices; i++)
    {
        fprintf(file, "%zu;\n", i);
    }

    for (size_t i = 0; i < matrix->num_of_vertices; i++)
    {
        for (size_t j = 0; j < matrix->num_of_vertices; j++)
        {
            if (matrix->dist[i][j] != 0)
            {
                fprintf(file, "%zu -> %zu [label=\"%d\"];\n", i, j, matrix->dist[i][j]);
            }
        }
    }

    fprintf(file, "}\n");
    fclose(file);

    char cmd[50] = "dot -Tpng -o ";
    char file_png[50];

    strncpy(file_png, file_name, strlen(file_name) - 4);
    file_png[strlen(file_name) - 4] = '\0';
    strcat(file_png, ".png ");

    strcat(cmd, file_png);
    strcat(cmd, file_name);

    system(cmd);
}

void print_distances(int dist[], size_t len, size_t src)
{
    printf("\nРасстояние от исходной вершины \033[36m%zu\033[0m:\n", src);
    printf("-----------------------------------------------------------------------------------------\n");
    for (size_t i = 0; i < len; i++)
    {
        if (dist[i] != INT_MAX)
        {
            printf("До вершины \033[36m%zu\033[0m: %d\n", i, dist[i]);
        }
        else
        {
            printf("До вершины \033[36m%zu\033[0m: -\n", i);
        }
    }
    printf("-----------------------------------------------------------------------------------------\n");
}

void print_possible_paths(int dist[], size_t len, size_t src, int maximum_allowed)
{
    printf("\nВершины, до которых можно добраться из исходной вершины \033[36m%zu\033[0m " \
    "по пути не длиннее %d:\n", src, maximum_allowed);
    printf("-----------------------------------------------------------------------------------------\n");

    bool is_exist = false;
    for (size_t i = 0; i < len; i++)
    {
        if (dist[i] <= maximum_allowed)
        {
            printf("Вершина \033[36m%zu\033[0m (Расстояние %d)\n", i, dist[i]);
            is_exist = true;
        }
    }
    if (!is_exist) 
    {
        printf("Нет ни одной вершины, путь до которой не превышает указанную длину.\n");
    }
    printf("-----------------------------------------------------------------------------------------\n");
}

#include "operations.h"

void menu()
{
    fprintf(stdout, MENU);
}

operation_t choose_operation()
{
    int operation;
    
    while (true)
    {
        menu();
        fprintf(stdout, ENTER_OPERATION);
        __fpurge(stdin);
   
        int input = fscanf(stdin, "%d", &operation);

        if (input == 1 && operation >= 0 && operation <= EFFICIENCY_OF_THE_ALGORITHM)
        {
            break;
        }
    
        err_message(ERR_INVALID_OPERATION);
    }

    return operation;
}


error_t user_find_min_distance(adjacency_matrix_t *matrix)
{
    int input;
    int src_vertice;

    printf(ENTER_VERTICE, matrix->num_of_vertices - 1);

    input = scanf("%d", &src_vertice);
    if (input != 1)
    {
        return ERR_READ_DATA;
    }   
    if (src_vertice < 0 || (size_t) src_vertice >= matrix->num_of_vertices)
    {
        return ERR_INVALID_DATA;
    }

    int dist[MAX_NUM_OF_VERTICES];
    dijkstra(matrix, (size_t) src_vertice, dist);
    
    print_distances(dist, matrix->num_of_vertices, src_vertice);

    return STATUS_OK;
}

error_t user_find_vertices(adjacency_matrix_t *matrix)
{
    int input;
    int src_vertice, maximum_allowed;

    printf(ENTER_VERTICE, matrix->num_of_vertices - 1);

    input = scanf("%d", &src_vertice);
    if (input != 1)
    {
        return ERR_READ_DATA;
    }   
    if (src_vertice < 0 || (size_t) src_vertice >= matrix->num_of_vertices)
    {
        return ERR_INVALID_DATA;
    }
    printf(ENTER_DIST);
    input = scanf("%d", &maximum_allowed);
    if (input != 1)
    {
        return ERR_READ_DATA;
    }   
    if (maximum_allowed < 0)
    {
        return ERR_INVALID_DATA;
    }

    int dist[MAX_NUM_OF_VERTICES];
    dijkstra(matrix, (size_t) src_vertice, dist);
    
    print_possible_paths(dist, matrix->num_of_vertices, src_vertice, maximum_allowed);

    return STATUS_OK;
}


error_t measure_time(adjacency_matrix_t *matrix)
{
    int num_of_mesures;
    int input;

    printf("Введите количество замеров: ");
    input = scanf("%d", &num_of_mesures);
    if (input != 1)
    {
        return ERR_READ_DATA;
    }
    if (num_of_mesures < 1 || num_of_mesures > MAX_NUM_OF_MEASURES)
    {
        return ERR_INVALID_DATA;
    }

    double avg_time = 0; 

    unsigned long long start, end;
    int dist[MAX_NUM_OF_VERTICES];

    for (int i = 0; i < num_of_mesures; i++)
    {
        for (size_t j = 0; j < matrix->num_of_vertices; j++)
        {
            microseconds_now(&start);
            dijkstra(matrix, j, dist);
            microseconds_now(&end);
            avg_time += (double) (end - start);
        }
    }
    
    avg_time /= (double) (num_of_mesures * matrix->num_of_vertices);
    size_t memory = sizeof(int) * matrix->num_of_vertices * matrix->num_of_vertices;
    printf(STATISTICS, avg_time, memory, sizeof(int) * matrix->num_of_vertices * 2);

    return STATUS_OK;
}

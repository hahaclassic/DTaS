#include "graph.h"
 
int minDistance(int dist[], bool sptSet[], size_t len)
{
    // Initialize min value
    int min = INT_MAX, min_index;
 
    for (size_t v = 0; v < len; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
 
    return min_index;
}

void dijkstra(adjacency_matrix_t *matrix, size_t src, int dist[])
{
    bool sptSet[MAX_NUM_OF_VERTICES];
   
    for (size_t i = 0; i < matrix->num_of_vertices; i++)
        dist[i] = INT_MAX, sptSet[i] = false;
 
    dist[src] = 0;
 
    for (size_t count = 0; count < matrix->num_of_vertices - 1; count++) {

        int u = minDistance(dist, sptSet, matrix->num_of_vertices);
        sptSet[u] = true;

        for (size_t v = 0; v < matrix->num_of_vertices; v++)
        {
            if (!sptSet[v] && matrix->dist[u][v] && dist[u] != INT_MAX
                && dist[u] + matrix->dist[u][v] < dist[v])
            {
                dist[v] = dist[u] + matrix->dist[u][v];
            }
        }
    }
}

#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <stddef.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_NUM_OF_VERTICES 1000
#define MAX_DIST 1000000


typedef struct adjacency_matrix_t adjacency_matrix_t;

struct adjacency_matrix_t
{
    int dist[MAX_NUM_OF_VERTICES][MAX_NUM_OF_VERTICES];
    size_t num_of_vertices;
};

void dijkstra(adjacency_matrix_t *matrix, size_t src, int dist[]);


#endif 

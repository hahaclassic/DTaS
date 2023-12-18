#ifndef __WRITER_H__
#define __WRITER_H__

#include <stdio.h>
#include <string.h>
#include "graph.h"
#include <stdlib.h>
#include <limits.h>

#define STATISTICS  "\n=========================================================================================\n" \
                    "|                            Эффективность алгоритма Дейкстры                           |\n" \
                    "-----------------------------------------------------------------------------------------\n" \
                    "|      Время, мкс      |   Память под матрицу, байты   |  Дополнительная память, байты  |\n" \
                    "|---------------------------------------------------------------------------------------|\n" \
                    "|      %-15lf |             %-17zu |             %-18zu |\n" \
                    "=========================================================================================\n" 

#define GRAPH_DOT_FILE "./out/graph.dot"

void export_to_dot(char *file_name, adjacency_matrix_t *matrix);

void print_distances(int dist[], size_t len, size_t src);

void print_possible_paths(int dist[], size_t len, size_t src, int maximum_allowed);

#endif

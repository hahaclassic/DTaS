#ifndef __OPERATIONS_H__
#define __OPERATIONS_H__

#include <stdio.h>
#include "errors.h"
#include "timer.h"
#include "writer.h"
#include "reader.h"
#include <stdbool.h>
#include <stdio_ext.h>

#define MENU "\n=========================================================================================\n" \
             "|  Нахождение всех вершин, до которых можно добраться по пути не длиннее введенного А.  |\n" \
             "-----------------------------------------------------------------------------------------\n" \
             "| Операции                                                                              |\n" \
             "|---------------------------------------------------------------------------------------|\n" \
             "| 1. Найти кратчайшие пути от выбранной вершины до всех остальных.                      |\n" \
             "| 2. Найти все вершины, до которых можно добраться по пути не длинее А.                 |\n" \
             "| 3. Создать изображение графа                                                          |\n" \
             "| 4. Эффективность алгоритма Дейкстры                                                   |\n" \
             "|                                                                                       |\n" \
             "| 0. Выход из программы.                                                                |\n" \
             "-----------------------------------------------------------------------------------------\n" \


#define ENTER_OPERATION "\nВведите номер операции: "

#define ENTER_VERTICE "\nВведите номер вершины от 0 до %zu: "

#define ENTER_DIST "\nВведите максимальное допустимое расстояние: "

#define MAX_NUM_OF_MEASURES 1000000

typedef enum _operation
{
    /// Конец работы программы.
    END = 0,

    MIN_DISTANCE,

    FIND_VERTICES, 

    CREATE_PNG_GRAPH,

    EFFICIENCY_OF_THE_ALGORITHM,
    
} operation_t;

void menu();

operation_t choose_operation();

error_t measure_time(adjacency_matrix_t *matrix);

error_t user_find_vertices(adjacency_matrix_t *matrix);

error_t user_find_min_distance(adjacency_matrix_t *matrix);

#endif

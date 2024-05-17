#include "writer.h"

void print_statistics(size_t arr_time, size_t arr_mem, size_t list_time, size_t list_mem)
{
    printf(STATISTICS, arr_mem, list_mem, arr_time, list_time);
}

void print_message(char *str)
{
    printf("%s", str);
}

void print_result(int result)
{
    if (result)
    {
        print_message(RESULT_TRUE);
    }
    else
    {
        print_message(RESULT_FALSE);
    }
}

void print_free_nodes(stats_t *stats)
{
    printf("\nСвободные области: ");
    for (size_t i = 0; i < stats->n_nodes; i++)
    {
        printf("%p ", (void*) stats->free_nodes[i]);
    }
    printf("\n");
}

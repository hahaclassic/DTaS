#include "stats.h"

void init_stats(stats_t *stats, int operation)
{
    stats->mode = operation;
    stats->curr = 0;
    stats->max = 0;
    stats->n_nodes = 0;
}

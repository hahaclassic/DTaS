#include "stats.h"

void init_avg_stats(avg_search_stats_t *stats)
{
    stats->open_hash_table_search_time = 0;
    stats->open_hash_table_count = 0;

    stats->closed_hash_table_search_time = 0;
    stats->closed_hash_table_count = 0;

    stats->tree_search_time = 0;
    stats->tree_count = 0;

    stats->balanced_tree_search_time = 0;
    stats->balanced_tree_count = 0;
}

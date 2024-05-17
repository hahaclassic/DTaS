#ifndef __STATS_H__
#define __STATS_H__

#include <stddef.h>

typedef struct search_stats_t search_stats_t;

struct search_stats_t 
{
    unsigned long long open_hash_table_search_time;
    unsigned long long closed_hash_table_search_time;
    unsigned long long tree_search_time;
    unsigned long long balanced_tree_search_time;
    size_t open_hash_table_count; // number of comparisons
    size_t closed_hash_table_count;
    size_t tree_count;
    size_t balanced_tree_count;
};

typedef struct avg_search_stats_t avg_search_stats_t;

struct avg_search_stats_t 
{
    double open_hash_table_search_time;
    double closed_hash_table_search_time;
    double tree_search_time;
    double balanced_tree_search_time;
    double open_hash_table_count; // number of comparisons
    double closed_hash_table_count;
    double tree_count;
    double balanced_tree_count;
};

typedef struct memory_stats_t memory_stats_t;

struct memory_stats_t
{
    size_t len;
    size_t open_hash_table_size;
    size_t closed_hash_table_size;
    size_t tree_size;
    size_t balanced_tree_size;
    size_t open_hash_table_memory;
    size_t closed_hash_table_memory;
    size_t tree_memory;
    size_t balanced_tree_memory;
};

void init_avg_stats(avg_search_stats_t *stats);

#endif

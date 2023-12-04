#ifndef __TYPES_H__
#define __TYPES_H__

#include <stdlib.h>
#include "consts.h"

typedef struct time_range
{
    double min;
    double max;
} time_range_t;

typedef struct ranges_t 
{
    time_range_t t1;
    time_range_t t2;
    time_range_t t3;
    time_range_t t4;
} ranges_t;

typedef struct parameters
{
    void* p_in;
    void* p_out;
    void* low;
    void* up;
    int max_num;
    int count_request;
    int sum_size;
    int curr_size;
    int out_request;
    int in_request;
} parameters_t;


typedef struct node node_t;

struct node
{
    char data;
    node_t *next;
};

typedef struct stats
{
    node_t *freed_memory[MAX_LEN];
    node_t *used_memory[MAX_LEN];
    int count_used;
    int count_freed; 
    int count_reused;
} stats_t;



void param_init(parameters_t *param);
void param_add(parameters_t *param);
void param_delete(parameters_t *param);

void init_array(parameters_t *param, void *q);

double rand_time(time_range_t *t);

int queue_is_empty(parameters_t *param);

#endif 

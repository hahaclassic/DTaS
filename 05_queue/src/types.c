#include "types.h"

void param_init(parameters_t *param)
{
    param->max_num = MAX_LEN;
    param->p_in = NULL;
    param->p_out = NULL;
    param->out_request = 0;
    param->sum_size = 0;
    param->count_request = 0;
    param->curr_size = 0;
    param->in_request = 0;
}

void init_array(parameters_t *param, void *q)
{
    param_init(param);
    param->up = (int *) q + param->max_num;
    param->low = q;
    param->p_in = q;
    param->p_out = q;
}

double rand_time(time_range_t *t)
{
    return (t->max - t->min) * (rand() / (double) RAND_MAX) + t->min;
}

// 1 if empty
int queue_is_empty(parameters_t *param)
{
    return ((param->p_in == param->p_out) && (*((char*) param->p_in) == 0));
}

void param_add(parameters_t *param)
{
    param->curr_size++;
    param->sum_size += param->curr_size;
    param->count_request++;
    param->in_request++;
}

void param_delete(parameters_t *param)
{
    param->curr_size--;
    param->sum_size += param->curr_size;
    param->count_request++;
    param->out_request++;
}

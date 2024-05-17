#include "parentheses.h"

size_t max(size_t a, size_t b)
{
    if (a > b)
    {
        return a;
    }
    return b;
}

bool match(char a, char b)
{
    if ((a == '(' && b == ')') || (a == '{' && b == '}') || (a == '[' && b == ']')) 
    {
        return true;
    }

    return false;
}

int is_correct(char *str, stack_t *stack, bool *ok, stats_t *stats)
{
    int err;

    if (stats->mode == ARR_STACK_INFO || stats->mode == LIST_STACK_INFO)
    {   
        stack->show(stack->base);
    }

    for (size_t i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == '(' || str[i] == '{' || str[i] == '[')
        {
            err = stack->add(stack->base, str[i]);
            if (err)
            {
                return err;
            }
            if (stats->mode == STATS)
            {
                stats->curr++;
                stats->max = max(stats->curr, stats->max);
            }
        }
        else if (match(stack->get_top(stack->base), str[i]))
        {
            if (stats->mode == LIST_STACK_INFO)
            { 
                stats->free_nodes[stats->n_nodes] = (((list_stack_t*) stack->base)->top);
                stats->n_nodes++;
            }
            if (stats->mode == STATS)
            {
                stats->curr--;
            }
            stack->delete(stack->base);
        }
        else
        {
            *ok = false;
            return STATUS_OK;
        }

        if (stats->mode == ARR_STACK_INFO || stats->mode == LIST_STACK_INFO)
        {   
            stack->show(stack->base);
        }
    }

    *ok = stack->is_empty(stack->base);
    return STATUS_OK;
}   



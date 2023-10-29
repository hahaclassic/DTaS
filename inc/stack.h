#include <stdbool.h>
#include "array.h"
#include "linked_list.h"

#ifndef STACK_H
#define STACK_H

typedef struct stack_t
{
    void *base;    

    bool (*is_empty)(void*);
    bool (*is_full)(void*);
    char (*get_top)(void*);
    int (*add)(void*, char);
    int (*delete)(void*);
    void (*show)(void*);
} stack_t;

#endif

void init_arr_stack(stack_t *stack, arr_stack_t *arr_stack);

void init_list_stack(stack_t *stack, list_stack_t *list_stack);

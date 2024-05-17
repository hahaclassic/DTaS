#include "stack.h"

void init_arr_stack(stack_t *stack, arr_stack_t *arr_stack)
{
    arr_stack->size = 0;
    //arr_stack->elements = elements;

    stack->base = arr_stack;
    stack->is_empty = arr_is_empty;
    stack->is_full = arr_is_full;
    stack->add = arr_add;
    stack->get_top = arr_get_top;
    stack->delete = arr_delete;
    stack->show = arr_show;
}


void init_list_stack(stack_t *stack, list_stack_t *list_stack)
{
    list_stack->size = 0;
    list_stack->top = NULL;

    stack->base = list_stack;
    stack->is_empty = list_is_empty;
    stack->is_full = list_is_full;
    stack->add = list_add;
    stack->get_top = list_get_top;
    stack->delete = list_delete;
    stack->show = list_show;
}

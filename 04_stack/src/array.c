#include "array.h"

bool arr_is_empty(void *vstack)
{
    return ((arr_stack_t*) vstack)->size == 0;
}

bool arr_is_full(void *vstack)
{
    return ((arr_stack_t*) vstack)->size >= MAX_SIZE;
}

int arr_add(void *vstack, char symbol)
{
    arr_stack_t *stack = vstack;

    if (arr_is_full(stack))
    {
        return ERR_STACK_FULL;
    }

    stack->elements[stack->size] = symbol;
    stack->size++;

    return STATUS_OK;
}

char arr_get_top(void *vstack)
{
    arr_stack_t *stack = vstack;

    if (arr_is_empty(stack))
    {
        return '\0';
    }
    
    return stack->elements[stack->size - 1];
}

int arr_delete(void *vstack)
{
    arr_stack_t *stack = vstack;

    if (arr_is_empty(stack))
    {
        return ERR_STACK_EMPTY;
    }

    stack->size--;

    return STATUS_OK;
}

void arr_show(void *vstack)
{
    arr_stack_t *stack = vstack;

    printf("Состояние стека: ");
    if (stack->size == 0)
    {
        printf("пустой");
    }

    for (size_t i = 0; i < stack->size; i++)
    {
        printf("%c ", stack->elements[i]);
    }
    printf("\n");
}

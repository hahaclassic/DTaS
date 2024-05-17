#include <stddef.h>
#include "errors.h"
#include <stdbool.h>
#include "const.h"

#ifndef STACK_ARRAY_H
#define STACK_ARRAY_H

// char elements[MAX_SIZE];

typedef struct arr_stack_t
{
    char elements[MAX_SIZE];
    size_t size;
} arr_stack_t;

#endif

bool arr_is_empty(void *vstack);

bool arr_is_full(void *vstack);

int arr_add(void *vstack, char symbol);

char arr_get_top(void *vstack);

int arr_delete(void *vstack);

void arr_show(void *vstack);

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include "errors.h"
#include "const.h"

#ifndef STACK_LIST_H
#define STACK_LIST_H

typedef struct node_t node_t;

struct node_t
{
    node_t *next;
    char symbol;
};

typedef struct list_stack_t
{
    node_t *top;
    size_t size;
} list_stack_t;

#endif

bool list_is_empty(void *vstack);

bool list_is_full(void *vstack);

int list_add(void *vstack, char symbol);

char list_get_top(void *vstack);

int list_delete(void *vstack);

void list_free(void *vstack);

void list_show(void *vstack);

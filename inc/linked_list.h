#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include "errors.h"
#include "dynamic_arr.h"

#define NOT_EQUAL 1
#define EQUAL 0

typedef struct node node_t;

struct node
{
    void *data;
    node_t *next;
};

bool list_is_empty(node_t *node);

node_t *list_init(dynamic_arr_t *arr);

void list_free(node_t *head);

size_t list_len(node_t *head);


void *pop_front(node_t **head);

node_t *find(node_t *head, const void *data, int (*comparator)(const void*, const void*));

node_t *reverse(node_t *head);

#endif

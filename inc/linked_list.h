#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include "errors.h"

#define NOT_EQUAL 1
#define EQUAL 0

typedef struct node node_t;

struct node
{
    void *data;
    node_t *next;
};

typedef struct list_queue_t
{
    node_t *in;
    node_t *out;
    size_t len;
    size_t max_len;
} list_queue_t;

list_queue_t *create_queue(size_t max_len);

void destroy_queue(list_queue_t *queue);

// Добавляет в конец очереди элемент
int list_push(list_queue_t *queue, void *data);

// Возвращает первый элемент очереди. Из самой очереди удаляется.
node_t *list_pop(list_queue_t *queue);

void list_free(node_t *head);

size_t list_len(node_t *head);

#endif

#ifndef __LIST_QUEUE_H__
#define __LIST_QUEUE_H__

#include "types.h"
#include "errors.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "message.h"
#include "timer.h"

node_t *create_node(char c);
node_t *add_node(node_t *head, node_t *node);
node_t *pop_node(node_t **head);

void free_queues(node_t *head);

node_t *list_push(node_t *queue, char c);
node_t *list_pop(node_t **queue);
void list_print(node_t *queue);

error_t option_list(int n, int log_flag, int log_interval, ranges_t *ranges);

#endif

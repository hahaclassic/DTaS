#ifndef __SORT_H__
#define __SORT_H__

#include "errors.h"
#include <math.h>
#include "linked_list.h"
#include "const.h"
#include "datatype.h"

#define FIRST_GREATER 1
#define SECOND_GREATER -1
#define FIRST_MIN 1
#define SECOND_MIN -1
#define EQUAL 0

int compare_teams(const void *team1, const void *team2);

void front_back_split(node_t *head, node_t **back);

node_t *sorted_merge(node_t **head_a, node_t **head_b, int (*comparator)(const void *, const void *));

node_t *sort(node_t *head, int (*comparator)(const void *, const void *));

#endif

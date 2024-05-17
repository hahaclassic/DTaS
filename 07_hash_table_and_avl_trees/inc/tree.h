#ifndef __TREE_H__
#define __TREE_H__

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "errors.h"
#include "general_parameters.h"
#include <stdio.h>

// typedef enum err
// {
//     STATUS_OK = 0,
//     ERR_MEMORY_ALLOC,
//     ERR_NOT_FOUND,
//     ERR_KEY_EXISTS,
//     ERR_INVALID_ARGS,
// } error_t;

typedef struct tree_node_t tree_node_t;

struct tree_node_t
{
    char key[MAX_KEY_LEN + 1];
    char value[MAX_VALUE_LEN + 1];
    tree_node_t *left;
    tree_node_t *right;
};

void bst_free(tree_node_t *root);

error_t bst_insert_key(tree_node_t **root, size_t *count, const char *key, const char *value);

error_t bst_find(tree_node_t *root, size_t *count_comparison, const char *key, char **value);

void bst_in_order_traversal(tree_node_t *root, void (*action)(tree_node_t *data, void *param), void *param);

void bst_pre_order_traversal(tree_node_t *root, void (*action)(tree_node_t *data, void *param), void *param);

tree_node_t *bst_balance(tree_node_t *root);

#endif

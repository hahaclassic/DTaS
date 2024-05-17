#ifndef __TREE_H__
#define __TREE_H__

#include <stddef.h>
#include <stdbool.h>
#include "errors.h"
#include <string.h>
#include <stdlib.h>

#define NUM_OF_ACCESS_TYPES 3
#define MAX_FILE_NAME_LEN 50
#define MAX_NUM_OF_FILES 1000

#define FIRST_LATER_OR_EQUAL 1
#define SECOND_LATER -1

typedef struct date_t
{
    size_t hours;
    size_t minutes;
    size_t day;
    size_t month;
    size_t year;
} date_t;

typedef struct attributes_t
{
    char user[NUM_OF_ACCESS_TYPES]; // права доступа пользователя [rwx]
    char group[NUM_OF_ACCESS_TYPES]; // права доступа группы [rwx]
    char others[NUM_OF_ACCESS_TYPES]; // права доступа для остальных [rwx]
} attributes_t;


typedef struct node_t node_t;

struct node_t
{
    char name[MAX_FILE_NAME_LEN + 1];
    attributes_t *attr;
    date_t *last_access;
    node_t *left;
    node_t *right;
};

// BASIC
node_t *create_node(void);

void free_node(node_t *node);

void bst_free(node_t *root);


// APPEND - REMOVE
error_t bst_append(node_t **root, node_t *node, int (*compare)(void *arg1, void *arg2));

node_t *bst_remove(node_t *root, int (*compare)(void *arg1, void *param), void *param, error_t *err);


node_t *bst_alpha_remove_all(node_t *root, node_t *mask);

node_t *bst_date_remove_all(node_t *root, node_t *mask);


// COMPARATORS

int compare_names(void *arg1, void *arg2);

int compare_dates(void *arg1, void *arg2);

int is_older(void *arg1, void *arg2);

// TRAVERSAL

void bst_in_order_traversal(node_t *root, void (*action)(node_t *data, void *param), void *param);

void bst_pre_order_traversal(node_t *root, void (*action)(node_t *data, void *param), void *param);


// SPECIAL

void bst_convert(node_t *src_root, node_t **dest_root, int (*compare)(void *arg1, void *param));

node_t *bst_deep_copy(node_t *src_root);


#endif


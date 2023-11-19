#ifndef __TREE_H__
#define __TREE_H__

#include <stddef.h>
#include <stdbool.h>

typedef struct date_t
{
    size_t hour;
    size_t minutes;
    size_t day;
    size_t month;
    size_t year;
} date_t;

#define NUM_OF_ACCESS_TYPES 3

typedef struct attributes_t
{
    char user[NUM_OF_ACCESS_TYPES]; // права доступа пользователя [rwx]
    char group[NUM_OF_ACCESS_TYPES]; // права доступа группы [rwx]
    char others[NUM_OF_ACCESS_TYPES]; // права доступа для остальных [rwx]
    bool immutable; // [i]
    bool secure_deletion; // [s]
} attributes_t;


typedef struct node tree_node_t;

struct node
{
    char *name;
    attributes_t *attr;
    date_t *last_access;
    tree_node_t *left;
    tree_node_t *right;
};

#endif

/*
    1. Считать данные в дерево
*/


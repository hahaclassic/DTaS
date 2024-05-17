#ifndef __OPEN_HASH_TABLE_H__
#define __OPEN_HASH_TABLE_H__

#include "general_parameters.h"

typedef struct bucket_node_t  bucket_node_t ;
typedef struct open_hash_table_t open_hash_table_t;

struct bucket_node_t 
{
    char key[MAX_KEY_LEN + 1];
    char value[MAX_VALUE_LEN + 1];
    bucket_node_t *next;
};

struct open_hash_table_t 
{
    bucket_node_t *data;
    size_t size; // Размер хеш-таблицы
    size_t len; // Количество элементов в хеш-таблице
    size_t (*func)(const char *, size_t);
};

open_hash_table_t *open_hash_table_create(size_t size, size_t (*func)(const char *, size_t));

void open_hash_table_free(open_hash_table_t *table);


error_t open_hash_table_auto_restruct(open_hash_table_t *table);

error_t open_hash_table_restruct(open_hash_table_t *table, size_t new_size);


// with table restruction 
error_t open_hash_table_insert(open_hash_table_t *table, const char *key, const char *value);

error_t open_hash_table_simple_insert(open_hash_table_t *table, bool mode, size_t *count,
    const char *key, const char *value);

error_t open_hash_table_find(open_hash_table_t *table, size_t *count_comparison, const char *key, char **value);


void open_hash_table_show(open_hash_table_t *table);

#endif // __OPEN_HASH_TABLE_H__


#ifndef __CLOSED_HASH_TABLE_H__
#define __CLOSED_HASH_TABLE_H__

#include "general_parameters.h"

typedef struct block_t block_t;
typedef struct closed_hash_table_t closed_hash_table_t;

struct block_t
{
    char key[MAX_KEY_LEN + 1];
    char value[MAX_VALUE_LEN + 1];
};

struct closed_hash_table_t 
{
    block_t *data;
    size_t size; // Размер хеш-таблицы
    size_t len; // Количество элементов в хеш-таблице
    size_t (*func)(const char *, size_t);
};

closed_hash_table_t *closed_hash_table_create(size_t size, size_t (*func)(const char *, size_t));

void closed_hash_table_free(closed_hash_table_t *table);



error_t closed_hash_table_auto_restruct(closed_hash_table_t *table);

error_t closed_hash_table_restruct(closed_hash_table_t *table, size_t new_size);



// with table restruction 
error_t closed_hash_table_insert(closed_hash_table_t *table, const char *key, const char *value);

error_t closed_hash_table_simple_insert(closed_hash_table_t *table, bool mode, size_t *count,
    const char *key, const char *value);

error_t closed_hash_table_find(closed_hash_table_t *table, size_t *count_comparison, const char *key, char **value);

void closed_hash_table_show(closed_hash_table_t *table);


#endif // __CLOSED_HASH_TABLE_H__

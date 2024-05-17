#include "closed_hash_table.h"



closed_hash_table_t *closed_hash_table_create(size_t size, size_t (*func)(const char *, size_t))
{
    closed_hash_table_t *table = malloc(sizeof(closed_hash_table_t));

    if (table == NULL)
    {
        return NULL;
    }
    
    table->data = malloc(sizeof(block_t) * size); 
    if (table->data == NULL)
    {
        free(table);
        return NULL;
    }

    block_t *curr;
    for (size_t i = 0; i < size; i++)
    {
        curr = table->data + i;
        curr->key[0] = '\0';  //(table->data + i)->key = NULL;
        curr->value[0] = '\0';  //(table->data + i)->value = NULL;
    }

    table->size = size;
    table->func = func;
    table->len = 0;

    return table;
}

void closed_hash_table_free(closed_hash_table_t *table)
{
    free(table->data);    
    free(table);
}

error_t closed_hash_table_auto_restruct(closed_hash_table_t *table)
{
    error_t err;
    size_t new_size, old_size = table->size, old_len = table->len;
    size_t count_comparison;
    block_t *new_data = NULL, *old_data = table->data;
    block_t *curr;

    do 
    {
        if (new_data != NULL)
        {
            free(new_data);
        }

        new_size = (size_t) (((double) table->size) * RESIZE_STEP);   
        new_data = malloc(sizeof(block_t) * new_size);

        if (new_data == NULL)
        {
            table->data = old_data;
            table->size = old_size;
            table->len = old_len;
            return ERR_MEMORY_ALLOCATION;
        }

        table->data = new_data;
        table->size = new_size;
        table->len = 0;

        for (size_t i = 0; i < table->size; i++)
        {
            curr = table->data + i;
            curr->key[0] = '\0';  
            curr->value[0] = '\0';
        }   

        for (size_t i = 0; i < old_size; i++)
        {
            curr = old_data + i;
            if (strlen(curr->key) != 0)
            {
                err = closed_hash_table_simple_insert(table, LIMIT_OF_COMPARISON_OFF, &count_comparison, curr->key, curr->value);
            }
            if (err)
            {
                break;
            }
        }
    }
    while (err);

    return STATUS_OK;
}

error_t closed_hash_table_restruct(closed_hash_table_t *table, size_t new_size)
{
    error_t err;
    size_t old_size = table->size, old_len = table->len;
    size_t count_comparison;
    block_t *new_data = NULL, *old_data = table->data;
    block_t *curr;

    if (new_size < table->len)
    {
        return ERR_WRONG_SIZE_FOR_RESTUCT;
    }

    new_data = malloc(sizeof(block_t) * new_size);
    if (new_data == NULL)
    {
        return ERR_MEMORY_ALLOCATION;
    }

    table->data = new_data;
    table->size = new_size;
    table->len = 0;

    for (size_t i = 0; i < table->size; i++)
    {
        curr = table->data + i;
        curr->key[0] = '\0';  
        curr->value[0] = '\0';
    }   

    for (size_t i = 0; i < old_size; i++)
    {
        curr = old_data + i;
        if (strlen(curr->key) != 0)
        {
            err = closed_hash_table_simple_insert(table, LIMIT_OF_COMPARISON_OFF, &count_comparison, curr->key, curr->value);
        }

        if (err)
        {
            table->data = old_data;
            table->size = old_size;
            table->len = old_len;
            free(new_data);
            return err;
        }
    }

    return STATUS_OK;
}

// with table restruction 
error_t closed_hash_table_insert(closed_hash_table_t *table, const char *key, const char *value)
{
    error_t err;
    size_t count;

    do 
    {
        err = closed_hash_table_simple_insert(table, LIMIT_OF_COMPARISON_ON, &count, key, value);
        if (err == ERR_LIMIT_OF_COMPARISONS || err == ERR_HASH_TABLE_IS_FULL)
        {
            if (closed_hash_table_auto_restruct(table) != STATUS_OK)
            {
                return ERR_MEMORY_ALLOCATION;
            }
        }
        else if (err)
        {
            return err;
        }
    }
    while (err);

    return STATUS_OK;
}

error_t closed_hash_table_simple_insert(closed_hash_table_t *table, bool mode, size_t *count, 
    const char *key, const char *value)
{
    if (table->len == table->size)
    {
        return ERR_HASH_TABLE_IS_FULL;
    }

    size_t position = table->func(key, table->size);
    block_t *block = table->data + position;
    *count = 0;

    while (block->key[0] != '\0')
    {           
        if (strcmp(block->key, key) == 0)
        {
            return ERR_KEY_EXISTS;
        }
        if (mode == LIMIT_OF_COMPARISON_ON && *count == MAX_COMPARISON)
        {
            return ERR_LIMIT_OF_COMPARISONS;
        }
        if (block == table->data + table->size - 1)
        {
            block = table->data;
        }
        else
        {
            block++;
        }
    }

    strcpy(block->key, key);
    strcpy(block->value, value);
    table->len++;

    return STATUS_OK;
}

error_t closed_hash_table_find(closed_hash_table_t *table, size_t *count_comparison,
     const char *key, char **value)
{
    size_t position = table->func(key, table->size);
    block_t *block = table->data + position;
    *count_comparison = 0;

    while (block->key[0] != '\0')
    {           
        (*count_comparison)++;
        if (strcmp(block->key, key) == 0)
        {
            *value = block->value;
            return STATUS_OK;
        }
        if (block == table->data + table->size - 1)
        {
            block = table->data;
        }
        else
        {
            block++;
        }
    }

    return ERR_NOT_FOUND;
}


void closed_hash_table_show(closed_hash_table_t *table)
{
    if (table == NULL)
    {
        return;
    }

    int show_empty = 1;
    printf("Показывать пустые ячейки? (1/0): ");
    int input = scanf("%d", &show_empty);
    if (input != 1)
    {
        show_empty = 1;
    }

    printf("\nХеш-таблица с закрытой адресацией:\n");
    block_t *curr;
    for (size_t i = 0; i < table->size; i++)
    {
        curr = table->data + i;
        if (curr->key[0] != '\0' || show_empty)
        {
            printf("%zu. ", i);
            if (curr->key[0] != '\0')
            {
                printf("{hash: %zu, key: %s}", table->func(curr->key, table->size), curr->key);
            }
            printf("\n");
        }
    }
}




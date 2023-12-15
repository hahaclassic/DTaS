#include "open_hash_table.h"


open_hash_table_t *open_hash_table_create(size_t size, size_t (*func)(const char *, size_t))
{
    open_hash_table_t *table = malloc(sizeof(open_hash_table_t));

    if (table == NULL)
    {
        return NULL;
    }
    
    table->data = malloc(sizeof(bucket_node_t) * size); 
    if (table->data == NULL)
    {
        free(table);
        return NULL;
    }

    bucket_node_t *curr;
    for (size_t i = 0; i < size; i++)
    {
        curr = table->data + i;
        curr->key[0] = '\0';  //(table->data + i)->key = NULL;
        curr->value[0] = '\0';  //(table->data + i)->value = NULL;
        curr->next = NULL;
    }

    table->size = size;
    table->func = func;
    table->len = 0;

    return table;
}

bucket_node_t *bucket_node_create()
{
    bucket_node_t *node = malloc(sizeof(bucket_node_t));
    
    if (node != NULL)
    {
        node->key[0] = '\0';
        node->value[0] = '\0';
        node->next = NULL;
    }
    return node;
}

void bucket_node_free(bucket_node_t *node)
{
    //free(node->key);
    //free(node->value);
    free(node);
}

void data_free(open_hash_table_t *table)
{
    bucket_node_t *next, *curr;
    for (size_t i = 0; i < table->size; i++)
    {
        curr = (table->data + i);
        curr = curr->next;
        while (curr != NULL)
        {
            next = curr->next;
            bucket_node_free(curr);
            curr = next;
        }
    }
    free(table->data);
}

void open_hash_table_free(open_hash_table_t *table)
{
    data_free(table);
    free(table);
}

error_t open_hash_table_auto_restruct(open_hash_table_t *table)
{
    error_t err;
    size_t new_size, old_size = table->size, old_len = table->len;
    size_t count_comparison;
    bucket_node_t *new_data = NULL, *old_data = table->data;
    bucket_node_t *curr;

    do 
    {
        if (new_data != NULL)
        {
            data_free(table);
        }

        new_size = (size_t) (((double) table->size) * RESIZE_STEP);   
        new_data = malloc(sizeof(bucket_node_t) * new_size);

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
            curr->next = NULL;
        }

        for (size_t i = 0; i < old_size; i++)
        {
            curr = old_data + i;
            while (curr != NULL)
            {
                if (strlen(curr->key) != 0)
                {
                    err = open_hash_table_simple_insert(table, LIMIT_OF_COMPARISON_ON, &count_comparison, curr->key, curr->value);
                }
                if (err)
                {
                    break;
                }
                curr = curr->next;
            }
        }
    }
    while (err);

    return STATUS_OK;
}

error_t open_hash_table_restruct(open_hash_table_t *table, size_t new_size)
{
    error_t err;
    size_t count_comparison;
    size_t old_size = table->size, old_len = table->len;
    bucket_node_t *new_data = NULL, *old_data = table->data;
    bucket_node_t *curr;
 
    new_data = malloc(sizeof(bucket_node_t) * new_size);
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
        curr->next = NULL;
    }

    for (size_t i = 0; i < old_size; i++)
    {
        curr = old_data + i;
        while (curr != NULL)
        {
            if (strlen(curr->key) != 0)
            {
                err = open_hash_table_simple_insert(table, LIMIT_OF_COMPARISON_OFF, &count_comparison, curr->key, curr->value);
            }
            if (err)
            {
                data_free(table);
                table->data = old_data;
                table->size = old_size;
                table->len = old_len;
                return err;
            }
            curr = curr->next;
        }
    }

    return STATUS_OK;
}


// with table restruction 
error_t open_hash_table_insert(open_hash_table_t *table, const char *key, const char *value)
{
    error_t err;
    size_t count;

    do 
    {
        err = open_hash_table_simple_insert(table, LIMIT_OF_COMPARISON_ON, &count, key, value);
        if (err == ERR_LIMIT_OF_COMPARISONS)
        {
            if (open_hash_table_auto_restruct(table) != STATUS_OK)
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

error_t open_hash_table_simple_insert(open_hash_table_t *table, bool mode, size_t *count,
    const char *key, const char *value)
{
    size_t position = table->func(key, table->size);
    bucket_node_t *bucket = table->data + position;
    *count = 0;

    if (bucket->key[0] != '\0')
    {
        while (bucket->next != NULL)
        {
            (*count)++;
            if (strcmp(bucket->key, key) == 0)
            {
                return ERR_KEY_EXISTS;
            }
            if (mode == LIMIT_OF_COMPARISON_ON && *count == MAX_COMPARISON)
            {
                return ERR_LIMIT_OF_COMPARISONS;
            }
            bucket = bucket->next;
        }

        (*count)++;
        if (strcmp(bucket->key, key) == 0)
        {
            return ERR_KEY_EXISTS;
        }
        if (mode == LIMIT_OF_COMPARISON_ON && *count == MAX_COMPARISON)
        {
            return ERR_LIMIT_OF_COMPARISONS;
        }
        bucket->next = bucket_node_create();
        
        if (bucket->next == NULL)
        {
            return ERR_MEMORY_ALLOCATION;
        }
        
        bucket = bucket->next;
    }

    strcpy(bucket->key, key);
    strcpy(bucket->value, value);
    table->len++;

    return STATUS_OK;
}

error_t open_hash_table_find(open_hash_table_t *table, size_t *count_comparison,
    const char *key, char **value)
{
    size_t position = table->func(key, table->size);
    bucket_node_t *bucket = table->data + position;
    *count_comparison = 0;

    for (; bucket != NULL; bucket = bucket->next)
    {
        (*count_comparison)++;
        if (strcmp(bucket->key, key) == 0)
        {
            *value = bucket->value;
            return STATUS_OK;
        }
    }

    return ERR_NOT_FOUND;
}


void open_hash_table_show(open_hash_table_t *table)
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

    printf("\nХеш-таблица с открытой адресацией:\n");
    bucket_node_t *curr;
    for (size_t i = 0; i < table->size; i++)
    {
        curr = table->data + i;
        if (curr->key[0] != '\0' || show_empty)
        {
            printf("%zu. ", i);
            while (curr != NULL)
            {
                if (curr->key[0] != '\0')
                {
                    printf("{hash: %zu, key: %s}", table->func(curr->key, table->size), curr->key);
                }
                if (curr->next != NULL)
                {
                    printf(" -> ");
                }
                curr = curr->next;
            }
            printf("\n");
        }
    }
}



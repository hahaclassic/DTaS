#include "dynamic_arr.h"

void da_init(dynamic_arr_t *arr, size_t size)
{
    arr->len = INIT_LEN;
    arr->cap = INIT_CAP;
    arr->data = NULL;
    arr->size = size;
}

void add(char *dest, char *src, size_t size)
{
    size_t i = 0;
    while (i < size)
    {
        *dest = *src;
        dest++;
        src++;
        i++;
    }
}

int da_append(dynamic_arr_t *arr, void *item)
{
    if (!arr->data)
    {
        arr->data = malloc(INIT_CAP * arr->size);
        if (!arr->data)
        {
            return ERR_MEMORY_ALLOCATION;
        }
        arr->cap = INIT_CAP;
        arr->len = 0;
    }
    else if (arr->len >= arr->cap)
    {
        void *tmp = realloc(arr->data, arr->cap * DA_STEP * arr->size);
        if (!tmp)
        {
            return ERR_MEMORY_ALLOCATION;
        }
        arr->data = tmp;
        arr->cap *= DA_STEP;
    }

    char *array = arr->data;
    add(&array[arr->len * arr->size], (char *) item, arr->size);
    arr->len++;
    return STATUS_OK;
}

void da_free(dynamic_arr_t *arr)
{
    free(arr->data);
}

void free_teams(dynamic_arr_t *arr)
{
    char *data = arr->data; 
    for (size_t i = 0; i < arr->len; i++)
    {
        free(((team_t *) data)->name);
        free(((team_t *) data)->sponsor);
        data += arr->size;
    } 

    da_free(arr);
}

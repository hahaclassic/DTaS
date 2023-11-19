#ifndef __DYNAMIC_ARR_H__
#define __DYNAMIC_ARR_H__

#include "stdio.h"
#include "errors.h"
#include <stdlib.h>
#include "datatype.h"

#define INIT_CAP 5
#define INIT_LEN 0
#define DA_STEP 2

#ifndef DYNAMIC_ARR_H
#define DYNAMIC_ARR_H

typedef struct dynamic_arr_t
{
    void *data; 
    size_t len;
    size_t cap;
    size_t size;
} dynamic_arr_t;

#endif

int da_append(dynamic_arr_t *arr, void *item);

void da_free(dynamic_arr_t *arr);

void da_init(dynamic_arr_t *arr, size_t size);

void free_teams(dynamic_arr_t *arr);

#endif

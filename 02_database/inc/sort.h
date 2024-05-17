
#include <stdlib.h>
#include <stdio.h>
#include "type.h"

int compare_int(const void *arg1, const void *arg2);

int compare_key_t(const void *arg1, const void *arg2);

int compare_car_t(const void *arg1, const void *arg2);

void quick_sort(void *base, size_t nmemb, size_t size, int (*compare)(const void*, const void*));

void selection_sort(void *base, size_t nmemb, size_t size, int (*compare)(const void*, const void*));

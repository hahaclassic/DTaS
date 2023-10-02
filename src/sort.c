#include "sort.h"
#include "type.h"
#include <stdlib.h>

int compare_int(const void *arg1, const void *arg2)
{
    const int *a = arg1;
    const int *b = arg2;

    return *a - *b;
}

int compare_car_t(const void *arg1, const void *arg2)
{
    const car_t *a = arg1;
    const car_t *b = arg2;

    return a->price - b->price;
}

void swap(char *s, char *t, size_t size)
{
    size_t i = 0;
    char temp;
    while (i < size)
    {
        temp = *s;
        *s = *t;
        *t = temp;

        i++;
        s++;
        t++;
    }
}

void selection_sort(void *base, size_t nmemb, size_t size, int (*compare)(const void*, const void*))
{
    char *start = base;
    char *end = start + (nmemb - 1) * size;

    char *max;
    while (end > start)
    {
        max = start;
        for (char *curr = start + size; curr <= end; curr += size)
        {
            if (compare((void *) curr, (void *) max) > 0)
            {
                max = curr;
            }
        }
        swap(max, end, size);
        end -= size;
    }
}

void partion(void *base, size_t size, void *low, void *high)
{
    
}

void quick_sort(void *base, size_t nmemb, size_t size, int (*compare)(const void*, const void*))
{

}
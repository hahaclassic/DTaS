#include <stdbool.h>
#include <stdlib.h>

#define MAX_NUMBER_OF_RECORDS 10000

#define MAX_STR_LEN 15

#ifndef OLD_H
typedef struct
{
    int year;
    int mileage;
    int repairs;
    int owners;
} old_t;
#define OLD_H
#endif

#ifndef KEY_H
#define KEY_H

typedef struct
{
    int index;
    int value;
} key_t;
#endif

#ifndef CAR_H
typedef struct
{
    char brand[MAX_STR_LEN + 1];
    char country[MAX_STR_LEN + 1];
    char color[MAX_STR_LEN + 1];
    int price;
    bool service;
    bool condition;
    union
    {
        int guarantee;
        old_t old;
    };
} car_t;  
#define CAR_H
#endif


#ifndef STATS_H
#define STATS_H
typedef struct
{
    unsigned long long qsort_cars_time;
    unsigned long long qsort_keys_time;
    unsigned long long ssort_cars_time;
    unsigned long long ssort_keys_time;
    int cars_mem;
    int keys_mem;
} stat_t;
#endif

void copy(void *src, void *dest, size_t size, size_t len);

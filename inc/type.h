#include <stdbool.h>
#include <stdlib.h>

#define MAX_NUMBER_OF_RECORDS 50

#define MAX_STR_LEN 20

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

void copy(void *src, void *dest, size_t size, size_t len);

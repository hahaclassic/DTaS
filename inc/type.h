#include <stdbool.h>

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
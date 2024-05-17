#include <string.h>
#include "errors.h"
#include "type.h"

// show result
#define SHOW_CARS 1
#define SHOW_KEYS 2
#define SHOW_CARS_WITH_KEYS 3


#define CARS_HEADER "\n+===========================================================================================================================================================+\n" \
                      "|   i   |      brand      |     country     |      color      |    price    | service | condition | guarantee | year |   mileage  |  repairs   |   owners   |\n" \
                      "+-----------------------------------------------------------------------------------------------------------------------------------------------------------+\n"

#define CAR_FORMAT    "| %-5d | %-15s | %-15s | %-15s | %-11d | %-7c | %-9s | %-9d | %-4d | %-10d | %-10d | %-10d |\n" \
                      "+-----------------------------------------------------------------------------------------------------------------------------------------------------------+"
                                 
#define KEYS_HEADER "\n+=========================================+\n" \
                      "|   i   |    index    |       price       |\n" \
                      "+-----------------------------------------+\n"

#define KEYS_FORMAT   "| %-5d | %-11d | %-17d |\n" \
                      "+-----------------------------------------+\n"


void show_car(const void *obj, int index);

void show_key(const void *obj, int index);

void show_table(void *base, size_t len, size_t size, char *header, void (*show)(const void*, int));

void show_table_with_keys(car_t cars[], key_t keys[], size_t len);

int show_spec(car_t cars[], size_t len, int min_price, int max_price, char *name);

void show_stats(stat_t *stats, int len);

void show_result(car_t cars[], key_t keys[], int len, int mode);

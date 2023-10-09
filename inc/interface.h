#include "type.h"
#include <stdio.h>
#include <string.h>
#include "errors.h"

#define ADD_RECORD 0
#define DELETE_RECORD 1
#define SORT_KEYS 2
#define SORT_TABLE 3
#define STATS 4
#define SHOW_SOURCE_TABLES 5

int read_new_record(car_t *car, int len);

int read_value(int *value);

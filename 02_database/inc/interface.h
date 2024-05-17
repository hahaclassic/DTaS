#include "type.h"
#include <string.h>
#include "errors.h"

// operations
#define ADD_RECORD 1
#define DELETE_RECORD 2
#define SORT_KEYS 3
#define SORT_TABLE 4
#define STATS 5
#define SEARCH 6
#define SHOW_SOURCE_CARS 7
#define SHOW_SOURCE_KEYS 8

// show result
#define SHOW_CARS 1
#define SHOW_KEYS 2
#define SHOW_CARS_WITH_KEYS 3


int get_new_record(car_t *car, int len);

int read_value(int *value);

int get_search_data(int *min_price, int *max_price, char *brand);

void message_ok(int mode);

int menu(int *operation);

int result_menu(int *operation);

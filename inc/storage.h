#include <string.h>
#include "type.h"
#include "errors.h"

int get_all(FILE *file, car_t cars[], key_t keys[], int *len);

int add_record(FILE *file, car_t *car);

int delete_record(FILE *file, car_t cars[], int len, int value);

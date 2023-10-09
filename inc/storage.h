#include <stdio.h>
#include <string.h>
#include "type.h"
#include "errors.h"

#define READ_MODE 1
#define WRITE_MODE 2
#define ADD_MODE 3

int get_all(FILE *file, car_t cars[], key_t keys[], int *len);

int add_record(FILE *file, car_t *car);

int delete_record(FILE *file, car_t cars[], int len, int value);

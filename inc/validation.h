#include "errors.h"
#include <stdbool.h>
#include <string.h>

#define AMOUNT 0
#define MULTIPLICATION 1
#define INVERSE_MATRIX 2

int check_args(int argc, char **argv, int *operation);

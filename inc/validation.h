#ifndef __VALIDATION_H__
#define __VALIDATION_H__

#include "errors.h"
#include "string.h"

// operation modes
#define SORT 0
#define PRINT_ALL 1
#define FIND 2

int check_args(int argc, char **argv, int *operation);

#endif

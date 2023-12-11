#ifndef __GENERAL_PARAMETERS_H__
#define __GENERAL_PARAMETERS_H__

#include <stddef.h>
#include <stdlib.h>
#include "errors.h"
#include <string.h>
#include <stdbool.h>

#define DEFAULT_SIZE 100

#define MAX_KEY_LEN 20
#define MAX_VALUE_LEN 1000
#define RESIZE_STEP 1.5
#define MAX_COMPARISON 4

#define LIMIT_OF_COMPARISON_ON 1
#define LIMIT_OF_COMPARISON_OFF 0

size_t hash_func(const char *key, size_t size);

#endif // __GENERAL_PARAMETERS_H__

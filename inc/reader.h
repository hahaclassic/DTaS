#ifndef __READER_H__
#define __READER_H__

#include "string.h"
#include "errors.h"
#include "datatype.h"
#include <math.h>
#include "dynamic_arr.h"
#include "const.h"

int get_all(FILE *file, dynamic_arr_t *teams);

#endif

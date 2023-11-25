#ifndef __VALIDATION_H__
#define __VALIDATION_H__

#include "errors.h"
#include "string.h"

// operation modes
#define STREAM_FILE 0
#define STREAM_STDIN 1

error_t check_args(int argc, int *iostream);

#endif

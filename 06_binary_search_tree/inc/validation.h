#ifndef __VALIDATION_H__
#define __VALIDATION_H__

#include "errors.h"
#include "string.h"

// operation modes
#define STREAM_FILES 0
#define STREAM_STDIN_STDOUT 1

error_t check_args(int argc, int *iostream);

#endif

#ifndef __ERRORS_H__
#define __ERRORS_H__

#include <stdio.h>
#include "consts.h"

typedef enum error {
    STATUS_OK,
    ERR_WRONG_OPTION,
    ERR_ARR_SIZE,
    ERR_MEMORY_ALLOC,
    ERR_QUEUE_IS_FULL,
    ERR_TIMER
} error_t;

void err_message(error_t error);

#endif 

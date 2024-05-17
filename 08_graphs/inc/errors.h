#ifndef __ERRORS_H__
#define __ERRORS_H__

#include <stdio.h>

typedef enum _error
{
    /// При выполнении действия ошибок не возникло
    STATUS_OK = 0,

    ERR_INCORRECT_ARG,

    ERR_FILE_OPEN,

    ERR_READ_DATA,

    ERR_INVALID_DATA,

    ERR_INCORRECT_NUM_OF_VERTICES,

    ERR_INVALID_OPERATION,

    ERR_TIMER,
} error_t;

void err_message(error_t err);

#endif


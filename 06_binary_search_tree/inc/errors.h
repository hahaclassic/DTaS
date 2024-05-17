#ifndef __ERRORS_H__
#define __ERRORS_H__

#include <stdio.h>

typedef enum _error
{
    /// При выполнении действия ошибок не возникло
    STATUS_OK = 0,

    ERR_INCORRECT_ARG,

    ERR_NOT_FOUND,

    ERR_KEY_EXISTS,

    ERR_FILE_OPEN,

    ERR_MEMORY_ALLOCATION,

    ERR_INVALID_ATTR,

    ERR_INVALID_DATE,

    ERR_INVALID_NAME,

    ERR_INVALID_NUM_OF_FILES,

    ERR_READ_DATA,

    ERR_INVALID_OPERATION,

    ERR_TIMER,

    ERR_EMPTY_TREE,
} error_t;

void err_message(error_t err);

#endif


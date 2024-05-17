#ifndef __ERRORS_H__
#define __ERRORS_H__

#include <stdio.h>

typedef enum _error
{
    /// При выполнении действия ошибок не возникло
    STATUS_OK = 0,

    ERR_NOT_FOUND,

    ERR_KEY_EXISTS,

    ERR_FILE_OPEN,

    ERR_MEMORY_ALLOCATION,

    ERR_EMPTY_TREE,

    ERR_HASH_TABLE_IS_FULL,

    ERR_WRONG_SIZE_FOR_RESTUCT,

    ERR_LIMIT_OF_COMPARISONS,

    ERR_INVALID_OPERATION,

    ERR_READ_DATA,

    ERR_INVALID_DATA,

    ERR_TIMER,
} error_t;

void err_message(error_t err);

#endif


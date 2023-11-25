#ifndef __ERRORS_H__
#define __ERRORS_H__

#include "stdio.h"


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
} error_t;




// // Returned if the program or function completes successfully
// #define STATUS_OK 0

// // command line arguments error
// #define ERR_INCORRECT_ARG 1

// // tree
// #define STATUS_OK 0
// #define ERR_MEMORY_ALLOC 1
// #define ERR_NOT_FOUND 2
// #define ERR_KEY_EXISTS 3
// #define ERR_INVALID_ARGS 4


// // file errors
// #define ERR_FILE_OPEN 2
// #define ERR_EMPTY_FILE 3

// #define ERR_MEMORY_ALLOCATION 100

// // data reading errors
// #define ERR_INVALID_DATA 4
// #define ERR_READ_DATA 5
// #define ERR_EOF 6
// #define ERR_INCOMPLETE_STRUCT 7

// // linked list
// #define ERR_INIT_LIST 20

// // find
// #define ERR_NOT_FOUND 30

// // other
// #define ERR_COPY_DATA 9

// void err_message(int err);

#endif

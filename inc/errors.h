#ifndef __ERRORS_H__
#define __ERRORS_H__

#include "stdio.h"

// Returned if the program or function completes successfully
#define STATUS_OK 0

// command line arguments error
#define ERR_INCORRECT_ARG 1

// file errors
#define ERR_FILE_OPEN 2
#define ERR_EMPTY_FILE 3

#define ERR_MEMORY_ALLOCATION 100

// data reading errors
#define ERR_INVALID_DATA 4
#define ERR_READ_DATA 5
#define ERR_EOF 6
#define ERR_INCOMPLETE_STRUCT 7

// linked list
#define ERR_INIT_LIST 20

// find
#define ERR_NOT_FOUND 30

// other
#define ERR_COPY_DATA 9

void err_message(int err);

#endif

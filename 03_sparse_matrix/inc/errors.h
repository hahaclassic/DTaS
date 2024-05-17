#include <stdio.h>

#define STATUS_OK 0

// command line arguments error
#define ERR_INCORRECT_ARG 1

// file errors
#define ERR_FILE_OPEN 2

// data reading errors
#define ERR_INCORRECT_MATRIX_SIZES 3
#define ERR_READ_DATA 4
#define ERR_NOT_ENOUGH_ELEMENTS 5
#define ERR_INCORRECT_DATA 6

// operations
#define ERR_DIFFERENT_MATRIX_SIZES 8

// timer error
#define ERR_TIMER 50

// others
#define ERR_MEMORY_ALLOCATION 30


void err_message(int err);

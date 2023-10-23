#include <stdio.h>

#define STATUS_OK 0

// command line arguments error
#define ERR_INCORRECT_ARG 1

// file errors
#define ERR_FILE_OPEN 2

// data reading errors
#define ERR_INCORRECT_MATRIX_SIZES 4
#define ERR_READ_DATA 4
#define ERR_NOT_ENOUGH_ELEMENTS 5
#define ERR_TOO_MANY_ELEMENTS 6

// operations
#define ERR_DIFFERENT_SIZES 7
#define ERR_INCORRECT_SIZES 8
#define ERR_NON_SQUARE_MATRIX 9

#define ERR_NO_SINGLE_SOLUTION 11


// sparse_matrix
#define ERR_WRONG_TYPE_MATRIX 20


// others
#define ERR_MEMORY_ALLOCATION 30


void err_message(int err);

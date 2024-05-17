#include <stdio.h>

#define STATUS_OK 0

// Reading data
#define ERR_READ_INT 1
#define ERR_READ_FLOAT 2
#define ERR_BUFFER_OVERFLOW 3
#define ERR_INVALID_CHAR 4
#define ERR_EMPTY_INPUT 5
#define ERR_READ_MANTISSA 6
#define ERR_READ_EXP 7

#define ERR_STR_CMD 10

// multiply
#define ERR_INF 22
#define ERR_MACHINE_ZERO 23

void err_message(int err);

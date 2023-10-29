#include <stdio.h>

#define STATUS_OK 0

// data reading errors
#define ERR_READ_DATA 1
#define ERR_OPERATION_NUM 2
#define ERR_INCORRECT_DATA 5
#define ERR_MAX_LEN 6

// timer error
#define ERR_TIMER 50

// others
#define ERR_MEMORY_ALLOCATION 100


// stack
#define ERR_STACK_FULL 30
#define ERR_STACK_EMPTY 31


void err_message(int err);

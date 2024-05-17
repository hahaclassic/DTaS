#include <stdio.h>

#define STATUS_OK 0

// args
#define ERR_INVALID_ARGS 1

// file errors
#define ERR_FILE_OPEN 2
#define ERR_EMPTY_FILE 3

// data reading errors
#define ERR_INVALID_DATA 4
#define ERR_READ_DATA 5 
#define ERR_INCOMPLETE_STRUCT 7
#define ERR_TOO_MANY_OBJECTS 8
#define ERR_NO_DATA 9
#define ERR_READ_BEGINNING_OF_STRUCT 10

// interface
#define ERR_NOT_ENOUGH_SPACE 21

#define ERR_INVALID_USER_DATA 22

// data deleting errors
#define ERR_NO_DATA_WITH_THIS_VALUE 31


// data writing errors
#define ERR_SAVE_DATA 41
#define ERR_EMPTY_SEARCH_RESULT 43


// timer error
#define ERR_TIMER 50

// other
#define ERR_COPY_DATA 20
#define ERR_NOT_FOUND 21

void err_message(int err);

#include "errors.h"
#include <stdio.h>
#include <ctype.h>

#define BUFER_OVERFLOW_ERR 1
#define TOO_MANY_SPECIAL_CHAR_ERR 2
#define INVALID_SEQUENCE 3

#define IS_DIGIT 5 // status = 5 - previous symbol was number,
#define IS_DOT 1 // status = 1 - previous symbol was dot,
#define IS_E_LETTER 2 // status = 2 - previos symbol was E/e,
#define IS_PLUS_MINUS 3 // status = 3 - previous symbol was +/-
#define IS_SPACE 4 // status = 4 - previous symbol was space
#define INVALID_SYMBOL 0  // status = 0 - fail
#define START 6

int check_float(char *str, int *is_e_letter_exist);

unsigned short check_symbol(int curr);

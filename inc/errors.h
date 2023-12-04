#ifndef __ERRORS_H__
#define __ERRORS_H__

#include <stdio.h>
#include "consts.h"

typedef enum error {
    STATUS_OK,
    ERR_WRONG_OPTION,
    ERR_ARR_SIZE,
    ERR_MEMORY_ALLOC
} error_t;

// static char const * const err_messages[] = {
//         "",
//         "Введена неправильная команда!",
//         "Слишком большое число!",
//         "Ошибка выделения памяти!"
// };

void print_error(FILE *stream, error_t error);

#endif 

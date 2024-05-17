#include "errors.h"

// Sends an error message to the terminal. 
// If there is no error, it doesn't output anything.


void err_message(int err)
{
    switch (err)
    {
        case STATUS_OK:
            break;
        case ERR_READ_DATA:
            printf("[ERR]: Ошибка при попытке чтения данных.\n");
            break;
        case ERR_OPERATION_NUM:
            printf("[ERR]: Некорректный номер операции.\n");
            break;
        case ERR_INCORRECT_DATA:
            printf("[ERR]: Некорректные данные\n");
            break;
        case ERR_MAX_LEN:
            printf("[ERR]: Введена слишком длинная строка\n");
            break;
        case ERR_TIMER:
            printf("[ERR]: Ошибка при измерениях.\n");
            break;
        case ERR_MEMORY_ALLOCATION:
            printf("[ERR]: Ошибка при попытке выделения памяти.\n");
            break;
        default:
            printf("[ERR]: Неизвестная ошибка.");
            break;
    }
}


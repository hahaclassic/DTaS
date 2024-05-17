#include "errors.h"

// Sends an error message to the terminal. 
// If there is no error, it doesn't output anything.

void err_message(error_t err)
{
    switch (err)
    {
        case STATUS_OK:
            break;
        case ERR_INCORRECT_ARG:
            printf("\n[ERR]: Указаны некорректные аргументы.\n");
            break;
        case ERR_FILE_OPEN:
            printf("\n[ERR]: Ошибка при открытии файла.\n");
            break;
        case ERR_READ_DATA:
            printf("\n[ERR]: Ошибка при попытке чтения данных.\n");
            break;
        case ERR_INVALID_DATA:
            printf("\n[ERR]: Некорректные данные.\n");
            break;
        case ERR_INCORRECT_NUM_OF_VERTICES:
            printf("\n[ERR]: Некорректное количество вершин.\n");
            break;
        case ERR_INVALID_OPERATION:
            printf("\n[ERR]: Указан некорректный номер операции.\n");
            break;
        case ERR_TIMER:
            printf("\n[ERR]: Ошибка при измерении времени\n");
            break;
        default:
            printf("\n[ERR]: Неизвестная ошибка.");
            break;
    }
}

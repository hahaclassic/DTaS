#include "errors.h"

// Sends an error message to the terminal. 
// If there is no error, it doesn't output anything.

void err_message(int err)
{
    switch (err)
    {
        case STATUS_OK:
            break;
        case ERR_INCORRECT_ARG:
            printf("[ERR]: Указаны некорректные аргументы.\n");
            break;
        case ERR_FILE_OPEN:
            printf("[ERR]: Ошибка при открытии файла.\n");
            break;
        case ERR_EMPTY_FILE:
            printf("[ERR]: Указан пустой файл.\n");
            break;
        case ERR_INVALID_DATA:
            printf("[ERR]: В файле присутствуют некорректные данные.\n");
            break;
        case ERR_READ_DATA:
            printf("[ERR]: Ошибка при попытке чтения данных.\n");
            break;
        case ERR_EOF:
            printf("[ERR]: Достигнут конец файла.\n");
            break;
        case ERR_INCOMPLETE_STRUCT:
            printf("[ERR]: В файле присутствуют некорректные данные.\n");
            break;
        case ERR_COPY_DATA:
            printf("[ERR]: Ошибка при копировании данных.\n");
            break;
        default:
            printf("[ERR]: Неизвестная ошибка.");
            break;
    }
}

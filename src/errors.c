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
            printf("[ERR]: Указаны некорректные аргументы.\n");
            break;
        case ERR_FILE_OPEN:
            printf("[ERR]: Ошибка при открытии файла.\n");
            break;
        case ERR_READ_DATA:
            printf("[ERR]: Ошибка при попытке чтения данных.\n");
            break;
        case ERR_INVALID_ATTR:
            printf("[ERR]: Права доступа файла указаны некорректно.\n");
            break;
        case ERR_INVALID_DATE:
            printf("[ERR]: Дата последнего обращения указана некорректно.\n");
            break;
        case ERR_INVALID_NAME:
            printf("[ERR]: В имени файла указаны недопустимые символы или длина имени превышает 50 знаков.\n");
            break;
        case ERR_NOT_FOUND:
            printf("[ERR]: Файл с такими параметрами не найден.\n");
            break;
        case ERR_KEY_EXISTS:
            printf("[ERR]: Директория-дерево уже содержит файл с таким именем.\n");
            break;
        case ERR_MEMORY_ALLOCATION:
            printf("[ERR]: Ошибка при выделении памяти.\n");
            break;
        case ERR_INVALID_NUM_OF_FILES:
            printf("[ERR]: В файле указано некорректное количество файлов.\n");
            break;
        case ERR_INVALID_OPERATION:
            printf("[ERR]: Указан некорректный номер операции.\n");
            break;
        case ERR_TIMER:
            printf("[ERR]: Ошибка при измерении времени\n");
            break;
        case ERR_EMPTY_TREE:
            printf("[ERR]: Невозможно выполнить операцию. Директория пуста.\n");
            break;
        default:
            printf("[ERR]: Неизвестная ошибка.");
            break;
    }
}

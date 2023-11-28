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
        case ERR_INVALID_ATTR:
            printf("\n[ERR]: Права доступа файла указаны некорректно.\n");
            break;
        case ERR_INVALID_DATE:
            printf("\n[ERR]: Дата последнего обращения указана некорректно.\n");
            break;
        case ERR_INVALID_NAME:
            printf("\n[ERR]: В имени файла указаны недопустимые символы, или длина имени превышает 50 знаков.\n");
            break;
        case ERR_NOT_FOUND:
            printf("\n[ERR]: Файл с такими параметрами не найден.\n");
            break;
        case ERR_KEY_EXISTS:
            printf("\n[ERR]: Директория-дерево уже содержит файл с таким именем.\n");
            break;
        case ERR_MEMORY_ALLOCATION:
            printf("\n[ERR]: Ошибка при выделении памяти.\n");
            break;
        case ERR_INVALID_NUM_OF_FILES:
            printf("\n[ERR]: В файле указано некорректное количество файлов.\n");
            break;
        case ERR_INVALID_OPERATION:
            printf("\n[ERR]: Указан некорректный номер операции.\n");
            break;
        case ERR_TIMER:
            printf("\n[ERR]: Ошибка при измерении времени\n");
            break;
        case ERR_EMPTY_TREE:
            printf("\n[ERR]: Невозможно выполнить операцию. Директория пуста.\n");
            break;
        default:
            printf("\n[ERR]: Неизвестная ошибка.");
            break;
    }
}

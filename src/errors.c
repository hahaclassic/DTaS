#include "errors.h"

// Sends an error message to the terminal. 
// If there is no error, it doesn't output anything.

void err_message(error_t err)
{
    switch (err)
    {
        case STATUS_OK:
            break;
        case ERR_NOT_FOUND:
            printf("\n[ERR]: Ключевое слово не найдено.\n");
            break;
        case ERR_KEY_EXISTS:
            printf("\n[ERR]: Данное ключевое слово уже существует.\n");
            break;
        case ERR_MEMORY_ALLOCATION:
            printf("\n[ERR]: Ошибка при выделении памяти.\n");
            break;
        case ERR_EMPTY_TREE:
            printf("\n[ERR]: Невозможно выполнить операцию. Пустое дерево.\n");
            break;
        case ERR_HASH_TABLE_IS_FULL:
            printf("\n[ERR]: Невозможно выполнить операцию. Хеш-таблица заполнена.\n");
            break;
        case ERR_WRONG_SIZE_FOR_RESTUCT:
            printf("\n[ERR]: Невозможно выполнить операцию. Указан некорректный новый размер для хеш-таблицы.\n");
            break;
        case ERR_LIMIT_OF_COMPARISONS:
            printf("\n[ERR]: Превышен лимит сравнений в хеш-таблице. Реструктурируйте таблицу.\n");
            break;
        case ERR_INVALID_OPERATION:
            printf("\n[ERR]: Указан некорректный номер операции.\n");
            break;
        case ERR_READ_DATA:
            printf("\n[ERR]: Ошибка при чтении данных.\n");
            break;
        case ERR_INVALID_DATA:
            printf("\n[ERR]: Введены некорректные данные.\n");
            break;
        case ERR_TIMER:
            printf("\n[ERR]: Ошибка в работе таймера. Выполните замер времени повторно.\n");
            break;
        
        default:
            printf("\n[ERR]: Неизвестная ошибка.");
            break;
    }
}

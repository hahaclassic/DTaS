#include "errors.h"

void err_message(error_t error) 
{
    switch (error)
    {
    case ERR_WRONG_OPTION:
        printf("[ERR]: Введен неверный номер операции. Повторите попытку: ");
        break;

    case ERR_ARR_SIZE:
        printf("[ERR]: Введен неверный размер очереди.\n");
        break;

    case ERR_MEMORY_ALLOC:
        printf("[ERR]: Ошибка при попытке выделения памяти.\n");
    
    default:
        break;
    }
}

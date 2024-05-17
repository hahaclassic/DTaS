#include "errors.h"


void err_message(int err)
{
    switch (err)
    {
        case STATUS_OK:
            break;
        case ERR_INVALID_ARGS:
            printf("[ERR]: Некорректные параметры запуска.\n");
            break;
        case ERR_FILE_OPEN:
            printf("[ERR]: Ошибка при открытии файла.\n");
            break;
        case ERR_EMPTY_FILE:
            printf("[ERR]: Указан пустой файл.\n");
            break;
        case ERR_READ_DATA:
            printf("[ERR]: Ошибка при попытке чтения данных.\n");
            break;
        case ERR_INCOMPLETE_STRUCT:
            printf("[ERR]: Ошибка при попытке чтения данных. Указана неполная стуктура.\n");
            break;
        case ERR_INVALID_DATA:
            printf("[ERR]: Ошибка при попытке чтения данных. Некорректные данные.\n");
            break;
        case ERR_TOO_MANY_OBJECTS:
            printf("[ERR]: Слишком много объектов в файле.\n");
            break;
        case ERR_NO_DATA:
            printf("[ERR]: В файле нет данных.\n");
            break;
        case ERR_NOT_ENOUGH_SPACE:
            printf("[ERR]: База данных заполнена. Освободите место, чтобы добавить новый автомобиль.\n");
            break;
        case ERR_NO_DATA_WITH_THIS_VALUE:
            printf("[ERR]: Нет автомобилей с указанной ценовой категорией. Удаление невозможно.\n");
            break;
        case ERR_SAVE_DATA:
            printf("[ERR]: Ошибка при попытке сохранить данные.\n");
            break;
        case ERR_EMPTY_SEARCH_RESULT:
            printf("[ERR]: Автомобилей с указанными параметрами не найдено.\n");
            break;
        case ERR_INVALID_USER_DATA:
            printf("[ERR]: Введены некорректные данные.\n");
            break;

        default:
            printf("[ERR]: Неизвестная ошибка.");
            break;
    }
}

#include "errors.h"

void err_message(int err)
{
    switch (err)
    {
    case ERR_READ_INT:
        printf("%s", "[ERR]: Ошибка при чтении целого числа. Некорректный ввод.\n");
        break;

    case ERR_READ_FLOAT:
        printf("%s", "[ERR]: Ошибка при чтении вещественного числа. Некорректный ввод.\n");
        break;

    case ERR_BUFFER_OVERFLOW:
        printf("%s", "[ERR]: Превышено максимально возможное количество разрядов.\n");
        break;

    case ERR_INVALID_CHAR:
        printf("%s", "[ERR]: Ошибка при чтении числа. Некорректный ввод.\n");
        break;

    case ERR_EMPTY_INPUT:
        printf("%s", "[ERR]: Ошибка при чтении числа. Пустой ввод.\n");
        break;

    case ERR_READ_MANTISSA:
        printf("%s", "[ERR]: Ошибка при чтении вещественного числа. Некорректный ввод.\n");
        break;

    case ERR_READ_EXP:
        printf("%s", "[ERR]: Ошибка при чтении вещественного числа. Некорректный ввод.\n");
        break;

    default:
        break;
    }
}

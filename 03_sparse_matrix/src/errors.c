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
        case ERR_READ_DATA:
            printf("[ERR]: Ошибка при попытке чтения данных.\n");
            break;
        case ERR_INCORRECT_MATRIX_SIZES:
            printf("[ERR]: Указаны некорректные размеры.\n");
            break;
        case ERR_NOT_ENOUGH_ELEMENTS:
            printf("[ERR]: В файле указано недостаточное количество элементов.\n");
            break;
        case ERR_MEMORY_ALLOCATION:
            printf("[ERR]: Ошибка при попытке выделения памяти.\n");
            break;
        case ERR_DIFFERENT_MATRIX_SIZES:
            printf("[ERR]: Невозможно выполнить умножение, матрицы имеют некорректные размеры.\n" \
            "Количество столбцов первой матрицы не совпадает с кол-вом строк второй матрицы.\n");
            break;
        default:
            printf("[ERR]: Неизвестная ошибка.");
            break;
    }
}

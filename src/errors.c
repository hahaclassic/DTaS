#include "errors.h"

// Sends an error message to the terminal. 
// If there is no error, it doesn't output anything.

// void err_message(int err)
// {
//     switch (err)
//     {
//         case STATUS_OK:
//             break;
//         case ERR_INCORRECT_ARG:
//             printf("[ERR]: Указаны некорректные аргументы.\n");
//             break;
//         case ERR_FILE_OPEN:
//             printf("[ERR]: Ошибка при открытии файла.\n");
//             break;
//         case ERR_EMPTY_FILE:
//             printf("[ERR]: Указан пустой файл.\n");
//             break;
//         case ERR_READ_DATA:
//             printf("[ERR]: Ошибка при попытке чтения данных.\n");
//             break;
//         case ERR_NO_ELEMENTS:
//             printf("[ERR]: В файле нет элементов.\n");
//             break;
//         case ERR_MEMORY_ALLOCATION:
//             printf("[ERR]: Ошибка при попытке выделения файла.\n");
//             break;
//         case ERR_INVALID_POINTERS:
//             printf("[ERR]: Некорректные указатели на начало и конец массива.\n");
//             break;
//         case ERR_EMPTY_FILTERING_RESULT:
//             printf("[ERR]: Результатом фильтрации является пустой массив.\n");
//             break;

//         default:
//             printf("[ERR]: Неизвестная ошибка.");
//             break;
//     }
// }

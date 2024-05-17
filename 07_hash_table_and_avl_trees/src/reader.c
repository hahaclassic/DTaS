#include "reader.h"
#include <stdio_ext.h>

error_t get_key(char *key)
{
    printf("Введите ключевое слово: ");
    int input = scanf("%s", key);

    if (input != 1)
    {
        return ERR_READ_DATA;
    }
    if (strlen(key) > MAX_KEY_LEN)
    {
        return ERR_INVALID_DATA;
    }

    return STATUS_OK;
}

error_t get_data(char *data)
{
    printf("Введите подсказку для ключевого слова: ");
    char *check = fgets(data, MAX_VALUE_LEN, stdin);
    if (check == NULL)
    {
        return ERR_READ_DATA;
    }
    if (strlen(data) > MAX_VALUE_LEN || data[strlen(data) - 1] != '\n')
    {
        return ERR_INVALID_DATA;
    }
    data[strlen(data) - 1] = '\0';
    
    if (strlen(data) == 0)
    {
        return ERR_INVALID_DATA;
    }
    
    return STATUS_OK;
}

error_t get_key_data(char *key, char *data)
{
    error_t err;
    err = get_key(key);
    if (err)
    {
        return err;
    }
    __fpurge(stdin);
    err = get_data(data);
    if (err)
    {
        return err;
    }
    
    return STATUS_OK;
}

error_t get_table_size(size_t old_size, size_t *new_size)
{
    int new, input;

    printf("\nТекущий размер хеш-таблицы: %zu\n", old_size);
    printf("ОБРАТИТЕ ВНИМАНИЕ: При уменьшении таблицы повышается вероятность коллизий.\n\n");
    printf("Введите новый размер хеш-таблицы: ");
    input = scanf("%d", &new);
    if (input != 1)
    {
        return ERR_READ_DATA;
    }
    if (new <= 0)
    {
        return ERR_INVALID_DATA;
    }

    *new_size = (size_t) new;
    return STATUS_OK;
}

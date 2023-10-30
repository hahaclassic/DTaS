#include "reader.h"

int read_char(FILE *input, char *symbol)
{   
    int s = fgetc(input);
    if (s == EOF)
    {
        return ERR_READ_DATA;
    }

    if (s != '(' && s != ')' && s != '[' && s != ']' && s != '{' && s != '}' && s != '\n')
    {
        return ERR_INCORRECT_DATA;
    }

    *symbol = s;

    return STATUS_OK;
}

int read_str(FILE *file, char *str)
{
    char symbol;
    int err;
    size_t i = 0;

    err = read_char(file, &symbol);
    err = read_char(file, &symbol);

    while (!err && symbol != '\n')
    {
        if (i >= MAX_LEN)
        {
            return ERR_MAX_LEN;
        }
        str[i] = symbol;
        i++;

        err = read_char(file, &symbol);
    }

    if (err == ERR_INCORRECT_DATA)
    {
        return err;
    }
    else if (i == 0 || feof(file))
    {
        return ERR_INCORRECT_DATA;
    }

    str[i] = '\0';
    printf("\n");
    
    return STATUS_OK;
}

int select_operation(int *operation, int *main_operation)
{
    printf("\nВведите номер операции: ");
    int input = scanf("%d", operation);
    if (input != 1)
    {
        return ERR_READ_DATA;
    }
    if (*operation < 1 || *operation > 5)
    {
        return ERR_OPERATION_NUM;
    }

    if (*operation == 1 || *operation == 3)
    {
        *main_operation = 1;
    }
    else if (*operation == 2 || *operation == 4)
    {
        *main_operation = 2;
    }
    else
    {
        *main_operation = 5;
    }

    return STATUS_OK;
}

#include <stdio.h>
#include "errors.h"
#include "type.h"

/*
    Данный модуль отвечает за взаимодействие с пользователем через терминал.
*/

static int get_str(FILE *file, char *str)
{
    char buff[MAX_STR_LEN + 10];
    char *check;

    check = fgets(buff, sizeof(buff), file);
    if (check == NULL || feof(file))
    {
        return ERR_READ_DATA;
    }
    if (strlen(buff) > MAX_STR_LEN + 1 || buff[strlen(buff) - 1] != '\n')
    {
        return ERR_INVALID_DATA;
    }
    buff[strlen(buff) - 1] = '\0';

    check = strncpy(str, buff, MAX_STR_LEN + 1);
    if (check == NULL)
    {   
        return ERR_COPY_DATA;
    }

    return STATUS_OK;
}

// read info from stdin to struct
int read_new_record(car_t *car, int len)
{
    if (len == MAX_NUMBER_OF_RECORDS)
    {
        return ERR_NOT_ENOUGH_SPACE;
    }

    int err, input;

    printf("\nВведите марку автомобиля: ");
    int err = get_str(stdin, car->brand);
    if (err)
    {
        return err;
    }

    printf("Введите страну-производитель: ");
    int err = get_str(stdin, car->country);
    if (err)
    {
        return err;
    }

    printf("Введите цвет автомобиля: ");
    int err = get_str(stdin, car->color);
    if (err)
    {
        return err;
    }

    printf("Введите цену автомобиля: ");
    input = scanf("%d", &car->price);
    if (input != 1 || car->price <= 0)
    {
        return ERR_INVALID_USER_DATA;
    }

    printf("Поддерживается ли обслуживание? (Да - 1 / Нет - 0): ");
    input = scanf("%d", &car->service);
    if (input != 1)
    {
        return ERR_INVALID_USER_DATA;
    }

    printf("Новый автомобиль? (Да - 1 / Нет - 0): ");
    input = scanf("%d", &car->condition);
    if (input != 1)
    {
        return ERR_INVALID_USER_DATA;
    }

    if (!car->condition)
    {
        printf("Введите год выпуска: ");
        input = scanf("%d", &car->old.year);
        if (input != 1 || car->old.year < 1800)
        {
            return ERR_INVALID_USER_DATA;
        }

        printf("Введите пробег (целое кол-во км): ");
        input = scanf("%d", &car->old.mileage);
        if (input != 1 || car->old.mileage < 0)
        {
            return ERR_INVALID_USER_DATA;
        }

        printf("Введите количество ремонтов: ");
        input = scanf("%d", &car->old.repairs);
        if (input != 1 || car->old.repairs < 0)
        {
            return ERR_INVALID_USER_DATA;
        }

        printf("Введите количество владельцев: ");
        input = scanf("%d", &car->old.owners);
        if (input != 1 || car->old.owners < 1)
        {
            return ERR_INVALID_USER_DATA;
        }
    }
    else 
    {
        printf("Введите гаранию (в годах): ");
        input = scanf("%d", &car->guarantee);
        if (input != 1 || car->guarantee < 0) 
        {
            return ERR_INVALID_USER_DATA;
        }
    }
    
    return STATUS_OK;
}

// read value from stdin
int read_value(int *value)
{
    printf("\nВведите цену: ");
    int input = scanf("%d", value);
    if (input != 1) {
        return ERR_INVALID_USER_DATA;
    }

    return STATUS_OK;
}

// Returns index of operations
// int menu()
// {

// }

#include "storage.h"


static int get_str(FILE *file, char *str)
{
    char buff[MAX_STR_LEN + 10];
    char *check;

    check = fgets(buff, sizeof(buff), file);
    if (check == NULL)
    {
        return ERR_READ_DATA;
    }
    if (strlen(buff) > MAX_STR_LEN + 1 || buff[strlen(buff) - 1] != '\n')
    {
        return ERR_INVALID_DATA;
    }
    buff[strlen(buff) - 1] = '\0';

    // if (strlen(buff) == 0) 
    // {
    //     return ERR_READ_DATA;
    // }

    check = strncpy(str, buff, MAX_STR_LEN + 1);
    if (check == NULL)
    {   
        return ERR_COPY_DATA;
    }

    return STATUS_OK;
}

// Reads one object from the file. Returns the error code.
int get_car(FILE *file, car_t *car)
{
    int input;
    int err;

    // Get brand
    err = get_str(file, car->brand);
    if (err)
    {
        if (err == ERR_READ_DATA)
        {
            err = ERR_READ_BEGINNING_OF_STRUCT;
        }
        return err;
    }
    
    // Get country
    err = get_str(file, car->country);
    if (err)
    {
        if (err == ERR_READ_DATA)
        {
            err = ERR_INCOMPLETE_STRUCT;
        }
        return err;
    }

    // Get color
    err = get_str(file, car->color);
    if (err)
    {
        if (err == ERR_READ_DATA)
        {
            err = ERR_INCOMPLETE_STRUCT;
        }
        return err;
    }

    // Get price, service, condition
    int service, condition; 
    input = fscanf(file, "%d\n%d\n%d\n", &car->price, &service, &condition);
    if (input != 3) 
    {
        return ERR_INCOMPLETE_STRUCT;
    }
    if (car->price <= 0 || (service != 0 && service != 1) || (condition != 0 && condition != 1))
    {
        return ERR_INVALID_DATA;
    }
    car->service = service;
    car->condition = condition;

    // Get others fields
    if (!car->condition)
    {
        input = fscanf(file, "%d\n%d\n%d\n%d\n", &car->old.year,
        &car->old.mileage, &car->old.repairs, &car->old.owners);
        if (input != 4) 
        {
            return ERR_INCOMPLETE_STRUCT;
        }
        if (car->old.year < 1800 || car->old.mileage < 0 || car->old.owners < 1 || car->old.repairs < 0)
        {
            return ERR_INVALID_DATA;
        }
    }
    else
    {
        input = fscanf(file, "%d\n", &car->guarantee);
        if (input != 1) 
        {
            return ERR_INCOMPLETE_STRUCT;
        }
        if (car->guarantee < 0)
        {
            return ERR_INVALID_DATA;
        }
    }

    return STATUS_OK;
}

// Reads all objects from the file into an array. Returns the error code.
int get_all(FILE *file, car_t cars[], key_t keys[], int *len)
{
    *len = 0;

    int err = get_car(file, &cars[*len]);
    while (!err)
    {
        keys[*len].index = *len;
        keys[*len].value = cars[*len].price;

        (*len)++;

        if (*len > MAX_NUMBER_OF_RECORDS)
        {
            return ERR_TOO_MANY_OBJECTS;
        }   

        err = get_car(file, &cars[*len]);
    }

    if (err != ERR_READ_BEGINNING_OF_STRUCT)
    {
        return err;
    }

    return STATUS_OK;
}

// Adds 1 record to storage
int add_record(FILE *file, car_t *car)
{
    int input = fprintf(file, "%s\n%s\n%s\n", car->brand, car->country, car->color);
    if (input < 0) {
        return ERR_SAVE_DATA;
    }

    input = fprintf(file, "%d\n%d\n%d\n", car->price, car->service, car->condition);
    if (input < 0) {
        return ERR_SAVE_DATA;
    }

    if (!car->condition)
    {
        input = fprintf(file, "%d\n%d\n%d\n%d\n", car->old.year, car->old.mileage, 
            car->old.repairs, car->old.owners);
        if (input < 0) {
            return ERR_SAVE_DATA;
        }
    }
    else
    {
        input = fprintf(file, "%d\n", car->guarantee);
        if (input < 0) {
            return ERR_SAVE_DATA;
        }
    }

    return STATUS_OK;
}

// Deletes all recors with price == value
int delete_record(FILE *file, car_t cars[], int len, int value)
{
    int count = 0;
    for (int i = 0; i < len; i++)
    {
        if (cars[i].price != value)
        {
            add_record(file, &cars[i]);
            count++;
        }
    }

    if (count == len)
    {
        return ERR_NO_DATA_WITH_THIS_VALUE;
    }

    return STATUS_OK;
}


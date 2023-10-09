#include "writer.h"

void show_car(const void *obj, int index)
{
    const car_t *car = obj;

    printf("%d. %s %s %s ", index, car->brand, car->country, car->color);
    printf("%d %d ", car->price, car->service);

    if (car->condition)
    {
        printf("%d %d %d %d ", car->old.year, car->old.mileage,
         car->old.repairs, car->old.owners);
    }
    else
    {
        printf("%d ", car->guarantee);
    }

    printf("\n");
}

void show_key(const void *obj, int index)
{
    const key_t *key = obj;
    printf("%d. %d %d\n", index, key->index, key->value);
}

void show_table(void *base, size_t len, size_t size, void (*show)(const void*, int))
{   
    char *curr = base;
    char *end = curr + len * size;

    int i = 1;
    for (; curr < end; curr += size) 
    {
        show(curr, i);
        i++;
    }
}

void show_table_with_keys(car_t cars[], key_t keys[], size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        show_car(&cars[keys[i].index], i);
    }
}

void show_spec(car_t cars[], size_t len, char *name)
{
    for (size_t i = 0; i < len; i++)
    {
        if (!cars[i].condition && cars[i].old.owners == 1 && )
    }
}

// void show_message()
// {

// }

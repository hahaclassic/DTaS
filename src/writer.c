#include "writer.h"

void show_car(const void *obj, int index)
{
    const car_t *car = obj;

    printf("| %-5d | %-15s | %-15s | %-15s | %-11d |", index, car->brand, car->country, car->color, car->price);

    if (car->service)
    {
        printf(" %-7c |", '+');
    }
    else
    {
        printf(" %-7c |", '-');
    }

    if (!car->condition)
    {
        printf(" %-9s |", "old");
        printf(" %-9c |", '-');
        printf(" %-4d | %-10d | %-10d | %-10d |", car->old.year, car->old.mileage,
         car->old.repairs, car->old.owners);
    }
    else 
    {
        printf(" %-9s |", "new");
        printf(" %-9d |", car->guarantee);
        printf(" %-4c | %-10c | %-10c | %-10c |", '-', '-', '-', '-');
    }

    printf("\n+-----------------------------------------------------------------------------------------------------------------------------------------------------------+\n");
}

void show_key(const void *obj, int index)
{
    const key_t *key = obj;
    printf(KEYS_FORMAT, index, key->index, key->value);
}

void show_table(void *base, size_t len, size_t size, char *header, void (*show)(const void*, int))
{   
    printf("%s", header);
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
    printf("%s", CARS_HEADER);
    for (size_t i = 0; i < len; i++)
    {
        show_car(&cars[keys[i].index], i + 1);
    }
}

int show_spec(car_t cars[], size_t len, int min_price, int max_price, char *name)
{
    int k = 0;
    for (size_t i = 0; i < len; i++)
    {
        if (!cars[i].condition && cars[i].old.owners == 1 
            && cars[i].price <= max_price && cars[i].price >= min_price
            && cars[i].old.repairs == 0 && cars[i].service 
            && strcmp(name, cars[i].brand) == 0 
            && strcmp(cars[i].country, "Russia") != 0 && strcmp(cars[i].country, "russia") != 0)
        {
            k++;
            if (k == 1)
            {
                printf("%s", CARS_HEADER);
            }
            show_car(&cars[i], k);
        }
    }

    if (k == 0)
    {
        return ERR_EMPTY_SEARCH_RESULT;
    }

    return STATUS_OK;
}


void show_stats(stat_t *stats, int len)
{
    printf("\n=================================================================================\n");
    printf("Сравнение эффективности сортировки данных с помощью quick_sort и selection_sort\n");
    printf("при использовании таблицы ключей и без нее (При len = %d).\n\n", len);
    printf("Данные приведены в микросекундах (время) и байтах (пямять).\n");
    printf("---------------------------------------------------------------------------------\n");

    printf("Исходная таблица:\n");
    printf("\t- quick_sort time: %lld мкс\n\t- selection_sort time: %lld мкс\n\t- memory: %d байт\n", stats->qsort_cars_time, stats->ssort_cars_time, stats->cars_mem);
    printf("Таблица ключей:\n");
    printf("\t- quick_sort time: %lld мкс\n\t- selection_sort time: %lld мкс\n\t- memory: %d байт\n", stats->qsort_keys_time, stats->ssort_keys_time, stats->keys_mem);

    printf("---------------------------------------------------------------------------------");

    float gain_time, gain_mem;

    printf("\nquick_sort:\n\t");
    if (stats->qsort_cars_time == 0 || stats->qsort_keys_time == 0)
    {
        printf("- Процентное соотношение не может быть вычислено.\n");
    } 
    else if (stats->qsort_keys_time < stats->qsort_cars_time)
    {
        gain_time = (float) (stats->qsort_cars_time - stats->qsort_keys_time) / (float) stats->qsort_keys_time * 100;
        printf("- Сортировка таблицы ключей быстрее, чем сортировка исходной на %f%%\n", gain_time);
    }
    else if (stats->qsort_keys_time > stats->qsort_cars_time)
    {
        gain_time = (float) (stats->qsort_keys_time - stats->qsort_cars_time) / (float) stats->qsort_cars_time * 100;
        printf("- Сортировка исходной таблицы быстрее, чем сортировка таблицы ключей на %f%%\n", gain_time);
    }
    else
    {
        printf("- Сортировки исходной таблицы и таблицы ключей равны по времени\n");
    }

    printf("selection_sort:\n\t");
    if (stats->ssort_cars_time == 0 || stats->ssort_keys_time == 0)
    {
        printf("- Процентное соотношение не может быть вычислено.\n");
    } 
    else if (stats->ssort_keys_time < stats->ssort_cars_time)
    {
        gain_time = (float) (stats->ssort_cars_time - stats->ssort_keys_time) / (float) stats->ssort_keys_time * 100;
        printf("- Сортировка таблицы ключей быстрее, чем сортировка исходной на %f%%\n", gain_time);
    }
    else if (stats->ssort_keys_time > stats->ssort_cars_time)
    {
        gain_time = (float) (stats->ssort_keys_time - stats->ssort_cars_time) / (float) stats->ssort_cars_time * 100;
        printf("- Сортировка исходной таблицы быстрее, чем сортировка таблицы ключей на %f%%\n", gain_time);
    }
    else
    {
        printf("- Сортировки исходной таблицы и таблицы ключей равны по времени\n");
    }


    printf("memory:\n\t");
    if (stats->cars_mem == 0 || stats->keys_mem == 0)
    {
        printf("- Процентное соотношение не может быть вычислено.\n");
    } 
    else if (stats->cars_mem < stats->keys_mem)
    {
        gain_mem = (float) (stats->keys_mem - stats->cars_mem) / (float) stats->cars_mem * 100;
        printf("- Сортировка таблицы ключей использует на %f%% больше памяти.\n", gain_mem);
    }
    else if (stats->cars_mem > stats->keys_mem)
    {
        gain_mem = (float) (stats->cars_mem - stats->keys_mem) / (float) stats->keys_mem * 100;
        printf("- Сортировка исходной таблицы использует на %f%% больше памяти.\n", gain_mem);
    }
    else
    {
        printf("- Сортировки исходной таблицы и таблицы ключей равны по памяти\n");
    }
    printf("---------------------------------------------------------------------------------\n");


    printf("Сортировка исходной таблицы:\n\t");
    if (stats->qsort_cars_time == 0 || stats->ssort_cars_time == 0)
    {
        printf("- Процентное соотношение не может быть вычислено.\n");
    } 
    else if (stats->ssort_cars_time > stats->qsort_cars_time)
    {
        gain_time = (float) (stats->ssort_cars_time - stats->qsort_cars_time) / (float) stats->qsort_cars_time * 100;
        printf("- quick_sort быстрее selection_sort на %f%%\n", gain_time);
    }
    else if (stats->ssort_cars_time < stats->qsort_cars_time)
    {
        gain_time = (float) (stats->qsort_cars_time - stats->ssort_cars_time) / (float) stats->ssort_cars_time * 100;
        printf("- selection_sort быстрее quick_sort на %f%%\n", gain_time);
    }
    else
    {
        printf("- quick_sort и selection_sort равны по времени.\n");
    } 

    printf("Сортировка таблицы ключей:\n\t");
    if (stats->qsort_keys_time == 0 || stats->ssort_keys_time == 0)
    {
        printf("- Процентное соотношение не может быть вычислено.\n");
    } 
    else if (stats->ssort_keys_time > stats->qsort_keys_time)
    {
        gain_time = (float) (stats->ssort_keys_time - stats->qsort_keys_time) / (float) stats->qsort_keys_time * 100;
        printf("- quick_sort быстрее selection_sort на %f%%\n", gain_time);
    }
    else if (stats->ssort_keys_time < stats->qsort_keys_time)
    {
        gain_time = (float) (stats->qsort_keys_time - stats->ssort_keys_time) / (float) stats->ssort_keys_time * 100;
        printf("- selection_sort быстрее quick_sort на %f%%\n", gain_time);
    }
    else
    {
        printf("- quick_sort и selection_sort равны по времени.\n");
    }
    printf("=================================================================================\n");
}


void show_result(car_t cars[], key_t keys[], int len, int mode) 
{
    switch (mode)
    {
        case SHOW_CARS:
            show_table(cars, len, sizeof(car_t), CARS_HEADER, show_car);
            break;

        case SHOW_CARS_WITH_KEYS:
            show_table_with_keys(cars, keys, len);
            break;

        case SHOW_KEYS:
            show_table(keys, len, sizeof(key_t), KEYS_HEADER, show_key);
            break;
    }
}

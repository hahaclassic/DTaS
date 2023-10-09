#include "interface.h"
#include "errors.h"
#include "type.h"
#include "storage.h"
#include "sort.h"
#include "writer.h"


int main() 
{
    int err;
    FILE *file;
    char file_path[] = "./data/cars.txt";

    int len;
    car_t cars[MAX_NUMBER_OF_RECORDS + 1];
    key_t keys[MAX_NUMBER_OF_RECORDS + 1];
    key_t keysB[MAX_NUMBER_OF_RECORDS + 1];
    car_t carsB[MAX_NUMBER_OF_RECORDS + 1];

    // Открытие файла для получения данных.
    file = fopen(file_path, "r");
    if (file == NULL)
    {
        return ERR_FILE_OPEN;
    }

    // Чтение данных в массивы стуктур.
    err = get_all(file, cars, keys, &len);
    fclose(file);
    if (err)
    {   
        return err;
    }

    // Выбор операции
    int operation = 5; // menu();

    switch (operation)
    {
    case ADD_RECORD:
        file = fopen(file_path, "a");
        if (file == NULL)
        {
            return ERR_FILE_OPEN;
        }

        car_t car;
        err = read_new_record(&car, len);
        if (err)
        {
            fclose(file);
            return err;
        }
        add_record(file, &car);
        break;

    case DELETE_RECORD:

        if (len == 0)
        {
            return ERR_NO_DATA;
        }

        file = fopen(file_path, "w");
        if (file == NULL)
        {
            return ERR_FILE_OPEN;
        }

        int value;
        err = read_value(&value);
        if (err)
        {
            fclose(file);
            return err;
        }

        err = delete_record(file, cars, len, value);
        if (err)
        {
            fclose(file);
            return err;
        }

        break;

    case SORT_KEYS:
        if (len == 0)
        {
            return ERR_NO_DATA;
        }
        
        copy(keys, keysB, sizeof(key_t), len);

        quick_sort(keys, len, sizeof(key_t), compare_key_t);

        selection_sort(keysB, len, sizeof(key_t), compare_key_t);

        show_table(keys, len, sizeof(key_t), show_key);
        break;

    case SORT_TABLE:

        if (len == 0)
        {
            return ERR_NO_DATA;
        }

        copy(cars, carsB, sizeof(car_t), len);

        quick_sort(cars, len, sizeof(car_t), compare_car_t);

        selection_sort(carsB, len, sizeof(car_t), compare_car_t);    

        show_table(cars, len, sizeof(car_t), show_car);
        break;     

    case STATS:

        if (len == 0)
        {
            return ERR_NO_DATA;
        }

        copy(cars, carsB, sizeof(car_t), len);
        copy(keys, keysB, sizeof(car_t), len);

        quick_sort(keys, len, sizeof(key_t), compare_key_t);

        selection_sort(keysB, len, sizeof(key_t), compare_key_t);
        
        quick_sort(cars, len, sizeof(car_t), compare_car_t);

        selection_sort(carsB, len, sizeof(car_t), compare_car_t);

        // show_stats()
        break;

    case SHOW_SOURCE_TABLES:
        
        show_table(cars, len, sizeof(car_t), show_car);
        show_table(keys, len, sizeof(key_t), show_key);

        break;
    }

    return STATUS_OK;
}
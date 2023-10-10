#include "interface.h"
#include "errors.h"
#include "type.h"
#include "storage.h"
#include "sort.h"
#include "writer.h"
#include "timer.h"

int main(int argc, char **argv) 
{
    if (argc != 2)
    {
        err_message(ERR_INVALID_ARGS);
        return ERR_INVALID_ARGS;
    }

    int err;
    FILE *file;
    //char file_path[] = "./data/cars.txt";

    int len;
    car_t cars[MAX_NUMBER_OF_RECORDS + 1];
    key_t keys[MAX_NUMBER_OF_RECORDS + 1];
    key_t keysB[MAX_NUMBER_OF_RECORDS + 1];
    car_t carsB[MAX_NUMBER_OF_RECORDS + 1];

    int min_price, max_price;
    char brand[MAX_STR_LEN + 1];

    // Открытие файла для получения данных.
    file = fopen(argv[1], "r");
    if (file == NULL)
    {
        err_message(ERR_FILE_OPEN);
        return ERR_FILE_OPEN;
    }

    // Чтение данных в массивы стуктур.
    err = get_all(file, cars, keys, &len);
    fclose(file);
    if (err)
    {   
        err_message(err);
        return err;
    }

    // Выбор операции
    int operation;
    err = menu(&operation);
    if (err)
    {
        err_message(err);
        return err;
    }

    switch (operation)
    {
    case ADD_RECORD:
        file = fopen(argv[1], "a");
        if (file == NULL)
        {
            err_message(ERR_FILE_OPEN);
            return ERR_FILE_OPEN;
        }

        car_t car;
        err = get_new_record(&car, len);
        if (err)
        {
            fclose(file);
            err_message(err);
            return err;
        }
        err = add_record(file, &car);
        if (err)
        {
            fclose(file);
            err_message(err);
            return err;
        }
        message_ok(ADD_RECORD);
        break;

    case DELETE_RECORD:

        if (len == 0)
        {
            err_message(ERR_NO_DATA);
            return ERR_NO_DATA;
        }

        int value;
        err = read_value(&value);
        if (err)
        {
            err_message(err);
            return err;
        }

        file = fopen(argv[1], "w");
        if (file == NULL)
        {
            err_message(ERR_FILE_OPEN);
            return ERR_FILE_OPEN;
        }

        err = delete_record(file, cars, len, value);
        if (err)
        {
            fclose(file);
            err_message(err);
            return err;
        }
        message_ok(DELETE_RECORD);
        break;

    case SORT_KEYS:
        if (len == 0)
        {
            err_message(ERR_NO_DATA);
            return ERR_NO_DATA;
        }

        quick_sort(keys, len, sizeof(key_t), compare_key_t);
        message_ok(SORT_KEYS);
        
        err = result_menu(&operation);
        if (err)
        {
            err_message(err);
            return err;
        }
        show_result(cars, keys, len, operation);

        break;

    case SORT_TABLE:

        if (len == 0)
        {
            err_message(ERR_NO_DATA);
            return ERR_NO_DATA;
        }

        quick_sort(cars, len, sizeof(car_t), compare_car_t); 
        message_ok(SORT_TABLE);
        
        err = result_menu(&operation);
        if (err)
        {
            err_message(err);
            return err;
        }
        show_result(cars, keys, len, operation);

        break;     

    case STATS:

        if (len == 0)
        {
            err_message(ERR_NO_DATA);
            return ERR_NO_DATA;
        }

        copy(cars, carsB, sizeof(car_t), len);
        copy(keys, keysB, sizeof(car_t), len);

        stat_t stats;
        stats.cars_mem = len * sizeof(car_t);
        stats.keys_mem = len * (sizeof(car_t) + sizeof(key_t));

        unsigned long long start, end;

        // The first measurement of time
        int err1 = microseconds_now(&start);
        quick_sort(keys, len, sizeof(key_t), compare_key_t);
        int err2 = microseconds_now(&end);

        if (err1 || err2)
        {
            err_message(err);
            return ERR_TIMER;
        }
        stats.qsort_keys_time = end - start;

        // The second measurment of time
        err1 = microseconds_now(&start);
        selection_sort(keysB, len, sizeof(key_t), compare_key_t);
        err2 = microseconds_now(&end);

        if (err1 || err2)
        {
            err_message(err);
            return ERR_TIMER;
        }
        stats.ssort_keys_time = end - start;

        // The 3rd measurment of time
        err1 = microseconds_now(&start);
        quick_sort(cars, len, sizeof(car_t), compare_car_t);
        err2 = microseconds_now(&end);

        if (err1 || err2)
        {
            err_message(err);
            return ERR_TIMER;
        }
        stats.qsort_cars_time = end - start;

        // The 4th measurment of time
        err1 = microseconds_now(&start);
        selection_sort(carsB, len, sizeof(car_t), compare_car_t);
        err2 = microseconds_now(&end);

        if (err1 || err2)
        {
            err_message(err);
            return ERR_TIMER;
        }
        stats.ssort_cars_time = end - start;

        show_stats(&stats, len);
        break;

    case SEARCH:
        
        if (len == 0)
        {
            err_message(ERR_NO_DATA);
            return ERR_NO_DATA;
        }

        err = get_search_data(&min_price, &max_price, brand);
        if (err)
        {
            err_message(err);
            return err;
        }

        err = show_spec(cars, len, min_price, max_price, brand);
        if (err)
        {
            err_message(err);
            return err;
        }
        break;

    case SHOW_SOURCE_CARS:

        if (len == 0)
        {
            err_message(ERR_NO_DATA);
            return ERR_NO_DATA;
        }
        
        show_table(cars, len, sizeof(car_t), CARS_HEADER, show_car);
        break;
    
    case SHOW_SOURCE_KEYS:

        if (len == 0)
        {
            err_message(ERR_NO_DATA);
            return ERR_NO_DATA;
        }

        show_table(keys, len, sizeof(key_t), KEYS_HEADER, show_key);
        break;
    }

    return STATUS_OK;
}

#include "interface.h"

/*
    Данный модуль отвечает за взаимодействие с пользователем через терминал.
*/

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

    if (strlen(buff) == 0) 
    {
        return ERR_READ_DATA;
    }

    check = strncpy(str, buff, MAX_STR_LEN + 1);
    if (check == NULL)
    {   
        return ERR_COPY_DATA;
    }

    return STATUS_OK;
}

// read info from stdin to struct
int get_new_record(car_t *car, int len)
{
    if (len == MAX_NUMBER_OF_RECORDS)
    {
        return ERR_NOT_ENOUGH_SPACE;
    }

    int err, input, temp;

    printf("\n=================================================================================\n");
    printf("Добавление нового автомобиля\n");
    printf("---------------------------------------------------------------------------------\n");

    printf("Введите марку автомобиля: ");
    err = get_str(stdin, car->brand);
    if (err)
    {
        return ERR_INVALID_USER_DATA;
    }

    printf("Введите страну-производитель: ");
    err = get_str(stdin, car->country);
    if (err)
    {
        return ERR_INVALID_USER_DATA;
    }

    printf("Введите цвет автомобиля: ");
    err = get_str(stdin, car->color);
    if (err)
    {
        return ERR_INVALID_USER_DATA;
    }

    printf("Введите цену автомобиля (целое число, $): ");
    input = scanf("%d", &car->price);
    if (input != 1 || car->price <= 0)
    {
        return ERR_INVALID_USER_DATA;
    }

    printf("Поддерживается ли обслуживание? (Да - 1 / Нет - 0): ");
    input = scanf("%d", &temp);
    if (input != 1 || (temp != 1 && temp != 0))
    {
        return ERR_INVALID_USER_DATA;
    }
    car->service = (bool) temp;

    printf("Новый автомобиль? (Да - 1 / Нет - 0): ");
    input = scanf("%d", &temp);
    if (input != 1 || (temp != 1 && temp != 0))
    {
        return ERR_INVALID_USER_DATA;
    }
    car->condition = (bool) temp;

    if (!car->condition)
    {
        printf("Введите год выпуска: ");
        input = scanf("%d", &car->old.year);
        if (input != 1 || car->old.year < 1800 || car->old.year > 2023)
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
    printf("\n=================================================================================\n");
    printf("Удаление автомобилей из указанной ценовой категории\n");
    printf("---------------------------------------------------------------------------------\n");
    printf("Введите цену (целое число, $): ");
    int input = scanf("%d", value);
    if (input != 1) {
        return ERR_INVALID_USER_DATA;
    }

    return STATUS_OK;
}

// Get search data from stdin
int get_search_data(int *min_price, int *max_price, char *brand)
{   
    printf("\n=================================================================================\n");
    printf("Поиск старых иномарок\n");
    printf("---------------------------------------------------------------------------------\n");
    printf("Введите марку автомобиля: ");
    int err = get_str(stdin, brand);
    if (err)
    {
        return ERR_INVALID_USER_DATA;
    }

    printf("Введите диапазон цен в долларах в формате '1000 2000' (где первое число - min, а второе - max): ");
    int input = scanf("%d %d", min_price, max_price);
    if (input != 2 || *min_price > *max_price || *min_price < 0) {
        return ERR_INVALID_USER_DATA;
    }

    return STATUS_OK;
}

void message_ok(int mode)
{   
    printf("---------------------------------------------------------------------------------");
    switch (mode)
    {
    case ADD_RECORD:
        printf("\nЗапись добавлена успешно.\n");
        break;

    case DELETE_RECORD:
        printf("\nЗаписи с указанными параметрами удалены успешно.\n");
        break;

    case SORT_KEYS:
        printf("\nТаблица ключей отсортирована успешно.\n");
        break;

    case SORT_TABLE:
        printf("\nИсходная таблица отсортирована успешно.\n");
        break;
    }
}


// getting index of operations
int menu(int *operation)
{
    printf("=================================================================================\n");
    printf("Программа для работы с данными oб автомобилях, имеющихся в магазине.\n");
    printf("Программа позволяет добавлять, удалять, сортировать данные и производить поиск\nпо определенным критериям.\n");
    printf("---------------------------------------------------------------------------------\n");
    printf("Список команд:\n");
    printf("\t1. Добавить новый автомобиль\n");
    printf("\t2. Удалить автомибили с указанной ценовой категорией из базы данных\n");
    printf("\t3. Отсортировать таблицу ключей\n");
    printf("\t4. Отсортировать исходную таблицу\n");
    printf("\t5. Проанализировать эффективность сортировки исходной таблицы\n\tи таблицы ключей с помощью quick_sort и selection_sort\n");
    printf("\t6. Найти старые иномарки с 1 владельцем, без ремонта, с поддержанием\n\tобслуживания (марка и диапазон цен задаются пользователем)\n");
    printf("\t7. Вывести исходную таблицу\n");
    printf("\t8. Вывести исходную таблицу ключей\n");
    printf("---------------------------------------------------------------------------------\n");
    
    printf("Введите номер команды: ");
    int input = scanf("%d", operation);
    if (input != 1 || *operation > 8 || *operation < 1)
    {
        return ERR_INVALID_USER_DATA;
    }

    char ch = getchar();
    if (ch != '\n')
    {
        return ERR_INVALID_USER_DATA;
    }
   
    return STATUS_OK;
}


// getting index of result operation
int result_menu(int *operation)
{
    printf("---------------------------------------------------------------------------------\n");
    printf("Какие данные вы хотите вывести? \n");
    printf("\t1. Таблицу автомобилей\n");
    printf("\t2. Таблицу ключей\n");
    printf("\t3. Таблицу автомобилей с помощью таблицы ключей\n");
    printf("---------------------------------------------------------------------------------\n");

    printf("Введите номер от 1 до 3: ");
    int input = scanf("%d", operation);
    if (input != 1 || *operation > 3 || *operation < 1)
    {
        return ERR_INVALID_USER_DATA;
    }

    return STATUS_OK;
}

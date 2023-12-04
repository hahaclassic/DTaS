#include "interface.h"

void print_range(time_range_t *T, int i)
{
    printf("%sT%d:%s от %s%.2lf%s до %s%.2lf%s е.в.\n", KBWHT, i, KNRM, KBLU, T->min, KNRM, KBLU, T->max, KNRM);
}

void input_range(time_range_t *T, int i)
{
    do
    {
        printf("\nВведите T%d_min T%d_max значения через пробел: ", i, i);
        fflush(stdin);
    }
    while (scanf("%lf %lf", &(T->min), &(T->max)) != 2);
}

error_t input_values(int *n, int *log_flag, int *log_interval, ranges_t *ranges)
{
    do
    {
        printf("\nВведите количество заявок для обслуживания: "); //Input stop queue1_out value:
        fflush(stdin);
    }
    while (scanf("%d", n) != 1 || *n <= 0);

//    if (*n > MAX_LEN)
//        return ERR_ARR_SIZE;

    do
    {
        printf("\nПоказывать логи? 1/0: ");
        fflush(stdin);
    }
    while (scanf("%d", log_flag) != 1 || (*log_flag != 1 && *log_flag != 0));

    if (*log_flag) 
    {
        do {
            printf("\nПоказывать логи каждые n обработанных заявок. Введите n: ");
            fflush(stdin);
        }
        while (scanf("%d", log_interval) != 1 || *log_interval <= 0);
    }

    int flag = 0;
    do
    {
        printf("\nВнести изменения во временные диапазоны? 1/0: ");
        fflush(stdin);
    }
    while (scanf("%d", &flag) != 1 || (flag != 1 && flag != 0));

    if (flag)
    {
        input_range(&ranges->t1, 1);
        input_range(&ranges->t2, 2);
        input_range(&ranges->t3, 3);
        input_range(&ranges->t4, 4);
    }
    return STATUS_OK;
}

void print_values(int n, int log_flag, int log_interval, ranges_t *ranges)
{
    printf("\nКоличество заявок для обслуживания: %s%d%s.\n", KBLU, n, KNRM);

    if (log_flag)
        printf("Покзывать логи каждые %s%d%s обработанных заявок.\n", KBLU, log_interval, KNRM);
    else
        printf("Отображение логов не задано.\n");

    print_range(&ranges->t1, 1);
    print_range(&ranges->t2, 2);
    print_range(&ranges->t3, 3);
    print_range(&ranges->t4, 4);
}

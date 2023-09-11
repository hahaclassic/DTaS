
#define MAX_MANTISSA 40 // Максимальное количество рязрядов в мантисее
#define MAX_EXP 5 // Максимальное количество разрядов в порядке
#define MAX_INT 8 // Максимальное кол-во разрядов в целом числе 
#define MAX_FLOAT 10 // Количество разбиений для представления 50-значного числа

#define TRUE 1
#define FALSE 0

#ifndef big_int
typedef int big_int[MAX_INT + 1];
#endif

#ifndef big_float
struct big_float
{
    char mantissa_sign; 
    int mantissa[MAX_FLOAT];
    char exp_sign; 
    int exp[MAX_EXP];
};
#endif

void zero_big_int(big_int num);



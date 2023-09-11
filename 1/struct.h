
#define MAX_MANTISSA 40 // Максимальное количество рязрядов в мантисее
#define MAX_EXP 5 // Максимальное количество разрядов в порядке
#define MAX_INT 10 // Максимальное кол-во разрядов в целом числе 
#define MAX_FLOAT 13 // Количество разбиений для представления 50-значного числа

#define TRUE 1
#define FALSE 0

#ifndef big_int
struct big_int
{
    char sign;
    int num[MAX_INT];
};
#endif

#ifndef big_float
struct big_float
{
    char mantissa_sign; 
    int mantissa[MAX_FLOAT];
    char point; 
    char exp_sign; 
    int exp;
};  
#endif

void zero_big_int(struct big_int *val);

void zero_big_float(struct big_float *val);

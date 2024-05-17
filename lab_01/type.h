#include <stdbool.h>

#define MAX_EXP 5 // Максимальное количество разрядов в порядке
#define MAX_DIGITS_COUNT 10 // Количество количество разрядов в мантиссе в 10000-чной С/С
#define MAX_DIGIT_LEN 4

#define MAX_DIGIT_NUM 10000
#define MAX_EXP_NUM 99999
#define MAX_MANTISSA 40 // Максимальная длина мантиссы
#define MAX_FLOAT_MANTISSA 30
#define MAX_INT_LEN 1 + MAX_MANTISSA // Максимальная длина целого числа
#define MAX_FLOAT_LEN 1 + MAX_MANTISSA + 1 + 1 + MAX_EXP // Максимальная длина вещественного числа

#ifndef BIG_FLOAT_NUM
typedef struct
{
    int mantissa[MAX_DIGITS_COUNT];
    bool mantissa_sign;
    int len;
    int exp;
} big_float;  
#define BIG_FLOAT_NUM
#endif

void init_bigfloat(big_float *val);

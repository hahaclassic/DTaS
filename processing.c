#include "processing.h"
#include <stdio.h>

int pow_num(int num, int exp)
{
    int result = 1;
    for (int i = 0; i < exp; i++)
    {
        result *= num;
    }
    
    return result;
}


// Переполнения быть не может
void multiply_mant(int mantissa[], int len, int x)
{
    int buffer = 0;
    for (int i = 0; i < len; i++)
    {
        mantissa[i] = mantissa[i] * x + buffer;
        buffer = mantissa[i] / MAX_DIGIT_NUM;
        mantissa[i] %= MAX_DIGIT_NUM;
    }
}


void shift_mantissa(int mantissa[], int *len, int offset)
{
    // Delete trailling zeros
    // for (int i = 0; i < *len; i++)
    // {
    //     if (mantissa[i] != 0)
    //     {
    //         break;
    //     }
    //     offset++;
    // }

    for (int i = 0; i + offset < *len; i++)
    {
        mantissa[i] = mantissa[i + offset];
    }

    (*len) -= offset;
}

int get_offset(int num)
{
    int base = 1000;
    int count = 0;
    while (base > 0 && num / base == 0)
    {
        base /= 10;
        count++;
    }
    
    return pow_num(10, count);
}

void round_mant(int mantissa[], int *len)
{
    int offset = get_offset(mantissa[*len - 1]);

    multiply_mant(mantissa, *len, offset);

    int extra = *len - MAX_DIGITS_COUNT;
    if (mantissa[extra - 1] / 1000 < 5)
    {   
        shift_mantissa(mantissa, len, extra);
        return;
    }

    for (int i = extra; i < *len; i++)
    {
        if (mantissa[i] + 1 == MAX_DIGIT_NUM)
        {
            mantissa[i] = 0;
            extra++;
        }
        else
        {
            mantissa[i]++;
            break;
        }
    }

    if (mantissa[*len - 1] == 0) 
    {
        mantissa[*len] = 1;
        (*len)++;
        shift_mantissa(mantissa, len, extra + 1);
    }
    else 
    {
        shift_mantissa(mantissa, len, extra);
    }
}


void zero_mant(int mant[], int len) 
{
    for (int i = 0; i < len; i++)
    {
        mant[i] = 0;
    }
}


int count_digits(int mantissa[], int len)
{
    int count = (len - 1) * 4;
    
    if (mantissa[len-1] >= 1000)
    {
        count += 4;
    } 
    else if (mantissa[len - 1] >= 100)
    {
        count += 3;
    }
    else if (mantissa[len - 1] >= 10)
    {
        count += 2;
    }
    else
    {
        count++;
    }

    return count;
}

// Multiply
int multiply(big_float *a, big_float *b, big_float *result)
{
    init_bigfloat(result);

    if ((a->mantissa_sign && !b->mantissa_sign) || (!a->mantissa_sign && b->mantissa_sign))
    {
        result->mantissa_sign = false;
    }
    else 
    {
        result->mantissa_sign = true;
    }
    
    int buffer;
    int mantissa[MAX_DIGITS_COUNT * 2]; // Неокругленная мантисса
    int len = a->len + b->len;
    zero_mant(mantissa, MAX_DIGITS_COUNT * 2);

    for (int i = 0; i < b->len; i++)
    {
        buffer = 0;
        int j = 0;
        for (; j < a->len; j++) 
        {
            mantissa[i + j] += a->mantissa[j] * b->mantissa[i] + buffer;
            buffer = mantissa[i + j] / MAX_DIGIT_NUM;
            mantissa[i + j] %= MAX_DIGIT_NUM;
        }

        if (buffer > 0) 
        {
            mantissa[i + j] += buffer;
        }

    }

    // вывод
    // for (int i = len - 1; i >= 0; i--)
    // {
    //     printf("%d ", mantissa[i]);
    // }
    // printf("\n");

    // Округление
    if (len > MAX_DIGITS_COUNT)
    {
        round_mant(mantissa, &len);
    }

    if (mantissa[len - 1] == 0) {
        len--;
    }
    

    // Приведение порядка
    result->exp = a->exp + b->exp;
    int predict = count_digits(a->mantissa, a->len) + count_digits(b->mantissa, b->len);
    result->exp -= predict - count_digits(mantissa, len);

    if (result->exp > MAX_EXP_NUM)
    {
        return ERR_INF;
    } 
    else if (result->exp < -MAX_EXP_NUM)
    {
        return ERR_MACHINE_ZERO;
    }


    // Копирование значений
    for (int i = 0; i < len; i++)
    {
        result->mantissa[i] = mantissa[i];
    }
    result->len = len;

    // вывод
    // for (int i = len - 1; i >= 0; i--)
    // {
    //     printf("%d ", mantissa[i]);
    // }
    // printf("\n");

    return 0;
}

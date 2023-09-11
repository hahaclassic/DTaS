#include "struct.h"

void zero_big_int(struct big_int *val)
{   
    for (int i = 0; i < MAX_INT; i++)
    {
        val->num[i] = 0;
    }
}

void zero_big_float(struct big_float *val)
{   
    for (int i = 0; i < MAX_FLOAT; i++)
    {
        val->mantissa[i] = 0;
    }

    val->exp = 0;
    val->point = 0;
}

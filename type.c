#include "type.h"


void init_bigfloat(big_float *val)
{

    for (int i = 0; i < MAX_DIGITS_COUNT; i++)
    {
        val->mantissa[i] = 0;
    }

    val->exp = 0;
    val->mantissa_sign = true;
}

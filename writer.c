#include "writer.h"


void print_result(big_float *num) 
{
    printf("\nРезультат: ");
    if (num->mantissa_sign) 
    {
        printf("+");
    }
    else
    {
        printf("-");
    }
    
    printf("0.");

    printf("%d", num->mantissa[num->len-1]);
    for (int i = num->len - 2; i >= 0; i--)
    {
        if (num->mantissa[i] / 1000 == 0)
        {
            printf("0");
        }
        if (num->mantissa[i] / 100 == 0)
        {
            printf("0");
        }
        if (num->mantissa[i] / 10 == 0)
        {
            printf("0");
        }
        
        printf("%d", num->mantissa[i]);
    }

    printf("E");

    if (num->exp >= 0)
    {
        printf("+");
    }

    printf("%d\n", num->exp);
}

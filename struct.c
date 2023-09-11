#include "struct.h"

void zero_big_int(big_int num)
{   
    for (int i = 0; i < MAX_INT; i++)
    {
        num[i] = 0;
    }
}

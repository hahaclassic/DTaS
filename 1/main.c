#include "reader.h"

int main() 
{
    int err;

    struct big_int num;
    zero_big_int(&num);

    struct big_float divider;
    zero_big_float(&divider);

    err = read_data(&num, &divider);

    //err = divide_num();

    //print_num();

    return err;
}
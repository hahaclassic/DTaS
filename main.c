#include "reader.h"
#include "writer.h"
#include "processing.h"

int main() 
{
    show_menu();

    int err;
    big_float num1, num2, result;

    err = read_data(&num1, &num2);
    if (err)
    {
        err_message(err);
        return err;
    }

    // print_result(&num1);
    // print_result(&num2);

    err = multiply(&num1, &num2, &result);
    if (err == ERR_MACHINE_ZERO)
    {
        printf("\nРезультат: Машинный нуль.\n");
    } 
    else if (err == ERR_INF)
    {
        printf("\nРезультат: Машинная бесконечность.\n");
    }
    else
    {
        print_result(&result);
    }

    return STATUS_OK;;
}

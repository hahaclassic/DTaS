#include "errors.h"
#include "interface.h"
#include "list_queue.h"
#include "array_queue.h"
#include <stdio_ext.h>


int main(void)
{
    int log = 1;
    int log_interval = 100;
    int n = 1000;
    ranges_t ranges = {
        .t1 = {1, 5},
        .t2 = {0, 3},
        .t3 = {0, 4},
        .t4 = {0, 1},
    };

    int option = -1, rc;
    srand(time(NULL));
    while (option)
    {
        printf(OPTIONS);
        if (scanf("%d", &option) != 1 || option < 0 || option > 4)
        {
            err_message(ERR_WRONG_OPTION);
            __fpurge(stdin);
        }

        switch (option)
        {
            case 0:
                break;
            case 1:
                if (input_values(&n,  &log, &log_interval, &ranges))
                    err_message(ERR_ARR_SIZE); 
                break;
            case 2:
                print_values(n, log, log_interval, &ranges);
                break;
            case 3:
                if ((rc = option_array(n, log, log_interval, &ranges)))
                {
                    err_message(rc); 
                    return rc;
                }
                break;
            case 4:
                if ((rc = option_list(n, log, log_interval, &ranges)))
                {
                    err_message(rc); 
                    return rc;
                }
                break;
            default:
                break;
        }
    }

    return STATUS_OK;
}

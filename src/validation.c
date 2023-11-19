#include "validation.h"

// Checks the correctness of the specified arguments
int check_args(int argc, char **argv, int *operation)
{
    if (argc < 3 || argc > 4)
    {
        return ERR_INCORRECT_ARG;
    }

    if (argc == 3)
    {
        *operation = SORT;
    }
    else if (!strcmp(argv[3], "ALL"))
    {
        *operation = PRINT_ALL;
    } 
    else 
    {
        *operation = FIND;
    } 
    
    return STATUS_OK;
}

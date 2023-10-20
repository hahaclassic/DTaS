#include "validation.h"

// Checks the correctness of the specified arguments
int check_args(int argc, char **argv, int *operation)
{
    if (argc < 4 || argc > 5)
    {
        return ERR_INCORRECT_ARG;
    }

    if (argc == 4 && strcmp(argv[1], "o") == 0)
    {
        *operation = INVERSE_MATRIX;
        return STATUS_OK;
    }
    if (argc == 5 && strcmp(argv[1], "a") == 0)
    {
        *operation = AMOUNT;
        return STATUS_OK;
    }
    if (argc == 5 && strcmp(argv[1], "m") == 0)
    {
        *operation = MULTIPLICATION;
        return STATUS_OK;
    }
    
    return ERR_INCORRECT_ARG;
}

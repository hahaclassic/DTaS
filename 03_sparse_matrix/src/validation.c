#include "validation.h"

// Checks the correctness of the specified arguments
int check_args(int argc, bool *input, bool *output)
{
    if (argc != 3 && argc != 1 && argc != 4)
    {
        return ERR_INCORRECT_ARG;
    }

    if (argc == 4)
    {
        *output = FILE_OUT;
        *input = FILE_IN;
    } 
    else if (argc == 3)
    {
        *output = STDOUT;
        *input = FILE_IN;
    }
    else
    {
        *input = STDIN;
        *output = STDOUT;
    }
    
    return STATUS_OK;
}

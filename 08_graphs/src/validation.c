#include "validation.h"

// Checks the correctness of the specified arguments
error_t check_args(int argc)
{
    if (argc == 2)
    {
        return STATUS_OK;
    }

    return ERR_INCORRECT_ARG;
}

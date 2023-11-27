#include "validation.h"

// Checks the correctness of the specified arguments
error_t check_args(int argc, int *iostream)
{
    if (argc == 1)
    {
        *iostream = STREAM_STDIN_STDOUT;
        return STATUS_OK;
    }
    else if (argc == 3)
    {
        *iostream = STREAM_FILES;
        return STATUS_OK;
    }

    return ERR_INCORRECT_ARG;
}

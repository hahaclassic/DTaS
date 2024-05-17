#include "general_parameters.h"

size_t hash_func(const char *key, size_t size)
{
    size_t sum = 0;
    size_t exp = 1;

    for (char *curr = (char *) key; *curr != '\0'; curr++)
    {
        sum += exp * (size_t) *curr;
        exp *= 10;
    }

    return sum % size;
}

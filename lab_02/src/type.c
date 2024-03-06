#include "type.h"

// Copy data from src to dest
void copy(void *src, void *dest, size_t size, size_t len)
{
    char *start_src = src;
    char *start_dest = dest;

    size_t i = 0, count = size * len;
    while (i < count) 
    {
        *start_dest = *start_src;

        start_src++;
        start_dest++;
        i++;
    }
}

#include "type.h"
#include "stdio.h"

void show_car(const void *obj, int index);

void show_key(const void *obj, int index);

void show_table(void *base, size_t len, size_t size, void (*show)(const void*, int));

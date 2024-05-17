#ifndef __READER_H__
#define __READER_H__

#include <string.h>
#include "errors.h"
#include "tree.h"
#include "general_parameters.h"

error_t get_key(char *key);

error_t get_data(char *data);

error_t get_key_data(char *key, char *data);

error_t get_table_size(size_t old_size, size_t *new_size);

#endif

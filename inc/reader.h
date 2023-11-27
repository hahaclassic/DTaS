#ifndef __READER_H__
#define __READER_H__

#include <string.h>
#include "errors.h"
#include "tree.h"
#include <ctype.h>

error_t get_date(FILE *stream, node_t *node);

error_t get_file_name(FILE *stream, node_t *node);

error_t get_file(FILE *stream, node_t **root);

error_t get_all(FILE *stream, node_t **root);

#endif

#ifndef __READER_H__
#define __READER_H__

#include <string.h>
#include "errors.h"
#include <ctype.h>
#include "graph.h"

error_t read_matrix(FILE *file, adjacency_matrix_t *matrix);

#endif

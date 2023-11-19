#ifndef __WRITER_H__
#define __WRITER_H__

#include "stdio.h"
#include "string.h"
#include "errors.h"
#include "datatype.h"
#include "linked_list.h"

int print_all(char *file_name, node_t *head);

int print_sponsor_teams(char *file_name, team_t *best, team_t *worst);

#endif

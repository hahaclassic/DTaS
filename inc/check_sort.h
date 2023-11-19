#ifndef __CHECK_SORT_H__
#define __CHECK_SORT_H__

#include "sort.h"
#include <check.h>
#include <stdbool.h>

Suite* front_back_split_suite(void);

Suite* sorted_merge_suite(void);

Suite* sort_suite(void);

#endif

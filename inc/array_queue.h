#ifndef __ARRAY_QUEUE_H__
#define __ARRAY_QUEUE_H__

#include "types.h"
#include "errors.h"
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "message.h"
#include "timer.h"

error_t arr_push(parameters_t *param, char c);
char arr_pop(parameters_t *param);

error_t option_array(int n, int log_flag, int log_interval, ranges_t *ranges);

#endif 

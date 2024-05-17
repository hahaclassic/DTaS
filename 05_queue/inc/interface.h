#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include "types.h"
#include "errors.h"
#include <stdio.h>

#define OPTIONS "==============================================================\n" \
                "|     Обработка очередей. Взаимодействие с программой        |\n" \
                "|------------------------------------------------------------|\n" \
                "| 1. Ввести значения вручную                                 |\n" \
                "|                                                            |\n" \
                "| 2. Вывести установленные значения                          |\n" \
                "|                                                            |\n" \
                "| 3. Произвести моделирование для массива                    |\n" \
                "|                                                            |\n" \
                "| 4. Произвести моделирование для списка                     |\n" \
                "|                                                            |\n" \
                "| 0. Выход                                                   |\n" \
                "--------------------------------------------------------------\n" \
                "Введите номер операции: " 

error_t input_values(int *n, int *log_flag, int *log_interval, ranges_t *ranges);
void input_range(time_range_t *T, int i);

void print_range(time_range_t *T, int i);
void print_values(int n, int log_flag, int log_interval, ranges_t *ranges);

#endif

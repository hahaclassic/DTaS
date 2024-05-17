#include <stdio.h>
#include "stack.h"
#include "parentheses.h"
#include "reader.h"
#include "writer.h"
#include "timer.h"

int main()
{
    int err;
    int operation;
    int main_operation;
    char str[MAX_LEN + 1];

    print_message(MENU);
    err = select_operation(&operation, &main_operation);
    if (err)
    {
        err_message(err);
        return err;
    }

    print_message(ENTER_STR);
    err = read_str(stdin, str);
    if (err)
    {
        err_message(err);
        return err;
    }

    arr_stack_t arr_stack;
    list_stack_t list_stack;
    stack_t stack;
    stats_t stats;
    bool ok;

    init_stats(&stats, operation);

    switch (main_operation)
    {
    case ARR_STACK:

        init_arr_stack(&stack, &arr_stack);
        
        err = is_correct(str, &stack, &ok, &stats);
        if (err)
        {
            err_message(err);
            return err;
        }

        print_result(ok);
        break;

    case LIST_STACK:

        init_list_stack(&stack, &list_stack);

        err = is_correct(str, &stack, &ok, &stats);

        list_free(&list_stack);

        if (err)
        {
            err_message(err);
            return err;
        }

        if (operation == LIST_STACK_INFO)
        {
            print_free_nodes(&stats);
        }
        print_result(ok);

        break;

    case STATS:

        init_arr_stack(&stack, &arr_stack);

        unsigned long long start, end, arr_time, list_time, arr_mem, list_mem;

        int err1 = microseconds_now(&start);
        err = is_correct(str, &stack, &ok, &stats);
        int err2 = microseconds_now(&end);
        if (err)
        {
            err_message(err);
            return err;
        }
        if (err1 | err2)
        {
            err_message(ERR_TIMER);
            return ERR_TIMER;
        }
        arr_time = end - start;
        arr_mem = sizeof(arr_stack_t);

        init_list_stack(&stack, &list_stack);
        init_stats(&stats, operation);

        err1 = microseconds_now(&start);
        err = is_correct(str, &stack, &ok, &stats);
        err2 = microseconds_now(&end);

        list_free(&list_stack);

        if (err)
        {
            err_message(err);
            return err;
        }
        if (err1 | err2)
        {
            err_message(ERR_TIMER);
            return ERR_TIMER;
        }

        list_time = end - start;
        list_mem = stats.max * sizeof(node_t) + sizeof(list_stack_t);

        print_result(ok);
        print_statistics(arr_time, arr_mem, list_time, list_mem);
        break;
    }
    

    return STATUS_OK;
}

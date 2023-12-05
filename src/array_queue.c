#include "array_queue.h"

error_t arr_push(parameters_t *param, char c)
{
    char *p_in = param->p_in;
    if (param->p_in == param->p_out && param->curr_size != 0) // && *((char*)param->p_in) != '\0'
    {
        printf("Очередь переполнена.\n");
        return ERR_QUEUE_IS_FULL;
    }
    
    *((char*) param->p_in) = c;
    
    if (param->p_in != param->up)
        param->p_in = p_in + 1;
    else
        param->p_in = param->low;
    
    return STATUS_OK;
}


char arr_pop(parameters_t *param)
{
    char *p_out = param->p_out;
    char ps = '\0';
    if (param->p_in == param->p_out && param->curr_size != 0) //*((char*) param->p_in) == '\0')
    {
        printf("Очередь пуста.\n");
    }
    else
    {
        ps = *((char*)param->p_out);
        *((char*)param->p_out) = '\0';

        if (param->p_out != param->up)
        {
            param->p_out = p_out + 1;
        }
        else
        {
            param->p_out = param->low;
        }
    }

    return ps;
}

error_t option_array(int n, int log_flag, int log_interval, ranges_t *ranges)
{
    char *queue1, *queue2;
    parameters_t param1, param2;
    error_t err;

    // allocating memory for two queues
    queue1 = calloc(MAX_LEN, sizeof(char));
    if (queue1  == NULL)
    {
        return ERR_MEMORY_ALLOC;
    }
    queue2 = calloc(MAX_LEN, sizeof(char));
    if (queue2 == NULL)
    {
        return ERR_MEMORY_ALLOC;
    }

    // initialising descriptors
    init_array(&param1, queue1);
    init_array(&param2, queue2);

    int type = 1; // current request type
    double t_q1 = 0, t_q2 = 0, t_oa = 0;
    double mod_time = 0.0; // modeling time

    // requests to queue in/out
    int req_in1 = 0, req_in2 = 0, req_out1 = 0, req_out2 = 0;
    int req_show = 0; // req_show flag;

    double total_time_out1 = 0;
    double total_time_out2 = 0;

    //time_t timer_beg = clock();
    unsigned long long timer_beg, timer_end;
    microseconds_now(&timer_beg);

    while (req_out1 < n)
    {
        if (param1.p_in == param1.p_out && *((char*) param1.p_in))
        {
            printf(FIRST_QUEUE_IS_FULL);
            break;
        }
        if (param2.p_in == param2.p_out && *((char*) param2.p_in))
        {
            printf(SECOND_QUEUE_IS_FULL);
            break;
        }

        // generating requests by random law
        if (t_q1 == 0)
        {
            t_q1 = rand_time(&ranges->t1);
        }
        if  (t_q2 == 0)
        {
            t_q2 = rand_time(&ranges->t2);
        }

        if (t_oa == 0)
        {
            if ((type == 1 || (queue_is_empty(&param2))) && !queue_is_empty(&param1))
            {
                t_oa = rand_time(&ranges->t3);
                type = 1;
                arr_pop(&param1);
                param_delete(&param1);
                total_time_out1 += t_oa;
            }
            else if ((type == 2 || (queue_is_empty(&param1))) && !queue_is_empty(&param2))
            {
                t_oa = rand_time(&ranges->t4);
                type = 2;
                arr_pop(&param2);
                param_delete(&param2);
                total_time_out2 += t_oa;
            }
        }

        double t_min; //= 0

        if(t_oa == 0)
            t_min = fmin(t_q1, t_q2);
        else
            t_min = fmin(t_q1, fmin(t_q2, t_oa));

        // Process requests
        if(t_min == t_oa)
        {
            t_oa = 0;
            if(type == 1)
                req_out1++;
            if(type == 2)
                req_out2++;
        }
        if (req_out1 == n)
            break;

        // Add requests
        if(t_min == t_q1)
        {
            err = arr_push(&param1, '1');
            if (err)
            {
                free(queue1);
                free(queue2);
                return err;
            }
            param_add(&param1);
            req_in1++;
        }
        if (t_min == t_q2)
        {
            err = arr_push(&param2, '2');
            if (err)
            {
                free(queue1);
                free(queue2);
                return err;
            }
            param_add(&param2);
            req_in2++;
        }

        t_q1 -= t_min;
        t_q2 -= t_min;

        if(t_oa >= t_min)
            t_oa -= t_min;
        mod_time += t_min;

        // Log
        if(req_out1 % log_interval == 0 && req_out1 != req_show && log_flag)
        {
            req_show = req_out1;
            printf(CURR_QUEUE_STATUS, req_out1, param1.curr_size, param1.sum_size / param1.out_request,
                param2.curr_size, param2.sum_size / param2.out_request);
        }
    }

    //time_t timer_end = clock();
    microseconds_now(&timer_end);
    double timer = timer_end - timer_beg;

    double downtime = fabs(mod_time - total_time_out1 - total_time_out2);
    double avg_time_in1 = (ranges->t1.min + ranges->t1.max) / 2;
    double avg_time_out1 = (ranges->t3.min + ranges->t3.max) / 2;
    double exp_mod_time = n * fmax(avg_time_in1, avg_time_out1);

    double out_err = 0;
    if (exp_mod_time > 0)
    {
        out_err = fabs(100*(mod_time - exp_mod_time)/exp_mod_time);
    }
    
    printf(RES_ARRAY);
    printf(RESULTS, req_in1, req_out1, req_in2, req_out2, mod_time, (int) timer, 
        downtime, exp_mod_time, out_err, sizeof(char)*MAX_LEN * 2 + 2 * sizeof(char *));
    
    free(queue1);
    free(queue2);

    return STATUS_OK;
}

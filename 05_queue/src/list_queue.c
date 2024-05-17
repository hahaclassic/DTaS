#include "list_queue.h"

stats_t stats = { .count_freed = 0, .count_reused = 0, .count_used = 0 };

node_t *create_node(char c)
{
    node_t *item = malloc(sizeof(node_t));

    if (item)
    {
        item->data = c;
        item->next = NULL;
    }

    return item;
}

node_t *add_node(node_t *head, node_t *node)
{
    node->next = head;
    return node;
}

node_t *pop_node(node_t **head)
{
    node_t* back = NULL;
    if (*head != NULL)
    {
        node_t *cur = (*head);
        if (cur->next)
        {
            for ( ; cur->next->next; cur = cur->next)
                ;
            back = cur->next;
            cur->next = NULL;
        }
        else
        {
            back = cur;
            *head = NULL;
        }
    }
    return back;
}

void free_queues(node_t *head)
{
    node_t *next;
    for ( ; head; head = next)
    {
        next = head->next;
        free(head);
    }
}

node_t *list_push(node_t *queue, char c)
{
    node_t* item = create_node(c);
   
    if (!item)
    {
        printf("Очередь заполнена.\n");
        return queue;
    }

    if (stats.count_used < MAX_LEN)
        stats.used_memory[stats.count_used++] = item;
    int sign = 0;
    for (int i = 0; i < stats.count_freed; i++)
    {
        if (item == stats.freed_memory[i])
        {
            stats.freed_memory[i] = NULL;
            sign = 1;
        }
        if (sign)
            stats.freed_memory[i] = stats.freed_memory[i+1];
    }
    if (sign)
    {
        stats.count_freed--;
        stats.count_reused++;
    }
    queue = add_node(queue, item);
    
    return queue;
}

node_t* list_pop(node_t** qu)
{
    node_t* cur = NULL;
    cur = pop_node(qu);
    if (cur == NULL)
        printf("Очередь пуста.\n");
    return cur;
}

void list_print(node_t* qu)
{
    node_t* cur = qu;
    if (qu == NULL)
    {
        printf("Пустая очередь\n");
    }
    else
    {
        printf("Очередь сейчас: \n");
        for ( ; cur; cur = cur->next)
            printf(": %c\n", cur->data);
        printf("\n");
    }
}

error_t option_list(int n, int log_flag, int log_interval, ranges_t *ranges)
{
    node_t* ret;
    stats.count_freed = 0;
    stats.count_reused = 0;
    stats.count_used = 0;

    node_t *queue1 = NULL, *queue2 = NULL;
    parameters_t param1, param2;

    param_init(&param1);
    param_init(&param2);

    int type = 1; // Current request type

    double time = 0.0; // Modeling time
    double t_q1 = 0, t_q2 = 0, t_oa = 0;
    
    // Requests to queue
    int req_in1 = 0, req_in2 = 0, req_out1 = 0, req_out2 = 0;
    int req_show = 0;

    double total_time_out1 = 0;
    double total_time_out2 = 0;

    //time_t timer_beg = clock();
    unsigned long long timer_beg, timer_end;
    microseconds_now(&timer_beg);

    while (req_out1 < n)
    {
        if (param1.curr_size >= MAX_LEN || param2.curr_size >= MAX_LEN)
        {
            printf("Очередь заполнена.\n");
            break;
        }

        if (t_q1 == 0)
            t_q1 = rand_time(&ranges->t1);
        if  (t_q2 == 0)
            t_q2 = rand_time(&ranges->t2);
        if (t_oa == 0)
        {
            if ((type == 1 || (type == 2 && queue2 == NULL)) && queue1)
            {
                t_oa = rand_time(&ranges->t3);
                type = 1;
                ret = list_pop(&queue1);

                if (ret != NULL)
                {
                    stats.freed_memory[stats.count_freed++] = ret;
                    free(ret);
                }
                param_delete(&param1);
                total_time_out1 += t_oa;
            }
            else if ((type == 2 || (type == 1 && queue1 == NULL)) && queue2)
            {
                t_oa = rand_time(&ranges->t4);
                type = 2;

                ret = list_pop(&queue2);
                if (ret != NULL)
                {
                    stats.freed_memory[stats.count_freed++] = ret;
                    free(ret);
                }
                param_delete(&param2);
                total_time_out2 += t_oa;
            }
        }

        double t_min;

        if(t_oa == 0)
            t_min = fmin(t_q1, t_q2);
        else
            t_min = fmin(t_q1, fmin(t_q2, t_oa));

        // Обработка запросов
        if(t_min == t_oa )
        {
            t_oa = 0.;
            if(type == 1)
                req_out1++;
            if(type == 2)
                req_out2++;
        }
        if (req_out1 == n)
            break;

        // Добавление запросов
        if(t_min == t_q1)
        {
            if ((queue1 = list_push(queue1, '1')) == NULL)
               return ERR_MEMORY_ALLOC;
            param_add(&param1);
            req_in1++;
        }
        if (t_min == t_q2)
        {
            if ((queue2 = list_push(queue2, '2')) == NULL)
               return ERR_MEMORY_ALLOC;
            param_add(&param2);
            req_in2++;
        }

        t_q1 -= t_min;
        t_q2 -= t_min;


        if(t_oa >= t_min)
            t_oa -= t_min;
        time += t_min;

        if(log_flag && (req_out1 % log_interval == 0) && req_out1 != req_show) // log
        {
            req_show = req_out1;
            printf(CURR_QUEUE_STATUS, req_out1, param1.curr_size, param1.sum_size / param1.out_request,
                param2.curr_size, param2.sum_size / param2.out_request);
        }
    }

    //time_t timer_end = clock();
    microseconds_now(&timer_end);
    double timer = timer_end - timer_beg;

    double downtime = fabs(time - total_time_out1 - total_time_out2);
    double avg_time_in1 = (ranges->t1.min + ranges->t1.max) / 2;
    double avg_time_out1 = (ranges->t3.min + ranges->t3.max) / 2;
    double exp_mod_time = n * fmax(avg_time_in1, avg_time_out1);

    double out_err = 0;
    if (exp_mod_time > 0)
    {
        out_err = fabs(100*(time - exp_mod_time) / exp_mod_time);
    }
    
    int avg_nodes = (param1.sum_size / param1.out_request) + (param2.sum_size / param2.out_request);

    printf(RES_LIST);
    printf(RESULTS, req_in1, req_out1, req_in2, req_out2, time, (int) timer, 
        downtime, exp_mod_time, out_err, sizeof(node_t) * avg_nodes + 2 * sizeof(char *));

   
    int flag = 0;
    printf("Показать результаты работы с памятью? 1/0: ");
    scanf("%d", &flag);

    if (flag)
    {
        printf("Переиспользованных адресов: %d\n", stats.count_reused);
        printf("Не использовались повторно: %d\n", stats.count_freed);
        printf("Первые %d из них: \n", (int) fmin(15, stats.count_freed));
        for (int i = 0; i < fmin(15, stats.count_freed); i++)
        {
            printf("[%p]\n", (void*) stats.freed_memory[i]);
        }
    }

    puts("--------------------------------------------------------------\n");

    free_queues(queue1);
    free_queues(queue2);
    return STATUS_OK;
}

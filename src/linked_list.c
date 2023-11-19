#include "linked_list.h"

node_t *create_node(void *data)
{
    node_t *node = malloc(sizeof(node_t));

    if (node)
    {
        node->data = data;
        node->next = NULL;
    }

    return node;
}

// Освобождает память из-под узлов списка, но данные не удаляются.
void list_free(node_t *head)
{
    node_t *curr;
    while (head != NULL)
    {
        curr = head;
        head = head->next;
        free(curr); 
    }
}

size_t list_len(node_t *head) 
{
    size_t count = 0;

    while (head != NULL)
    {
        count++;
        head = head->next; 
    }

    return count;
}


list_queue_t *create_queue(size_t max_len)
{
    list_queue_t *queue = malloc(sizeof(list_queue_t));
    queue->in = NULL;
    queue->out = NULL;
    queue->len = 0;
    queue->max_len = max_len;

    return queue;
}

void destroy_queue(list_queue_t *queue)
{
    list_free(queue->out);
    free(queue);
}

// Добавляет в конец очереди элемент
int list_push(list_queue_t *queue, void *data)
{
    node_t *new = create_node(data);

    if (new == NULL)
    {
        return ERR_MEMORY_ALLOCATION;
    }

    if (queue->len == queue->max_len)
    {
        return ERR_MAX_LEN;
    }

    if (queue->in == NULL)
    {
        queue->in = new;
        queue->out = new;
    }
    else
    {
        queue->in->next = new;
        queue->in = new;
    }

    return STATUS_OK;
}

// Возвращает первый элемент очереди. Из самой очереди удаляется.
node_t *list_pop(list_queue_t *queue)
{
    if (queue->out == NULL)
    {
        return NULL;
    }
    node_t *node = queue->out;
    queue->out = node->next;
    
    if (node == queue->in)
    {
        queue->in = NULL;
    }

    return node;
}

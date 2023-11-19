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

bool list_is_empty(node_t *head)
{
    return head == NULL;
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


node_t *list_init(dynamic_arr_t *arr) 
{
    node_t *head = NULL, *curr = NULL, *last = NULL;
    char *data = arr->data;

    for (size_t i = 0; i < arr->len; i++)
    {
        curr = create_node(data + i * arr->size);

        if (curr == NULL) 
        {
            list_free(head);
            return NULL;
        }
        if (head == NULL)
        {
            head = curr;
        }
        else 
        {
            last->next = curr;
        }
        last = curr;
    }

    return head;
}

node_t *find(node_t *head, const void *data, int (*comparator)(const void*, const void*))
{
    while (head != NULL)
    {
        if (!comparator(head->data, data))
        {
            return head;
        }
        head = head->next;
    }

    return NULL;
}

// Gets the top element and deletes it from the linked list.
void *pop_front(node_t **head)
{
    if (head == NULL || *head == NULL)
    {
        return NULL;
    }

    node_t *node = *head;
    void *data = node->data;
    (*head) = (*head)->next;
    free(node);

    return data;
}

// flips the linked list and returns the pointer to the new head.
node_t *reverse(node_t *head)
{
    node_t *prev = NULL, *next = NULL;

    while (head != NULL)
    {
        next = head->next;
        head->next = prev;

        prev = head;
        head = next;
    }

    return prev;
}

#include "linked_list.h"

node_t *create_node(char symbol)
{
    node_t *node = malloc(sizeof(node_t));

    if (node)
    {
        node->symbol = symbol;
        node->next = NULL;
    }

    return node;
}

void free_node(node_t *node)
{
    free(node);
}

bool list_is_empty(void *vstack)
{
    return ((list_stack_t*) vstack)->size == 0;
}

bool list_is_full(void *vstack)
{
    return ((list_stack_t*) vstack)->size >= MAX_SIZE;
}

int list_add(void *vstack, char symbol)
{
    list_stack_t *stack = vstack;

    if (list_is_full(stack))
    {
        return ERR_STACK_FULL;
    }

    node_t *node = create_node(symbol);
    
    if (!node)
    {
        return ERR_MEMORY_ALLOCATION;
    }

    node->next = stack->top;
    stack->top = node;
    stack->size++;

    return STATUS_OK;
}

char list_get_top(void *vstack)
{
    list_stack_t *stack = vstack;

    if (list_is_empty(stack))
    {
        return '\0';
    }
    
    return stack->top->symbol;
}

int list_delete(void *vstack)
{
    list_stack_t *stack = vstack;

    if (list_is_empty(stack))
    {
        return ERR_STACK_EMPTY;
    }

    node_t *node = stack->top;
    stack->top = stack->top->next;
    free_node(node);
    stack->size--;

    return STATUS_OK;
}

void list_free(void *vstack)
{
    list_stack_t *stack = vstack;
    while (!list_is_empty(stack))
    {
        list_delete(stack);
    }
}


void print_nodes(node_t *node)
{
    if (!node)
    {
        return;
    }
    print_nodes(node->next);
    printf("%c ", node->symbol);
}

void print_addresses(node_t *node)
{
    if (!node)
    {
        return;
    }
    print_addresses(node->next);
    printf("%p ", (void*) node);
}

void list_show(void *vstack)
{
    list_stack_t *stack = vstack;

    printf("Состояние стека:\n");
    if (stack->top == NULL)
    {
        printf("пустой");
    }
    print_nodes(stack->top);
    printf("\n");
    print_addresses(stack->top);
    printf("\n");
    printf("---------------------------------------------------------------------------------------\n");
}

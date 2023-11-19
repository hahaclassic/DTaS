#include "sort.h"

// Calculating the density of an object.
double win_ratio(const team_t *team)
{
    return (double) team->win / (double) (team->win + team->loss);
}

// Функция предназначена для сортировки команд в порядке убывания
int compare_teams(const void *team1, const void *team2)
{
    const team_t *t1 = team1, *t2 = team2;

    double diff = win_ratio(t1) - win_ratio(t2);
    if (fabs(diff) < DELTA)
    {
        return EQUAL;
    }
    else if (diff > 0)
    {
        return SECOND_MIN;
    }

    return FIRST_MIN;
}

// Разделяет связный список на две части.
void front_back_split(node_t *head, node_t **back)
{
    if (head == NULL)
    {
        (*back) = NULL;
        return;
    }

    size_t size = list_len(head);

    for (size_t i = 0; i < size / 2 + size % 2 - 1; i++)
    {
        head = head->next;
    }

    (*back) = head->next;
    head->next = NULL;
}

// Соединяет два отсортированных связных списка в один.
node_t *sorted_merge(node_t **head_a, node_t **head_b, int (*comparator)(const void *, const void *))
{
    node_t merged = { .data = NULL, .next = NULL };
    node_t *merged_ptr = &merged;

    while ((*head_a) != NULL && (*head_b) != NULL)
    {
        if (comparator((*head_a)->data, (*head_b)->data) <= 0)
        {
            merged_ptr->next = (*head_a);
            (*head_a) = (*head_a)->next;
        } 
        else
        {
            merged_ptr->next = (*head_b);
            (*head_b) = (*head_b)->next;
        }
        merged_ptr = merged_ptr->next;
    }
    if ((*head_a) != NULL)
    {
        merged_ptr->next = (*head_a);
        (*head_a) = NULL;
    }
    else
    {
        merged_ptr->next = (*head_b);
        (*head_b) = NULL;
    }

    return merged.next;
} 

// Merge sort
node_t *sort(node_t *head, int (*comparator)(const void *, const void *))
{
    if (head == NULL || head->next == NULL)
    {
        return head;
    }

    node_t *right = head, *left = NULL;

    front_back_split(right, &left);

    right = sort(right, comparator);
    left = sort(left, comparator);

    head = sorted_merge(&right, &left, comparator);

    return head;
}

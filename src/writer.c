#include "writer.h"

// Outputs the fields of a single object to the console.
void print_team(FILE *file, void *team)
{
    team_t *t = team;
    fprintf(file, "%s\n%d\n%d\n%s\n", t->name, t->win, t->loss, t->sponsor);
}

// Outputs the linked list items to the console.
int print_all(char *file_name, node_t *head)
{
    FILE *file = fopen(file_name, "w");
    if (file == NULL)
    {
        return ERR_FILE_OPEN;
    }

    while (head != NULL)
    {   
        print_team(file, pop_front(&head));
    }
    fclose(file);

    return STATUS_OK;
}

// void print_list(node_t *head)
// {
//     while (head != NULL)
//     {   
//         print_team(head->data);
//         head = head->next;
//     }
// }

int print_sponsor_teams(char *file_name, team_t *best, team_t *worst)
{
    FILE *file = fopen(file_name, "w");
    if (file == NULL)
    {
        return ERR_FILE_OPEN;
    }

    if (best == worst)
    {
        fprintf(file, "У этого спонсора всего одна команда: \n");
        print_team(file, best);
        fclose(file);
        return STATUS_OK;
    }

    fprintf(file, "Лучшая команда: \n");
    print_team(file, best);
    fprintf(file, "\n");

    fprintf(file, "Худшая команда: \n");
    print_team(file, worst);

    fclose(file);
    return STATUS_OK;
}

// // Outputs the linked list items to the console.
// void show_list(node_t *head)
// {
//     while (head != NULL)
//     {
//         if (head->data != NULL)
//         {
//             printf("%s ", ((team_t *) head->data)->name);
//         }
//         head = head->next;
//     }
//     printf("\n");
// }

// void show_splits(node_t *a, node_t *b)
// {
//     while (a != NULL)
//     {
//         if (a->data != NULL)
//         {
//             printf("%s ", ((team_t *) a->data)->name);
//         }
//         a = a->next;
//     }
//     printf("| ");
//     while (b != NULL)
//     {
//         if (b->data != NULL)
//         {
//             printf("%s ", ((team_t *) b->data)->name);
//         }
//         b = b->next;
//     }
//     printf("\n");
// }

#include "find_teams.h"

int compare_sponsors(const void *team1, const void *team2)
{
    const team_t *a = team1, *b = team2;

    return strcmp(a->sponsor, b->sponsor);
}



// Передается указатель на отсортированный по коэффициенту побед список команд. 
int find_teams(node_t *head, char *sponsor, team_t **best, team_t **worst)
{
    team_t compared = { NULL, 0, 0, sponsor };

    node_t *best_team = find(head, &compared, compare_sponsors);

    if (best_team == NULL)
    {
        return ERR_NOT_FOUND;
    }

    head = reverse(head);

    node_t *worst_team = find(head, &compared, compare_sponsors);

    head = reverse(head);

    (*best) = best_team->data;
    (*worst) = worst_team->data;

    return STATUS_OK;
}

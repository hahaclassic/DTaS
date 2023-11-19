#include <stdio.h>
#include "errors.h"
#include "validation.h"
#include "reader.h"
#include "writer.h"
#include "sort.h"
#include "linked_list.h"
#include "find_teams.h"

int main(int argc, char **argv)
{
    int err;
    int operation;

    // Checking args
    err = check_args(argc, argv, &operation);
    if (err)
    {
        //err_message(err);
        return err;
    }

    // Opening file
    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        //err_message(err);
        return ERR_FILE_OPEN;
    }

    // Getting all teams from a file
    dynamic_arr_t teams;
    da_init(&teams, sizeof(team_t));
    
    err = get_all(file, &teams);
    fclose(file);
    if (err)
    {   
        free_teams(&teams);
        //err_message(err);
        return err;
    }    

    node_t *head = list_init(&teams);

    if (head == NULL)
    {
        return ERR_INIT_LIST;
    }

    // Performing the specified operation
    switch (operation)
    {
        case SORT:
            head = sort(head, compare_teams);    
            err = print_all(argv[2], head);
            break;
        case PRINT_ALL:
            err = print_all(argv[2], head);
            break;
        case FIND:
            head = sort(head, compare_teams);

            team_t *best, *worst;
            err = find_teams(head, argv[3], &best, &worst);

            list_free(head);

            if (err)
            {
                free_teams(&teams);
                //err_message(err);
                return err;
            }

            err = print_sponsor_teams(argv[2], best, worst);
            break;
    }

    free_teams(&teams);
    //err_message(err);
    return err;
}
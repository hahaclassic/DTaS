#include "reader.h"

int check_value(float val)
{
    return val < 0 || fabs(val) < DELTA;
}

int read_char(FILE *input, char *symbol)
{   
    int s = fgetc(input);
    if (s == EOF)
    {
        return ERR_EOF;
    }

    *symbol = s;

    return STATUS_OK;
}

int read_line(FILE *file, dynamic_arr_t *str)
{
    char symbol;

    int err = read_char(file, &symbol);

    while (!err && symbol != '\n')
    {
        da_append(str, &symbol);
        err = read_char(file, &symbol);
    }

    symbol = '\0';
    da_append(str, &symbol);

    if (err)
    {
        return err;
    }
    
    return STATUS_OK;
}

// Reads one team from the file. Returns the error code.
int get_team(FILE *file, dynamic_arr_t *teams)
{
    team_t team;
    dynamic_arr_t name, sponsor;
    da_init(&name, sizeof(char));
    da_init(&sponsor, sizeof(char));

    int input;

    // Get name
    int err = read_line(file, &name);
    team.name = name.data;
    if (err)
    {   
        da_free(&name);
        return err;
    }

    // Get number of victories and defeats.
    input = fscanf(file, "%d\n%d\n", &team.win, &team.loss);
    if (input != 2) 
    {
        da_free(&name);
        return ERR_INCOMPLETE_STRUCT;
    }
    if (check_value(team.win) || check_value(team.loss))
    {
        da_free(&name);
        return ERR_INVALID_DATA;
    }

    // Get sponsor
    err = read_line(file, &sponsor);
    team.sponsor = sponsor.data;

    if (err)
    {   
        da_free(&name);
        da_free(&sponsor);
        return ERR_INCOMPLETE_STRUCT;
    }

    da_append(teams, &team);

    return STATUS_OK;
}

// Reads all teams from the file into an array. Returns the error code.
int get_all(FILE *file, dynamic_arr_t *teams)
{
    int err = get_team(file, teams);
    while (!err)
    {
        err = get_team(file, teams);
    }
    
    if (err && err != ERR_EOF)
    {
        return err;
    }
    if (err == ERR_EOF && teams->len == 0)
    {
        return err;
    }

    return STATUS_OK;
}

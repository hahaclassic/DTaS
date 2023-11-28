#include "reader.h"

#define MAX_LEN_ATTR 10

error_t get_date(FILE *stream, node_t *node)
{
    int day, month, year, hours, minutes;
    int input = fscanf(stream, "%d.%d.%d %d:%d", &day, &month, &year, &hours, &minutes);
    if (input != 5)
    {
        return ERR_READ_DATA;
    }

    if (day < 1 || day > 31 || month < 1 || month > 12
        || year < 2000 || year > 2023 || hours < 0 || hours > 23 || minutes < 0 || minutes > 59)
    {
        return ERR_INVALID_DATE;
    }

    node->last_access->day = day;
    node->last_access->month = month;
    node->last_access->year = year;
    node->last_access->hours = hours;
    node->last_access->minutes = minutes;
    
    return STATUS_OK;
}

error_t get_attr(FILE *stream, node_t *node)
{
    char attr[MAX_LEN_ATTR + 10];
    int input = fscanf(stream, "%s", attr);

    if (input != 1)
    {
        return ERR_READ_DATA;
    }

    if (strlen(attr) != 10 || attr[0] != '-')
    {
        return ERR_INVALID_ATTR;
    }

    for (size_t i = 1; i < MAX_LEN_ATTR; i++)
    {   
        if (attr[i] != '-')
        {
            if (((i - 1) % 3 == 0 && attr[i] != 'r')
            || ((i - 1) % 3 == 1 && attr[i] != 'w')
            || ((i - 1) % 3 == 2 && attr[i] != 'x'))
            {
                return ERR_INVALID_ATTR;
            }
        }
    }

    for (size_t i = 0; i < 3; i++)
    {
        node->attr->user[i] = attr[i + 1];
    }
    for (size_t i = 0; i < 3; i++)
    {
        node->attr->group[i] = attr[i + 4];
    }
    for (size_t i = 0; i < 3; i++)
    {
        node->attr->others[i] = attr[i + 7];
    }

    return STATUS_OK;
}

error_t get_file_name(FILE *stream, node_t *node)
{
    char file_name[MAX_FILE_NAME_LEN + 10];

    int input = fscanf(stream, "%s", file_name);
    if (input != 1)
    {
        return ERR_READ_DATA;
    }

    if (strlen(file_name) > MAX_FILE_NAME_LEN)
    {
        return ERR_INVALID_NAME;
    }

    for (char *ch = file_name; (*ch) != '\0'; ch++)
    {
        if (!isalnum(*ch) && *ch != '.' && *ch != '-' && *ch != '_')
        {
            return ERR_INVALID_NAME;
        }
    }
    
    strncpy(node->name, file_name, strlen(file_name) + 1);

    return STATUS_OK;
}

error_t get_file(FILE *stream, node_t **root)
{
    node_t *node = create_node();

    if (node == NULL)
    {
        return ERR_MEMORY_ALLOCATION;
    }

    error_t err = get_attr(stream, node);
    if (err) 
    {
        free_node(node);
        return err;
    }

    err = get_date(stream, node);
    if (err)
    {
        free_node(node);
        return err;
    }

    // Get name
    err = get_file_name(stream, node);
    if (err)
    {
        free_node(node);
        return err;
    }

    err = bst_append(root, node, compare_names);

    if (err)
    {
        return err;
    }

    return STATUS_OK;
}

error_t get_count(FILE *stream, int *count)
{
    int input = fscanf(stream, "%d", count);
    if (input != 1)
    {
        return ERR_READ_DATA;
    }
    if (*count < 1 || *count > MAX_NUM_OF_FILES)
    {
        return ERR_INVALID_NUM_OF_FILES;
    }

    return STATUS_OK;
}

error_t get_all(FILE *stream, node_t **root)
{
    int count; 
    error_t err = get_count(stream, &count);

    if (err)
    {
        return err;
    }

    for (size_t i = 0; i < (size_t) count; i++)
    {
        err = get_file(stream, root);
        if (err)
        {
            return err;
        }
    }

    return STATUS_OK;
}


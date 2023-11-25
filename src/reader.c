#include "reader.h"
#include "tree.h"
#include "dynamic_arr.h"
#include <ctype.h>

/*
    1. Ввести количество файлов
    2. Ввести файлы в стиле -rwx------ 12.20.10 12:10 name

    10 + 1 + 8 + 1 + 5 + 1 + 50 = 76 

    Правила ввода:
        1. Первые 10 символов - права доступа к файлу
        2. Далее идет дата в формате DD.MM.YY HH:MM 
        3. Далее название файла не более 50 символов
*/

#define MAX_LEN_ATTR 10

error_t check_file_name(char *file_name)
{
    for (char *ch = file_name; (*ch) != '\0'; ch++)
    {
        if (!isalnum(*ch) && *ch != '.' && *ch != '-' && *ch != '_')
        {
            return ERR_INVALID_NAME;
        }
    }

    return STATUS_OK;
}

error_t check_date(int day, int month, int year, int hours, int minutes)
{
    if (day < 1 || day > 31 || month < 1 || month > 12
        || year < 2000 || year > 2023 || hours < 0 || hours > 23 || minutes < 0 || minutes > 59)
    {
        return ERR_INVALID_DATE;
    }
    
    return STATUS_OK;
}

error_t get_attr(char *attr, node_t *node)
{
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

error_t get_file(FILE *stream, node_t **root)
{
    node_t *node = create_node();

    if (node == NULL)
    {
        return ERR_MEMORY_ALLOCATION;
    }

    char attr[MAX_LEN_ATTR + 10];
    int input = fscanf(stream, "%s", attr);
    if (input != 1)
    {
        free_node(node);
        return ERR_READ_DATA;
    }

    error_t err = get_attr(attr, node);
    if (err) 
    {
        free_node(node);
        return err;
    }

    int day, month, year, hours, minutes;
    input = fscanf(stream, "%d.%d.%d %d:%d", &day, &month, &year, &hours, &minutes);
    if (input != 5)
    {
        free_node(node);
        return ERR_READ_DATA;
    }

    err = check_date(day, month, year, hours, minutes);
    if (err)
    {
        free_node(node);
        return err;
    }

    node->last_access->day = day;
    node->last_access->month = month;
    node->last_access->year = year;
    node->last_access->hours = hours;
    node->last_access->minutes = minutes;
    
    char file_name[MAX_FILE_NAME_LEN + 10];

    //char *check;

    // Get name
    input = scanf("%s", file_name);
    if (input != 1)
    {
        return ERR_READ_DATA;
    }

    err = check_file_name(file_name);

    if (err)
    {
        free_node(node);
        return err;
    }

    strncpy(node->name, file_name, strlen(file_name) + 1);

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


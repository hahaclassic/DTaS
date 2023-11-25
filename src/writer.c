#include "writer.h"

void print_date(FILE *stream, node_t *node)
{
    if (node->last_access->day < 10)
    {
        fprintf(stream, "0");
    }
    fprintf(stream, "%zu.", node->last_access->day);
    if (node->last_access->month < 10)
    {
        fprintf(stream, "0");
    }
    fprintf(stream, "%zu.%zu ", node->last_access->month, node->last_access->year);

    if (node->last_access->hours < 10)
    {
        fprintf(stream, "0");
    }
    fprintf(stream, "%zu:", node->last_access->hours);

    if (node->last_access->minutes < 10)
    {
        fprintf(stream, "0");
    }
    fprintf(stream, "%zu", node->last_access->minutes);
}

void print_node(node_t *node, void *data)
{   
    FILE *stream = data;
    fprintf(stream, "-");
    for (size_t i = 0; i < 3; i++)
    {
        fprintf(stream, "%c", node->attr->user[i]);
    }
    for (size_t i = 0; i < 3; i++)
    {
        fprintf(stream, "%c", node->attr->group[i]);
    }
    for (size_t i = 0; i < 3; i++)
    {
        fprintf(stream, "%c", node->attr->others[i]);
    }

    fprintf(stream, " ");
    print_date(stream, node);

    fprintf(stream, " %s\n", node->name);
}

// void print_node_dot(node_t *node, void *param)
// {
//     FILE *stream = param;

//     if (node->left)
//         fprintf(stream, "\"");
//         print_date(node);
//         fprintf(stream, " %s\" -> %s;\n", node->name, tree->left->name);

//     if (node->right)
//         fprintf(stream, "%s -> %s;\n", node->name, tree->right->name);
// }

// void make_png_tree(FILE *stream, void *data)
// {

// }

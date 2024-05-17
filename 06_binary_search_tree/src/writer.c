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


void to_dot(node_t *node, void *param)
{
    FILE *f = param;

    if (node->left)
    {
        fprintf(f, "\"");
        print_date(f, node);
        fprintf(f, " %s\" -> ", node->name);
        fprintf(f, "\"");
        print_date(f, node->left);
        fprintf(f, " %s\";\n", node->left->name);
    }

    if (node->right)
    {
        fprintf(f, "\"");
        print_date(f, node);
        fprintf(f, " %s\" -> ", node->name);
        fprintf(f, "\"");
        print_date(f, node->right);
        fprintf(f, " %s\";\n", node->right->name);
    }
}

void export_to_dot(char *file_name, const char *tree_name, node_t *root)
{
    FILE *file = fopen(file_name, "w");
    if (file == NULL)
    {
        return;
    }

    fprintf(file, "digraph %s {\n", tree_name);

    if (root == NULL)
    {
        fprintf(file, "\"Пустое дерево\"");
    }
    else if (root->left == NULL && root->right == NULL)
    {
        fprintf(file, "\"");
        print_date(file, root);
        fprintf(file, " %s\"", root->name);
    }
    else
    {
        bst_pre_order_traversal(root, to_dot, file);
    }

    fprintf(file, "}\n");

    fclose(file);

    char cmd[50] = "dot -v -Tpng -o ";
    char file_png[50];

    strncpy(file_png, file_name, strlen(file_name) - 4);
    file_png[strlen(file_name) - 4] = '\0';
    strcat(file_png, ".png ");

    strcat(cmd, file_png);
    strcat(cmd, file_name);

    system(cmd);
}


void show_stats(unsigned long long alpha_tree_time, unsigned long long date_tree_time,
    unsigned long long convertation_time, unsigned long long deletion_time)
{
    printf(STATISTICS, alpha_tree_time, convertation_time, deletion_time, date_tree_time);
}

void print_tree(FILE *stream, node_t *root)
{
    if (root == NULL)
    {
        fprintf(stream, "\nДиректория пуста.\n");
    }
    else
    {
        bst_in_order_traversal(root, print_node, stream);
    }
}

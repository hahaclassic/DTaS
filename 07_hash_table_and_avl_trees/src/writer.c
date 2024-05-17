#include "writer.h"

void to_dot(tree_node_t *node, void *param)
{
    FILE *f = param;

    if (node->left)
    {
        fprintf(f, "\"%s\" -> \"%s\";\n", node->key, node->left->key);
    }

    if (node->right)
    {
        fprintf(f, "\"%s\" -> \"%s\";\n", node->key, node->right->key);
    }
}

void export_to_dot(char *file_name, const char *tree_name, tree_node_t *root)
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
        fprintf(file, "\"%s\"", root->key);
    }
    else
    {
        bst_pre_order_traversal(root, to_dot, file);
    }

    fprintf(file, "}\n");
    fclose(file);

    char cmd[50] = "dot -Tpng -o ";
    char file_png[50];

    strncpy(file_png, file_name, strlen(file_name) - 4);
    file_png[strlen(file_name) - 4] = '\0';
    strcat(file_png, ".png ");

    strcat(cmd, file_png);
    strcat(cmd, file_name);

    system(cmd);
}

// CREATE_PNG_TREES
void create_png_trees(tree_node_t *tree, tree_node_t *balanced_tree)
{
    export_to_dot(TREE, "tree", tree);

    export_to_dot(BALANCED_TREE, "balanced_tree", balanced_tree);

    printf("[OK]: Изображения в png формате успешно созданы.\n");
}


void show_search_stats(search_stats_t *stats)
{
    printf(SEARCH_STAT_TABLE, stats->open_hash_table_search_time, stats->open_hash_table_count,
        stats->closed_hash_table_search_time, stats->closed_hash_table_count,
        stats->tree_search_time, stats->tree_count, 
        stats->balanced_tree_search_time, stats->balanced_tree_count);
}

void show_avg_search_stats(avg_search_stats_t *stats)
{
    printf(AVG_SEARCH_STAT_TABLE, stats->open_hash_table_search_time, stats->open_hash_table_count,
        stats->closed_hash_table_search_time, stats->closed_hash_table_count,
        stats->tree_search_time, stats->tree_count, 
        stats->balanced_tree_search_time, stats->balanced_tree_count);
}

void show_memory_stats(memory_stats_t *stats)
{
    printf(MEMORY_STAT_TABLE, stats->len, stats->open_hash_table_size, stats->open_hash_table_memory, 
        stats->closed_hash_table_size, stats->closed_hash_table_memory, 
        stats->tree_size, stats->tree_memory, stats->balanced_tree_size, stats->balanced_tree_memory);
}


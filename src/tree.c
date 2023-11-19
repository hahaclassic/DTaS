#include "tree.h"
#include <stdlib.h>

#define ERR_FILE_ALREADY_EXISTS 151
#define ERR_NOT_FOUND 152

tree_node_t *create_node(void)
{
    tree_node_t *node = malloc(sizeof(tree_node_t));
    
    if (!node)
    {
        return NULL;
    }
    
    attributes_t *attr = malloc(sizeof(attributes_t));

    if (!attr)
    {
        free(node);
        return NULL;
    }

    date_t *last_access = malloc(sizeof(date_t));

    if (!last_access)
    {
        free(node);
        free(attr);
        return NULL;
    }

    node->attr = attr;
    node->last_access = last_access;
    node->left = NULL;
    node->right = NULL;

    return node;
}

void free_node(tree_node_t *node)
{
    if (node == NULL)
    {
        return;
    }
    free(node->attr);
    free(node->last_access);
    free(node);
}

void free_tree(tree_node_t *root)
{
    if (root == NULL)
    {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free_node(root);
}

void append_node(tree_node_t *root, tree_node_t *node, 
    int (*compare)(tree_node_t *node1, tree_node_t *node2))
{
    bool comp = compare(root, node) <= 0;

    if (comp && root->left == NULL)
    { 
        root->left = node;
    }
    else if (!comp && root->right == NULL)
    {
        root->right = node;
    }
    else if (comp)
    {
        append_node(root->left, node, compare);
    }
    else
    {
        append_node(root->right, node, compare);
    }
}

int delete_node(tree_node_t *root, tree_node_t *node, 
    int (*compare)(tree_node_t *node1, tree_node_t *node2))
{
    if (root == NULL || node == NULL)
    {
        return ERR_NOT_FOUND;
    }

    int comp = compare(root, node);

    if (comp > 0)
    {
        return is_exist(root->right, node, compare);
    }
    else if (comp < 0)
    {
        return is_exist(root->left, node, compare);
    }
}

// Возвращаемый элемент удаляется из дерева
tree_node_t *get_min(tree_node_t *root)
{
    if (root == NULL)
    {
        return NULL;
    }

    while (root->left != NULL)
    {
        root = root->left;
    }
    
    return root;
}

bool is_exist(tree_node_t *root, tree_node_t *node, 
    int (*compare)(tree_node_t *node1, tree_node_t *node2))
{
    if (root == NULL || node = NULL)
    {
        return NULL;
    }

    int comp = compare(root, node);

    if (comp > 0)
    {
        return is_exist(root->right, node, compare);
    }
    else if (comp < 0)
    {
        return is_exist(root->left, node, compare);
    }
    
    return node;
}

tree_node_t *find(tree_node_t *root, tree_node_t *node, 
    int (*compare)(tree_node_t *node1, tree_node_t *node2))
{
    if (root == NULL || node = NULL)
    {
        return NULL;
    }

    int comp = compare(root, node);

    if (comp > 0)
    {
        return find(root->right, node, compare);
    }
    else if (comp < 0)
    {
        return find(root->left, node, compare);
    }
    
    return node;
}

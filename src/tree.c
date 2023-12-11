#include "tree.h"

int compare_nodes(void *arg1, void *arg2)
{
    tree_node_t *node1 = arg1, *node2 = arg2;
    return strcmp(node1->key, node2->key);
}

tree_node_t *tree_node_create()
{
    tree_node_t *node = malloc(sizeof(tree_node_t));

    if (node)
    {
        node->left = NULL;
        node->right = NULL;
    }

    return node;
}

void tree_node_free(tree_node_t *node)
{
    if (node)
    {
        free(node);
    }
}

void bst_free(tree_node_t *root)
{
    if (root == NULL)
    {
        return;
    }

    bst_free(root->left);
    bst_free(root->right);

    free(root);
}


error_t bst_append(tree_node_t **root, tree_node_t *node, size_t *count_comparison)
{
    tree_node_t *curr = (*root);

    if (curr == NULL)
    {
        (*root) = node;
        return STATUS_OK;
    }

    while (curr != NULL)
    {
        if (count_comparison != NULL)
        {
            (*count_comparison)++;
        }

        int result = compare_nodes(node, curr);
        if (result == 0)
        {
            return ERR_KEY_EXISTS;
        }
        if (result > 0)
        {
            if (curr->right == NULL)
            {
                curr->right = node;
                break;
            }
            else
            {
                curr = curr->right;
            }
        }
        else
        {
            if (curr->left == NULL)
            {
                curr->left = node;
                break;
            }
            else
            {
                curr = curr->left;
            }
        }
    }

    return STATUS_OK;
}

error_t bst_insert_key(tree_node_t **root, size_t *count, const char *key, const char *value)
{
    tree_node_t *node = tree_node_create();
    if (node == NULL)
    {
        return ERR_MEMORY_ALLOCATION;
    }

    strcpy(node->key, key);
    strcpy(node->value, value);

    error_t err = bst_append(root, node, count);
    if (err)
    {
        tree_node_free(node);
        return err;
    }

    return STATUS_OK;
}


error_t bst_find(tree_node_t *root, size_t *count_comparison, const char *key, char **value)
{
    while (root != NULL)
    {
        int result = strcmp(key, root->key);

        if (count_comparison != NULL)
        {
            (*count_comparison)++;
        }

        if (result == 0)
        {   
            (*value) = root->value;
            return STATUS_OK;
        }
        if (result > 0)
        {
            root = root->right;
        }
        else
        {
            root = root->left;
        }
    }

    return ERR_NOT_FOUND;
}

void bst_in_order_traversal(tree_node_t *root, void (*action)(tree_node_t *data, void *param), void *param)
{
    if (root == NULL)
    {
        return;
    }

    bst_in_order_traversal(root->left, action, param);
    action(root, param);
    bst_in_order_traversal(root->right, action, param);
}

// pre-order traversal
void bst_pre_order_traversal(tree_node_t *root, void (*action)(tree_node_t *data, void *param), void *param)
{
    if (root == NULL)
    {
        return;
    }

    action(root, param);

    bst_pre_order_traversal(root->left, action, param);
    bst_pre_order_traversal(root->right, action, param);
}

int max(int a, int b) 
{
    if (a > b)
    {
        return a;
    }
    return b;
}


// Частичная балансировкая дерева
tree_node_t *bst_half_balance(tree_node_t *root, int *left_h, int *right_h, bool *is_balanced)
{
    *left_h = 0;
    *right_h = 0;
    if (root == NULL) 
    {
        return NULL;
    }
    if (root->left == NULL && root->right == NULL) 
    {   
        return root;
    }

    int ll_h, rr_h, lr_h, rl_h; // первая буква - левое или правое поддерево, вторая буква - поддерево от текущего поддерева
    root->left = bst_half_balance(root->left, &ll_h, &lr_h, is_balanced);
    root->right = bst_half_balance(root->right, &rl_h, &rr_h, is_balanced);

    *left_h = (root->left == NULL ? 0 : max(ll_h, lr_h) + 1);
    *right_h = (root->right == NULL ? 0 : max(rl_h, rr_h) + 1);

    tree_node_t *new_root = root;

    if (*left_h - *right_h > 1)
    {
        if (lr_h > ll_h)  // Большой правый поворот
        {
            new_root = root->left->right;
            root->left->right = new_root->left;
            new_root->left = root->left;
            root->left = new_root->right;
            new_root->right = root;
        } 
        else // Малый правый поворот
        {
            new_root = root->left;
            root->left = new_root->right;
            new_root->right = root;
        }
        (*left_h)--;
        (*right_h)++;
        *is_balanced = false;
    } 
    else if (*left_h - *right_h < -1)
    {
        if (rl_h > rr_h) // Большой левый поворот
        {
            new_root = root->right->left;
            root->right->left = new_root->right;
            new_root->right = root->right;
            root->right = new_root->left;
            new_root->left = root;
        } 
        else // Малый левый поворот
        {
            new_root = root->right;
            root->right = new_root->left;
            new_root->left = root;
        }
        *is_balanced = false;
        (*left_h)++;
        (*right_h)--;
    }

    return new_root;
}

// Полная балансировка дерева
tree_node_t *bst_balance(tree_node_t *root)
{
    int l_h, r_h;
    bool is_balanced;
    do 
    {
        is_balanced = true;
        root = bst_half_balance(root, &l_h, &r_h, &is_balanced);
    }
    while (is_balanced == false);

    return root;
}

#include "tree.h"

int compare_names(void *arg1, void *arg2)
{
    node_t *node1 = arg1, *node2 = arg2;
    return strcmp(node1->name, node2->name);
}

int compare_dates(void *arg1, void *arg2)
{
    node_t *node1 = arg1, *node2 = arg2;

    if (node1->last_access->year > node2->last_access->year)
    {
        return FIRST_LATER_OR_EQUAL;
    }
    else if (node1->last_access->year < node2->last_access->year)
    {
        return SECOND_LATER;
    }
    else if (node1->last_access->month > node2->last_access->month)
    {
        return FIRST_LATER_OR_EQUAL;
    }
    else if (node1->last_access->month < node2->last_access->month)
    {
        return SECOND_LATER;
    }
    else if (node1->last_access->day > node2->last_access->day)
    {
        return FIRST_LATER_OR_EQUAL;
    }
    else if (node1->last_access->day < node2->last_access->day)
    {
        return SECOND_LATER;
    }
    else if (node1->last_access->hours > node2->last_access->hours)
    {
        return FIRST_LATER_OR_EQUAL;
    }
    else if (node1->last_access->hours < node2->last_access->hours)
    {
        return SECOND_LATER;
    }
    else if (node1->last_access->minutes > node2->last_access->minutes)
    {
        return FIRST_LATER_OR_EQUAL;
    }
    else if (node1->last_access->minutes < node2->last_access->minutes)
    {
        return SECOND_LATER;
    }

    return FIRST_LATER_OR_EQUAL;
}

node_t *create_node(void)
{
    node_t *node = malloc(sizeof(node_t));
    
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

void free_node(node_t *node)
{
    if (node == NULL)
    {
        return;
    }
    free(node->attr);
    free(node->last_access);
    free(node);
}


void bst_free(node_t *root)
{
    if (root == NULL)
    {
        return;
    }

    bst_free(root->left);
    bst_free(root->right);
    free_node(root);
}

error_t bst_append(node_t **root, node_t *node, int (*compare)(void *arg1, void *arg2))
{
    node_t *curr = (*root);

    if (curr == NULL)
    {
        (*root) = node;
        return STATUS_OK;
    }

    while (curr != NULL)
    {
        int result = compare(node, curr);
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

// node_t *bst_min(node_t *root)
// {
//     if (root == NULL)
//     {
//         return NULL;
//     }

//     while (root->left != NULL)
//     {
//         root = root->left;
//     }

//     return root;
// }


// node_t *bst_remove(node_t *root, int (*compare)(void *arg1, void *param), void *param, int *err)
// {
//     if (root == NULL)
//     {
//         (*err) = ERR_NOT_FOUND;
//         return root;
//     }

//     node_t *temp;
//     int result = compare(root, param);

//     if (result < 0)
//     {
//         root->left = bst_remove(root->left, compare, param, err);
//     }
//     else if (result > 0)
//     {
//         root->right = bst_remove(root->right, compare, param, err);
//     }
//     else if (root->left != NULL && root->right != NULL)
//     {
//         temp = bst_min(root->right);
//         temp->left = root->left;
//         temp->right = bst_remove(root->right, compare, temp->key, err);

//         free_node(root);       
//         root = temp;
//     }
//     else
//     {
//         if (root->left == NULL && root->right == NULL)
//         {
//             return NULL;
//         }

//         temp = root;
//         if (root->left != NULL)
//         {
//             root = root->left;
//         }
//         else
//         {
//             root = root->right;
//         }
//         free_node(temp);       
//     }

//     return root;
// }


// int bst_find(node_t *root, const char *key, int **value)
// {
//     //bst_travesal(root, print, NULL);

//     if (root == NULL)
//     {
//         return ERR_NOT_FOUND;
//     }

//     while (root != NULL)
//     {
//         int result = strcmp(key, root->key);
//         if (result == 0)
//         {   
//             (*value) = &root->value;
//             return STATUS_OK;
//         }
//         if (result > 0)
//         {
//             root = root->right;
//         }
//         else
//         {
//             root = root->left;
//         }
//     }

//     return ERR_NOT_FOUND;
// }

node_t *copy_node(node_t *node)
{
    node_t *new = create_node();

    if (new == NULL)
    {
        return NULL;
    }

    attributes_t *attr = new->attr;
    date_t *date = new->last_access;

    char *dest = (void *) new, *src = (void *) node;

    size_t size = sizeof(node_t);
    for (size_t i = 0; i < size; i++)
    {
        *dest = *src;
        dest++;
        src++;
    }

    size = sizeof(attributes_t);
    dest = (void *) attr; src = (void *) node->attr;
    for (size_t i = 0; i < size; i++)
    {
        *dest = *src;
        dest++;
        src++;
    }

    size = sizeof(date_t);
    dest = (void *) date; src = (void *) node->last_access;
    for (size_t i = 0; i < size; i++)
    {
        *dest = *src;
        dest++;
        src++;
    }

    new->attr = attr;
    new->last_access = date;

    return new;
}

node_t *bst_deep_copy(node_t *src_root)
{
    if (src_root == NULL)
    {
        return NULL;
    }

    node_t *copy = copy_node(src_root);

    if (copy == NULL)
        return NULL;

    if (src_root->left != NULL)
    {
        copy->left = bst_deep_copy(src_root->left);

        if (copy->left == NULL)
        {
            bst_free(copy);
            return NULL;
        }   
    }
    else
    {
        copy->left = NULL;
    }

    if (src_root->right != NULL)
    {
        copy->right = bst_deep_copy(src_root->right);

        if (copy->right == NULL)
        {
            bst_free(copy);
            return NULL;
        }   
    }
    else
    {
        copy->right = NULL;
    }

    return copy;
}

// in-order travesal
void bst_travesal(node_t *root, void (*action)(node_t *data, void *param), void *param)
{
    if (root == NULL)
    {
        return;
    }

    bst_travesal(root->left, action, param);
    action(root, param);
    bst_travesal(root->right, action, param);
}

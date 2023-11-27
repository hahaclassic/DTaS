#include "operations.h"

void menu()
{
    fprintf(stdout, MENU);
    fprintf(stdout, INPUT_OUTPUT);
}

error_t choose_operation(operation_t *operation)
{
    fprintf(stdout, ENTER_OPERATION);
    int op;
    int input = fscanf(stdin, "%d", &op);

    if (input != 1)
    {
        return ERR_READ_DATA;
    }

    *operation = op;
    if (*operation < 0 || *operation > SHOW_FILES)
    {
        return ERR_INVALID_OPERATION;
    }

    return STATUS_OK;
}

error_t delete_file_by_name(node_t **root)
{
    if (*root == NULL)
    {
        return ERR_EMPTY_TREE;
    }

    node_t *mask = create_node();

    if (mask == NULL)
    {
        return ERR_MEMORY_ALLOCATION;
    }

    printf(ENTER_FILE_NAME);

    error_t err = get_file_name(stdin, mask);

    if (err)
    {
        free_node(mask);
        return err;
    }

    export_to_dot(ALPHABET_BST_BEFORE_DOT_FILE, "alphabet_tree_before", *root);

    (*root) = bst_remove(*root, compare_names, mask, &err);

    export_to_dot(ALPHABET_BST_AFTER_DOT_FILE, "alphabet_tree_after", *root);

    free_node(mask);

    return err;
}


error_t alpha_tree_delete_by_time(node_t **root)
{
    if (*root == NULL)
    {
        return ERR_EMPTY_TREE;
    }

    node_t *mask = create_node();

    if (mask == NULL)
    {
        return ERR_MEMORY_ALLOCATION;
    }

    printf(ENTER_DATE);

    error_t err = get_date(stdin, mask);

    if (err)
    {
        free_node(mask);
        return err;
    }

    export_to_dot(ALPHABET_BST_BEFORE_DOT_FILE, "alphabet_tree_before", *root);

    (*root) = bst_alpha_remove_all(*root, mask);

    export_to_dot(ALPHABET_BST_AFTER_DOT_FILE, "alphabet_tree_after", *root);

    free_node(mask);

    return err;
}


error_t date_tree_delete_by_time(node_t *root)
{
    if (root == NULL)
    {
        return ERR_EMPTY_TREE;
    }

    node_t *mask = create_node();

    if (mask == NULL)
    {
        return ERR_MEMORY_ALLOCATION;
    }

    printf(ENTER_DATE);

    error_t err = get_date(stdin, mask);

    if (err)
    {
        free_node(mask);
        return err;
    }

    node_t *copy_tree = bst_deep_copy(root);
    node_t *converted = NULL;

    bst_convert(copy_tree, &converted, compare_dates);

    export_to_dot(DATE_BST_BEFORE_DOT_FILE, "date_tree_before", converted);

    converted = bst_date_remove_all(converted, mask);

    export_to_dot(DATE_BST_AFTER_DOT_FILE, "date_tree_after", converted);

    bst_free(converted);
    free_node(mask);

    return err;
}

error_t measure_time(node_t **root, unsigned long long *alpha_tree_time, 
    unsigned long long *deletion_time, unsigned long long *convertation_time)
{
    if (*root == NULL)
    {
        return ERR_EMPTY_TREE;
    }

    node_t *mask = create_node();

    if (mask == NULL)
    {
        return ERR_MEMORY_ALLOCATION;
    }

    printf(ENTER_DATE);

    error_t err = get_date(stdin, mask);

    if (err)
    {
        free_node(mask);
        return err;
    }

    export_to_dot(ALPHABET_BST_BEFORE_DOT_FILE, "alphabet_tree_before", *root);

    unsigned long long start, end, mid;
    node_t *copy_tree = bst_deep_copy(*root);

    microseconds_now(&start);
    (*root) = bst_alpha_remove_all(*root, mask);
    microseconds_now(&end);

    *alpha_tree_time = end - start;

    export_to_dot(ALPHABET_BST_AFTER_DOT_FILE, "alphabet_tree_after", *root);

    if (err)
    {
        free_node(mask);
        bst_free(copy_tree);
        return err;
    }

    node_t *converted = NULL;

    microseconds_now(&start);
    bst_convert(copy_tree, &converted, compare_dates);
    microseconds_now(&mid);
    converted = bst_date_remove_all(converted, mask);
    microseconds_now(&end);

    export_to_dot(DATE_BST_AFTER_DOT_FILE, "date_tree_after", converted);

    free_node(mask);
    bst_free(converted);

    *convertation_time = (mid - start);
    *deletion_time = (end - mid);

    return STATUS_OK;
}

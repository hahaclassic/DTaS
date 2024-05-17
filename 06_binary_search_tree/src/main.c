#include "tree.h"
#include "reader.h"
#include "writer.h"
#include "validation.h"
#include "operations.h"
#include "timer.h"
#include <stdio_ext.h>


int main(int argc, char **argv)
{
    int iostream;
    error_t err;

    err = check_args(argc, &iostream);

    if (err)
    {
        return err;
    }

    FILE *in = stdin, *out = stdout;

    node_t *root = NULL;

    if (iostream == STREAM_FILES)
    {
        in = fopen(argv[1], "r");
        if (in == NULL)
        {
            err_message(ERR_FILE_OPEN);
            return ERR_FILE_OPEN;
        }

        err = get_all(in, &root);
        fclose(in);

        if (err)
        {
            err_message(err);
            bst_free(root);
            return err;
        }

        out = fopen(argv[2], "w");
        if (out == NULL)
        {
            bst_free(root);
            err_message(ERR_FILE_OPEN);
            return ERR_FILE_OPEN;
        }
    }

    unsigned long long alpha_tree_time, deletion_time, convertation_time;

    operation_t operation;

    menu();
    err = choose_operation(&operation);
    while (err)
    {
        __fpurge(stdin);
        err_message(ERR_INVALID_OPERATION);
        err = choose_operation(&operation);
    }

    while (operation)
    {
        switch (operation)
        {
        case APPEND_FILE:

            export_to_dot(ALPHABET_BST_BEFORE_DOT_FILE, "alphabet_tree_before", root);

            printf(ENTER_FILE);
            err = get_file(stdin, &root);

            export_to_dot(ALPHABET_BST_AFTER_DOT_FILE, "alphabet_tree_after", root);

            break;

        case DELETE_FILE:
            err = delete_file_by_name(&root);
            break;

        case ALPHABET_BST_DELETE:
            err = alpha_tree_delete_by_time(&root);
            break;

        case DATE_BST_DELETE:
            err = date_tree_delete_by_time(root);
            break;

        case TIMER:
            err = measure_time(&root, &alpha_tree_time, &deletion_time, &convertation_time);

            if (!err)
            {
                show_stats(alpha_tree_time, deletion_time + convertation_time,
                    convertation_time, deletion_time);
            }
            break;

        case SHOW_FILES:

            print_tree(stdout, root);

            break;
        
        case END:

            break;
        }

        if (err)
        {
            err_message(err);
            __fpurge(stdin);
        }
        else
        {
            printf("\n[OK]: Операция завершена успешно.\n");
        }

        menu();
        err = choose_operation(&operation);
        while (err)
        {
            __fpurge(stdin);
            err_message(err);
            err = choose_operation(&operation);
        }
    }

    print_tree(out, root);
    fclose(out);

    bst_free(root);
    return STATUS_OK;
}

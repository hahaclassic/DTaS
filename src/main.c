#include "tree.h"
#include "reader.h"
#include "writer.h"
#include "validation.h"

int main() //int argc, char **argv)
{
    // int iostream;
    // error_t err;

    // err = check_args(argc, &iostream);

    // if (err)
    // {
    //     return err;
    // }

    FILE *in = stdin, *out = stdout;

    node_t *root = NULL;

    // if (iostream == FILE_IN)
    // {
    //     in = fopen(argv[1], "r");
    //     if (in == NULL)
    //     {
    //         return ERR_FILE_OPEN;
    //     }

    //     error_t err = get_all(in, &root);

    //     if (err)
    //     {
    //         bst_free(root);
    //         return err;
    //     }
    // }

    // menu()

    error_t err = get_all(in, &root);
    if (err)
    {
        return err;
    }

    bst_travesal(root, print_node, out);

    node_t *copy = bst_deep_copy(root);

    if (copy == NULL)
    {
        bst_free(root);
        return ERR_MEMORY_ALLOCATION;
    }

    printf("\n\n");
    bst_travesal(copy, print_node, out);

    bst_free(copy);
    bst_free(root);
    return STATUS_OK;
}

#include "operations.h"

int main()
{
    open_hash_table_t *open_hash_table;
    closed_hash_table_t *closed_hash_table;
    tree_node_t *tree = NULL;
    tree_node_t *balanced_tree = NULL;

    search_stats_t search_stats;
    restruct_stats_t restruct_stats;
    memory_stats_t memory_stats;

    error_t err = init_structures(&open_hash_table, &closed_hash_table, &tree, &balanced_tree);
    if (err)
    {
        return err;
    }

    operation_t operation = choose_operation();

    while (operation)
    {
        switch (operation)
        {
        case FIND_DATA:
            err = find_data(open_hash_table, closed_hash_table, tree, balanced_tree);
            break;

        case INSERT_DATA:
            err = insert_data(open_hash_table, closed_hash_table, &tree, &balanced_tree);
            break;

        case RESTRUCTURE_HASH_TABLES:
            err = restructure_hash_tables(open_hash_table, closed_hash_table, &restruct_stats);

            if (!err)
                show_restruct_stats(&restruct_stats);

            break;

        case PRINT_OPEN_HASH_TABLE:
            open_hash_table_show(open_hash_table);
            break;

        case PRINT_CLOSED_HASH_TABLE:
            closed_hash_table_show(closed_hash_table);
            break;

        case CREATE_PNG_TREES:
            create_png_trees(tree, balanced_tree);
            break;
        
        case COMPARE_SEARCH:
            err = measure_search_time(open_hash_table, closed_hash_table, tree, 
                balanced_tree, &search_stats);

            if (!err)
                show_search_stats(&search_stats);
                
            break;

        case COMPARE_MEMORY:

            сalc_memory(open_hash_table, closed_hash_table, &memory_stats);
            show_memory_stats(&memory_stats);

            break;

        case END:

            break;
        }

        err_message(err);
        operation = choose_operation();
    }

    open_hash_table_free(open_hash_table);
    closed_hash_table_free(closed_hash_table);
    bst_free(tree);
    bst_free(balanced_tree);

    return STATUS_OK;
}

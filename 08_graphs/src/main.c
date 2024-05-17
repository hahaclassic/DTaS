#include "reader.h"
#include "writer.h"
#include "validation.h"
#include "operations.h"
#include "timer.h"
#include <stdio_ext.h>



int main(int argc, char **argv)
{
    error_t err;

    err = check_args(argc);

    if (err)
    {
        return err;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        err_message(ERR_FILE_OPEN);
        return ERR_FILE_OPEN;
    }

    adjacency_matrix_t matrix;

    err = read_matrix(file, &matrix);
    fclose(file);

    if (err)
    {
        err_message(err);
        return err;
    }

    operation_t operation = choose_operation();

    while (operation)
    {
        switch (operation)
        {
        case MIN_DISTANCE:
            
            err = user_find_min_distance(&matrix);
            break;

        case FIND_VERTICES:
            
            err = user_find_vertices(&matrix);
            break;

        case CREATE_PNG_GRAPH:

            export_to_dot(GRAPH_DOT_FILE, &matrix);
            printf("\n[OK]: Изображение создано успешно.\n");
            break;

        case EFFICIENCY_OF_THE_ALGORITHM:

            err = measure_time(&matrix);

            break;

        case END:

            break;
        }

        err_message(err);
        operation = choose_operation();
    }
    return STATUS_OK;
}

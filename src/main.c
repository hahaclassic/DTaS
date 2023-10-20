#include <stdio.h>
#include "validation.h"
#include "reader.h"
#include "writer.h"
#include "operations.h"

int main(int argc, char **argv)
{
    int err;
    int operation;

    // Checking args.
    err = check_args(argc, argv, &operation);
    if (err)
    {
        //err_message(err);
        return err;
    }


    matrix_t matrix1, matrix2, result;

    err = read_matrix(argv[2], &matrix1);
    if (err)
    {   
        //err_message(err);
        return err;
    }

    switch (operation)
    {
        case AMOUNT:

            err = read_matrix(argv[3], &matrix2);
            if (err)
            {   
                //err_message(err);
                free_matrix(&matrix1);
                return err;
            }

            if (matrix1.columns != matrix2.columns || matrix1.rows != matrix2.rows)
            {
                free_matrix(&matrix1);
                free_matrix(&matrix2);
                return ERR_DIFFERENT_SIZES;
            }

            err = set_matrix(&result, matrix1.rows, matrix1.columns);
            if (err)
            {
                free_matrix(&matrix1);
                free_matrix(&matrix2);
                return err;
            }

            sum(&matrix1, &matrix2, &result);

            err = write_data(argv[4], &result);
            break;
        case MULTIPLICATION:

            err = read_matrix(argv[3], &matrix2);
            if (err)
            {   
                //err_message(err);
                free_matrix(&matrix1);
                return err;
            }

            if (matrix1.columns != matrix2.rows)
            {
                free_matrix(&matrix1);
                free_matrix(&matrix2);
                return ERR_INCORRECT_SIZES;
            }

            err = set_matrix(&result, matrix1.rows, matrix2.columns);
            if (err)
            {
                free_matrix(&matrix1);
                free_matrix(&matrix2);
                return err;
            }

            multiply(&matrix1, &matrix2, &result);

            err = write_data(argv[4], &result);
            break;
        case INVERSE_MATRIX:
        
            if (matrix1.columns != matrix1.rows)
            {
                free_matrix(&matrix1);
                return ERR_NON_SQUARE_MATRIX;
            }

            err = set_matrix(&matrix2, matrix1.rows, matrix1.columns);
            if (err)
            {
                free_matrix(&matrix1);
                return err;
            }

            err = set_matrix(&result, matrix1.rows, matrix1.columns);
            if (err)
            {
                free_matrix(&matrix1);
                free_matrix(&matrix2);
                return err;
            }

            err = get_inverse_matrix(&matrix1, &matrix2, &result);

            if (!err)
            {
                err = write_data(argv[3], &result);
            } 
            break;
    }

    free_matrix(&matrix1);
    free_matrix(&matrix2);
    free_matrix(&result);

    if (err)
    {
        return err;
    }

    return STATUS_OK;
}

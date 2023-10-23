#include <stdio.h>
#include "validation.h"
#include "reader.h"
#include "writer.h"
#include "multiplication.h"


int main(int argc, char **argv)
{
    std_matrix_t std1, std2, std_res;
    sparse_matrix_t csr, csc, sparse_res;

    bool input, output;
    int err = check_args(argc, &input, &output);
    if (err)
    {
        return err;
    }

    if (input)
    {
        err = read_matrix_file(argv[1], &std1);
        if (err)
        {
            return err;
        }
        err = read_matrix_file(argv[2], &std2);
    }
    else
    {
        err = read_matrix(stdin, &std1);
        if (err)
        {
            return err;
        }
        err = read_matrix(stdin, &std2);
    }
    if (err)
    {
        free_std_matrix(&std1);
        return err;
    }

    // Проверка корректности размерностей матриц
    if (std1.columns != std2.rows)
    {
        free_std_matrix(&std1);
        free_std_matrix(&std2);
        return ERR_INCORRECT_MATRIX_SIZES;
    }

    err = set_std_matrix(&std_res, std1.rows, std2.columns);
    if (err)
    {
        free_std_matrix(&std1);
        free_std_matrix(&std2);
        return err;
    }

    err = set_sparse_matrix(&csr, std1.rows, std1.columns, std1.n_nz, CSR);
    if (err)
    {
        free_std_matrix(&std_res);
        free_std_matrix(&std1);
        free_std_matrix(&std2);
        return err;
    }

    err = set_sparse_matrix(&csc, std2.rows, std2.columns, std2.n_nz, CSC);
    if (err)
    {
        free_std_matrix(&std_res);
        free_std_matrix(&std1);
        free_std_matrix(&std2);
        free_sparse_matrix(&csr);
        return err;
    }

    err = set_sparse_matrix(&sparse_res, std1.rows, std2.columns, std1.rows * std2.columns, CSR);
    if (err)
    {
        free_std_matrix(&std_res);
        free_std_matrix(&std1);
        free_std_matrix(&std2);
        free_sparse_matrix(&csr);
        free_sparse_matrix(&csc);
        return err;
    }

    init_sparse_matrix(&csr, &std1);
    init_sparse_matrix(&csc, &std2);

    // Multiplication
    std_matrix_multiply(&std1, &std2, &std_res);

    sparse_matrix_multiply(&csr, &csc, &sparse_res);


    // Printing result
    // for (size_t i = 0; i < csr.n_nz; i++)
    // {
    //     printf("%lf ", csr.nums[i]);
    // }
    // printf("\n");
    // for (size_t i = 0; i < csr.n_nz; i++)
    // {
    //     printf("%zu ", csr.idx[i]);
    // }
    // printf("\n");
    // for (size_t i = 0; i <= csr.n_rows; i++)
    // {
    //     printf("%zu ", csr.start[i]);
    // }
    // printf("\n");
    // printf("\n");


    // for (size_t i = 0; i < csc.n_nz; i++)
    // {
    //     printf("%lf ", csc.nums[i]);
    // }
    // printf("\n");
    // for (size_t i = 0; i < csc.n_nz; i++)
    // {
    //     printf("%zu ", csc.idx[i]);
    // }
    // printf("\n");
    // for (size_t i = 0; i <= csc.n_cols; i++)
    // {
    //     printf("%zu ", csc.start[i]);
    // }
    // printf("\n");
    // printf("\n");


    // for (size_t i = 0; i < sparse_res.n_nz; i++)
    // {
    //     printf("%lf ", sparse_res.nums[i]);
    // }
    // printf("\n");
    // for (size_t i = 0; i < sparse_res.n_nz; i++)
    // {
    //     printf("%zu ", sparse_res.idx[i]);
    // }
    // printf("\n");
    // for (size_t i = 0; i <= sparse_res.n_rows; i++)
    // {
    //     printf("%zu ", sparse_res.start[i]);
    // }
    // printf("\n");
    // printf("\n");
    if (output)
    {
        err = write_sparse_matrix_file(argv[3], &sparse_res);
    }
    else
    {
        printf("Результат:\n");
        write_sparse_matrix(stdout, &sparse_res);
    }

    free_std_matrix(&std1);
    free_std_matrix(&std2);
    free_std_matrix(&std_res);
    free_sparse_matrix(&csr);
    free_sparse_matrix(&csc);
    free_sparse_matrix(&sparse_res);

    if (err)
    {
        return err;
    }

    return STATUS_OK;
}

#include <stdio.h>
#include "validation.h"
#include "reader.h"
#include "writer.h"
#include "multiplication.h"

int main(int argc, char **argv)
{
    std_matrix_t std1, std2, std_res;
    sparse_matrix_t csr, csc, sparse_res;
    csr.type = CSR;
    csr.type = CSC;

    bool input, output;
    int err = check_args(argc, &input, &output);
    if (err)
    {
        err_message(err);
        return err;
    }

    if (input)
    {
        err = read_matrix_file(argv[1], &csr, &std1);
        if (err)
        {
            err_message(err);
            return err;
        }

        err = read_matrix_file(argv[2], &csc, &std2);
    }
    else
    {
        show_menu();
        printf("Введите кол-во строк, столбцов и ненелувых элементов 1-ой матрицы (через пробел): ");

        err = read_matrix(stdin, &csr, &std1);
        if (err)
        {
            err_message(err);
            return err;
        }

        printf("Введите кол-во строк, столбцов и ненелувых элементов 2-ой матрицы (через пробел): ");
        err = read_matrix(stdin, &csc, &std2);
    }
    if (err)
    {
        err_message(err);
        free_std_matrix(&std1);
        free_sparse_matrix(&csr);
        return err;
    }

    for (size_t i = 0; i < csr.n_nz; i++)
    {
        printf("%lf ", csr.nums[i]);
    }
    printf("\n");
    for (size_t i = 0; i < csr.n_nz; i++)
    {
        printf("%zu ", csr.idx[i]);
    }
    printf("\n");
    for (size_t i = 0; i < csr.n_rows; i++)
    {
        printf("%zu ", csr.start[i]);
    }
    printf("\n");


    for (size_t i = 0; i < csc.n_nz; i++)
    {
        printf("%lf ", csc.nums[i]);
    }
    printf("\n");
    for (size_t i = 0; i < csr.n_nz; i++)
    {
        printf("%zu ", csc.idx[i]);
    }
    printf("\n");
    for (size_t i = 0; i < csr.n_rows; i++)
    {
        printf("%zu ", csc.start[i]);
    }
    printf("\n");

    // Проверка корректности размерностей матриц
    if (std1.columns != std2.rows)
    {
        free_std_matrix(&std1);
        free_std_matrix(&std2);
        free_sparse_matrix(&csr);
        free_sparse_matrix(&csc);
        err_message(ERR_DIFFERENT_MATRIX_SIZES);
        return ERR_DIFFERENT_MATRIX_SIZES;
    }

    err = set_std_matrix(&std_res, std1.rows, std2.columns);
    if (err)
    {
        free_std_matrix(&std1);
        free_std_matrix(&std2);
        free_sparse_matrix(&csr);
        free_sparse_matrix(&csc);
        err_message(err);
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
        err_message(err);
        return err;
    }

    // init_sparse_matrix(&csr, &std1);
    // init_sparse_matrix(&csc, &std2);

    // Multiplication
    stats_t stats;
    int err1, err2;
    unsigned long long start, end;

    err1 = microseconds_now(&start);
    std_matrix_multiply(&std1, &std2, &std_res);
    err2 = microseconds_now(&end);

    if (err1 | err2)
    {
        err_message(ERR_TIMER);
        return ERR_TIMER;
    }
    stats.std_matrix_time = end - start;


    err1 = microseconds_now(&start);
    sparse_matrix_multiply(&csr, &csc, &sparse_res);
    err2 = microseconds_now(&end);

    if (err1 | err2)
    {
        err_message(ERR_TIMER);
        return ERR_TIMER;
    }
    stats.sparse_matrix_time = end - start;

    stats.std_matrix_mem = sizeof(double) * (std1.columns * std1.rows + std2.columns * std2.rows + std_res.rows * std_res.columns);
    stats.std_matrix_mem += sizeof(double*) * (std1.rows + std2.rows + std_res.rows);
    stats.sparse_matrix_mem = sizeof(double) * csr.n_nz + sizeof(size_t) * csr.n_nz + sizeof(size_t) * csr.n_rows;
    stats.sparse_matrix_mem += sizeof(double) * csc.n_nz + sizeof(size_t) * csc.n_nz + sizeof(size_t) * csc.n_cols;
    stats.sparse_matrix_mem += sizeof(double) * sparse_res.n_nz + sizeof(size_t) * sparse_res.n_nz + sizeof(size_t) * sparse_res.n_rows;
   
    if (output)
    {
        err = write_sparse_matrix_file(argv[3], &sparse_res);
    }
    else if (print_matrix())
    {   
        printf("---------------------------------------------------------------------------------\n");
        printf("Результат:\n");
        write_sparse_matrix(stdout, &sparse_res);
    }

    print_stats(&stats, &csr, &csc);

    free_std_matrix(&std1);
    free_std_matrix(&std2);
    free_std_matrix(&std_res);
    free_sparse_matrix(&csr);
    free_sparse_matrix(&csc);
    free_sparse_matrix(&sparse_res);

    if (err)
    {
        err_message(ERR_TIMER);
        return err;
    }

    return STATUS_OK;
}

#include "writer.h"

int write_std_matrix(FILE *file, std_matrix_t *matrix)
{
    //int input;
    fprintf(file, "%zu %zu\n", matrix->rows, matrix->columns);

    for (size_t i = 0; i < matrix->rows; i++)
    {
        for (size_t j = 0; j < matrix->columns; j++)
        {
            fprintf(file, "%lf ", matrix->ptrs[i][j]);
        }
        fprintf(file, "\n");
    }

    return STATUS_OK;
}


int write_std_matrix_file(char *file_name, std_matrix_t *matrix)
{
    FILE *file = fopen(file_name, "w");
    if (file == NULL)
    {
        return ERR_FILE_OPEN;
    }

    int err = write_std_matrix(file, matrix);
    fclose(file);
    if (err)
    {
        return err;
    }

    return STATUS_OK;
}

void write_sparse_matrix(FILE *file, sparse_matrix_t *matrix)
{
    fprintf(file, "%zu %zu\n", matrix->n_rows, matrix->n_cols);

    size_t k = 0;
    for (size_t i = 0; i < matrix->n_rows; i++)
    {
        for (size_t j = 0; j < matrix->n_cols; j++)
        {
            if (matrix->idx[k] == j && k >= matrix->start[i] && k < matrix->start[i + 1])
            {
                fprintf(file, "%lf ", matrix->nums[k]);
                k++;
            }
            else
            {
                fprintf(file, "%lf ", 0.0);
            }
        }
        fprintf(file, "\n");
    }
}

int write_sparse_matrix_file(char *file_name, sparse_matrix_t *matrix)
{
    FILE *file = fopen(file_name, "w");
    if (file == NULL)
    {
        return ERR_FILE_OPEN;
    }

    write_sparse_matrix(file, matrix);
    fclose(file);

    return STATUS_OK;
}

bool print_matrix()
{
    int a;
    printf("Вывести матрицу на экран? (Да - 1 / Нет - 0): ");
    int input = scanf("%d", &a);
    if (input != 1 || a != 1)
    {
        return false;
    }

    return true;
}

void print_stats(stats_t *stats, sparse_matrix_t *csr, sparse_matrix_t *csc)
{
    double fullness1 = (double) csr->n_nz / (double) (csr->n_rows * csr->n_cols) * 100;
    double fullness2 = (double) csc->n_nz / (double) (csc->n_rows * csc->n_cols) * 100;

    printf("\n=================================================================================\n");
    printf("Сравнение эффективности умножения разреженных матриц стандартным методом и \n");
    printf("c помощью CSR/CSC матриц при заполненности %lf%% и %lf%%).\n", fullness1, fullness2);
    printf("Размерности входных матриц: n1 = %zu, m1 = %zu, n2 = %zu, m2 = %zu.\n\n", csr->n_rows, csr->n_cols, csc->n_rows, csc->n_cols);
    printf("Данные приведены в микросекундах (время) и байтах (пямять).\n");
    printf("---------------------------------------------------------------------------------\n");

    printf("Стандартный метод умножения матриц:\n");
    printf("\t- time: %lld мкс\n\t- memory: %d байт\n", stats->std_matrix_time, stats->std_matrix_mem);
    printf("Умножение CSR и CSC матриц:\n");
    printf("\t- time: %lld мкс\n\t- memory: %d байт\n", stats->sparse_matrix_time, stats->sparse_matrix_mem);

    printf("---------------------------------------------------------------------------------\n");

    float gain_time, gain_mem;

    printf("Time:\n\t");
    if (stats->std_matrix_time == 0 || stats->sparse_matrix_time == 0)
    {
        printf("- Процентное соотношение не может быть вычислено.\n");
    } 
    else if (stats->std_matrix_time < stats->sparse_matrix_time)
    {
        gain_time = (float) (stats->sparse_matrix_time - stats->std_matrix_time) / (float) stats->std_matrix_time * 100;
        printf("- Умножение стандартным методом быстрее на %f%%\n", gain_time);
    }
    else if (stats->std_matrix_time > stats->sparse_matrix_time)
    {
        gain_time = (float) (stats->std_matrix_time - stats->sparse_matrix_time) / (float) stats->sparse_matrix_time * 100;
        printf("- Умножение CSR и СSC матриц быстрее на %f%%\n", gain_time);
    }
    else
    {
        printf("- Для данных матриц методы умножения равны по времени.\n");
    }

    printf("\nMemory:\n\t");
    if (stats->sparse_matrix_mem == 0 || stats->std_matrix_mem == 0)
    {
        printf("- Процентное соотношение не может быть вычислено.\n");
    } 
    else if (stats->std_matrix_mem < stats->sparse_matrix_mem)
    {
        gain_mem = (float) (stats->sparse_matrix_mem - stats->std_matrix_mem) / (float) stats->std_matrix_mem * 100;
        printf("- Метод умножения CSR и CSC матриц использует на %f%% больше памяти.\n", gain_mem);
    }
    else if (stats->std_matrix_mem > stats->sparse_matrix_mem)
    {
        gain_mem = (float) (stats->std_matrix_mem - stats->sparse_matrix_mem) / (float) stats->sparse_matrix_mem * 100;
        printf("- Стандартный метод умножения матриц использует на %f%% больше памяти.\n", gain_mem);
    }
    else
    {
        printf("- Для данных матриц методы умножения равны по памяти.\n");
    }
    
    printf("=================================================================================\n");
}

void show_menu()
{
    printf("=================================================================================\n");
    printf("Умножение разреженных матриц стандартным методом и с помощью CSR/CSC матриц.\n");
    printf("---------------------------------------------------------------------------------\n");
    printf("При вводе матриц сначала указываются размерности в виде целых чисел не менее 1,\n");
    printf("затем элементы первой строки, потом второй и т.д.\n\n");
    printf("!!! ОБРАТИТИЕ ВНИМАНИЕ !!!\nКол-во столбцов первой матрицы должно совпадать с кол-вом строк второй матрицы.\n");
    printf("i - индекс строки, j - индекс столбца, value - значение элемента a[i][j]\n");
    printf("При вводе первой матрицы (CSR) данные записываются по строкам, а при вводе второй " \
    "матрицы  - по столбцам.\n");
    printf("---------------------------------------------------------------------------------\n");
}

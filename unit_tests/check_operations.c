#include "check_operations.h"

bool is_equal(matrix_t *a, matrix_t *b)
{
    for (size_t i = 0; i < a->rows; i++)
    {
        for (size_t j = 0; j < a->columns; j++)
        {
            if (fabs(a->ptrs[i][j] - b->ptrs[i][j]) > EPS)
            {
                return false;
            }
        }
    }

    return true;
}

void init_matrix(matrix_t *matrix, double static_matrix[][MAX_SIZE])
{
    for (size_t i = 0; i < matrix->rows; i++)
    {
        for (size_t j = 0; j < matrix->columns; j++)
        {
           matrix->ptrs[i][j] = static_matrix[i][j];
        }
    }
}

int allocate_all(matrix_t *m1, matrix_t *m2, matrix_t *result, matrix_t *expected, size_t sizes[])
{
    int err = set_matrix(m1, sizes[0], sizes[1]);
    if (err)
    {
        return ERR_MEMORY_ALLOCATION;
    } 
    err = set_matrix(m2, sizes[2], sizes[3]);
    if (err)
    {
        free_matrix(m1);
        return ERR_MEMORY_ALLOCATION;
    }
    err = set_matrix(result, sizes[4], sizes[5]);
    if (err)
    {
        free_matrix(m1);
        free_matrix(m2);
        return ERR_MEMORY_ALLOCATION;
    }
    err = set_matrix(expected, sizes[6], sizes[7]);
    if (err)
    {
        free_matrix(m1);
        free_matrix(m2);
        free_matrix(result);
        return ERR_MEMORY_ALLOCATION;
    }

    return STATUS_OK;
}


// SUM

START_TEST(test_sum_square_matrix) 
{
    size_t sizes[] = {5,5,5,5,5,5,5,5};
    matrix_t m1, m2, result, expected;
    ck_assert_int_eq(allocate_all(&m1, &m2, &result, &expected, sizes), STATUS_OK);

    for (int i = 0; i < (int) m1.rows; i++)
    {
        for (int j = 0; j < (int) m1.columns; j++)
        {
           expected.ptrs[i][j] = 0;
           m1.ptrs[i][j] = i * m1.columns + j;
           m2.ptrs[i][j] = -(i * (int) m1.columns + j);
        }
    }

    sum(&m1, &m2, &result);

    ck_assert(is_equal(&result, &expected));
    free_matrix(&m1);
    free_matrix(&m2);
    free_matrix(&result);
    free_matrix(&expected);
}
END_TEST


START_TEST(test_sum_one_elem_matrix) 
{
    size_t sizes[] = {1,1,1,1,1,1,1,1};
    matrix_t m1, m2, result, expected;
    ck_assert_int_eq(allocate_all(&m1, &m2, &result, &expected, sizes), STATUS_OK);

    expected.ptrs[0][0] = 247.0;
    m1.ptrs[0][0] = 123.5;
    m2.ptrs[0][0] = 123.5;

    sum(&m1, &m2, &result);

    ck_assert(is_equal(&result, &expected));
    free_matrix(&m1);
    free_matrix(&m2);
    free_matrix(&result);
    free_matrix(&expected);
}
END_TEST


START_TEST(test_sum_non_square_matrix) 
{
    size_t sizes[] = {3,5,3,5,3,5,3,5};
    matrix_t m1, m2, result, expected;
    ck_assert_int_eq(allocate_all(&m1, &m2, &result, &expected, sizes), STATUS_OK);

    for (int i = 0; i < (int) m1.rows; i++)
    {
        for (int j = 0; j < (int) m1.columns; j++)
        {
           expected.ptrs[i][j] = 0;
           m1.ptrs[i][j] = i * m1.columns + j;
           m2.ptrs[i][j] = -(i * (int) m1.columns + j);
        }
    }

    sum(&m1, &m2, &result);

    ck_assert(is_equal(&result, &expected));
    free_matrix(&m1);
    free_matrix(&m2);
    free_matrix(&result);
    free_matrix(&expected);
}
END_TEST



// MULTIPLY

START_TEST(test_multiply_square_matrix)
{
    size_t sizes[] = {3,3,3,3,3,3,3,3};
    matrix_t m1, m2, result, expected;
    ck_assert_int_eq(allocate_all(&m1, &m2, &result, &expected, sizes), STATUS_OK);

    for (int i = 0; i < (int) m1.rows; i++)
    {
        for (int j = 0; j < (int) m1.columns; j++)
        {
           m1.ptrs[i][j] = i * m1.columns + j + 1;
           m2.ptrs[i][j] = i * m1.columns + j + 1;
        }
    }

    double expected_matrix[MAX_SIZE][MAX_SIZE] = {
        {30, 36, 42},
        {66, 81, 96},
        {102, 126, 150}
    };

    init_matrix(&expected, expected_matrix);
    
    multiply(&m1, &m2, &result);

    ck_assert(is_equal(&result, &expected));
    free_matrix(&m1);
    free_matrix(&m2);
    free_matrix(&result);
    free_matrix(&expected);
}
END_TEST


START_TEST(test_multiply_non_square_matrix) 
{
    size_t sizes[] = {3,2,2,3,3,3,3,3};
    matrix_t m1, m2, result, expected;
    ck_assert_int_eq(allocate_all(&m1, &m2, &result, &expected, sizes), STATUS_OK);

    for (int i = 0; i < (int) m1.rows; i++)
    {
        for (int j = 0; j < (int) m1.columns; j++)
        {
           m1.ptrs[i][j] = i * m1.columns + j + 1;
           m2.ptrs[j][i] = j * m1.rows + i + 1;
        }
    }

    double expected_matrix[MAX_SIZE][MAX_SIZE] = {
        {9, 12, 15},
        {19, 26, 33},
        {29, 40, 51}
    };
    init_matrix(&expected, expected_matrix);
    
    multiply(&m1, &m2, &result);

    ck_assert(is_equal(&result, &expected));
    free_matrix(&m1);
    free_matrix(&m2);
    free_matrix(&result);
    free_matrix(&expected);
}
END_TEST


START_TEST(test_multiply_one_elem_matrix) 
{
    size_t sizes[] = {1,1,1,1,1,1,1,1};
    matrix_t m1, m2, result, expected;
    ck_assert_int_eq(allocate_all(&m1, &m2, &result, &expected, sizes), STATUS_OK);

    expected.ptrs[0][0] = 25.0;
    m1.ptrs[0][0] = 5.0;
    m2.ptrs[0][0] = 5.0;

    multiply(&m1, &m2, &result);

    ck_assert(is_equal(&result, &expected));
    free_matrix(&m1);
    free_matrix(&m2);
    free_matrix(&result);
    free_matrix(&expected);
}
END_TEST


START_TEST(test_multiply_unit_matrix)
{
    size_t sizes[] = {3,3,3,3,3,3,3,3};
    matrix_t m1, m2, result, expected;
    ck_assert_int_eq(allocate_all(&m1, &m2, &result, &expected, sizes), STATUS_OK);

    for (int i = 0; i < (int) m1.rows; i++)
    {
        for (int j = 0; j < (int) m1.columns; j++)
        {
            if (i == j)
            {
                m2.ptrs[i][j] = 1;
            }
            else
            {
                m2.ptrs[i][j] = 0;
            }
            m1.ptrs[i][j] = i * m1.columns + j + 1;
            expected.ptrs[i][j] = i * m1.columns + j + 1;
        }
    }
    
    multiply(&m1, &m2, &result);

    ck_assert(is_equal(&result, &expected));
    free_matrix(&m1);
    free_matrix(&m2);
    free_matrix(&result);
    free_matrix(&expected);
}
END_TEST


START_TEST(test_multiply_inverse_matrix) 
{
    size_t sizes[] = {3,3,3,3,3,3,3,3};
    matrix_t m1, m2, result, expected;
    ck_assert_int_eq(allocate_all(&m1, &m2, &result, &expected, sizes), STATUS_OK);

    unit_matrix(&expected);

    double matrix1[MAX_SIZE][MAX_SIZE] = {
        {2, 0, 1},
        {0, -3, -1},
        {-2, 4, 0}
    };
    double matrix2[MAX_SIZE][MAX_SIZE] = {
        {2, 2, 1.5},
        {1, 1, 1},
        {-3, -4, -3}
    };
    init_matrix(&m1, matrix1);
    init_matrix(&m2, matrix2);
    
    multiply(&m1, &m2, &result);

    ck_assert(is_equal(&result, &expected));
    free_matrix(&m1);
    free_matrix(&m2);
    free_matrix(&result);
    free_matrix(&expected);
}
END_TEST



// GET_INVERSE_MATRIX

START_TEST(test_get_inverse_matrix_inverse_matrix_exists) 
{
    size_t sizes[] = {3,3,3,3,3,3,3,3};
    matrix_t m1, m2, result, expected;
    ck_assert_int_eq(allocate_all(&m1, &m2, &result, &expected, sizes), STATUS_OK);

    unit_matrix(&m2);

    double matrix1[MAX_SIZE][MAX_SIZE] = {
        {2, 0, 1},
        {0, -3, -1},
        {-2, 4, 0}
    };
    double expected_matrix[MAX_SIZE][MAX_SIZE] = {
        {2, 2, 1.5},
        {1, 1, 1},
        {-3, -4, -3}
    };
    init_matrix(&m1, matrix1);
    init_matrix(&expected, expected_matrix);
    
    int err = get_inverse_matrix(&m1, &m2, &result);
    ck_assert_int_eq(err, STATUS_OK);

    ck_assert(is_equal(&result, &expected));
    free_matrix(&m1);
    free_matrix(&m2);
    free_matrix(&result);
    free_matrix(&expected);
}
END_TEST

// negative case
START_TEST(test_get_inverse_matrix_inverse_matrix_does_not_exist) 
{
    matrix_t m1, m2, result;

    // Allocating
    int err = set_matrix(&m1, 3, 3);
    ck_assert_int_eq(err, STATUS_OK);
   
    err = set_matrix(&m2, 3, 3);
    ck_assert_int_eq(err, STATUS_OK);
    if (err)
    {
        free_matrix(&m1);
    }

    err = set_matrix(&result, 3, 3);
    ck_assert_int_eq(err, STATUS_OK);
    if (err)
    {
        free_matrix(&m1);
        free_matrix(&m2);
    }
   

    double matrix1[MAX_SIZE][MAX_SIZE] = {
        {1, 2, 3},
        {4, 5 ,6},
        {7, 8, 9}
    };
    double matrix2[MAX_SIZE][MAX_SIZE] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };
    init_matrix(&m1, matrix1);
    init_matrix(&m2, matrix2);
    
    err = get_inverse_matrix(&m1, &m2, &result);
    ck_assert_int_eq(err, ERR_NO_SINGLE_SOLUTION);

    free_matrix(&m1);
    free_matrix(&m2);
    free_matrix(&result);
}
END_TEST

START_TEST(test_get_inverse_matrix_one_elem_matrix) 
{
    size_t sizes[] = {1,1,1,1,1,1,1,1};
    matrix_t m1, m2, result, expected;
    ck_assert_int_eq(allocate_all(&m1, &m2, &result, &expected, sizes), STATUS_OK);

    expected.ptrs[0][0] = 0.2;
    m1.ptrs[0][0] = 5.0;
    m2.ptrs[0][0] = 1.0;

    int err = get_inverse_matrix(&m1, &m2, &result);
    ck_assert_int_eq(err, STATUS_OK);

    ck_assert(is_equal(&result, &expected));
    free_matrix(&m1);
    free_matrix(&m2);
    free_matrix(&result);
    free_matrix(&expected);
}
END_TEST


Suite* sum_suite(void)
{
    Suite *s;
    TCase *tc;

    s = suite_create("sum");

    tc = tcase_create(""); 
    tcase_add_test(tc, test_sum_square_matrix);
    tcase_add_test(tc, test_sum_non_square_matrix);
    tcase_add_test(tc, test_sum_one_elem_matrix);

    suite_add_tcase(s, tc);

    return s;
}


Suite* multiply_suite(void)
{
    Suite *s;
    TCase *tc;

    s = suite_create("multiply");

    tc = tcase_create(""); 
    tcase_add_test(tc, test_multiply_square_matrix);
    tcase_add_test(tc, test_multiply_non_square_matrix);
    tcase_add_test(tc, test_multiply_one_elem_matrix);
    tcase_add_test(tc, test_multiply_unit_matrix);
    tcase_add_test(tc, test_multiply_inverse_matrix);

    suite_add_tcase(s, tc);

    return s;
}


Suite* get_inverse_matrix_suite(void)
{
    Suite *s;
    TCase *tc_pos, *tc_neg;

    s = suite_create("get_inverse_matrix");

    tc_pos = tcase_create("positive"); 
    tcase_add_test(tc_pos, test_get_inverse_matrix_inverse_matrix_exists);
    tcase_add_test(tc_pos, test_get_inverse_matrix_one_elem_matrix);

    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("negative"); 
    tcase_add_test(tc_pos, test_get_inverse_matrix_inverse_matrix_does_not_exist);
    
    suite_add_tcase(s, tc_neg);

    return s;
}


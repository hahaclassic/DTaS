#include "operations.h"


void std_matrix_multiply(std_matrix_t *matrix1, std_matrix_t *matrix2, std_matrix_t *result)
{
    for (size_t i = 0; i < matrix1->rows; i++)
    {
        for (size_t j = 0; j < matrix2->columns; j++)
        {
            result->nums[i][j] = 0;
            for (size_t k = 0; k < matrix1->columns; k++)
            {
                result->nums[i][j] += matrix1->nums[i][k] * matrix2->nums[k][j];
            }
        }
    }
}




double get_num(size_t idx, size_t beg, size_t end, vec_matrix_t *m1, vec_matrix_t *m2)
{

}



void vec_matrix_multiply(vec_matrix_t *matrix1, vec_matrix_t *matrix2, vec_matrix_t *result)
{
    result->rows = 0;
    result->columns = 0;

    for (size_t i = 0; i < matrix1->rows; i++)
    {
        for (size_t j = 0; j < matrix2->columns; i++)
        {   
            if 
        }
    }


    for (size_t i = 0; i < matrix1->rows; i++)
    {
        if (i != matrix1->rows)
        {
            get_num()
        }



    }


}

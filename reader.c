#include "reader.h"

#define MAX_BUFFER_INT_LEN 40 
#define MAX_BUFFER_FLOAT_LEN 50
#define MAX_DIGIT_LEN 5

int get_int_number(char *str, big_int value) {
 
    size_t i = 0, count = 0;
    size_t digit = 0;

    while (str[i] != '\0') 
    {
        if (!isdigit(str[i])) 
        {
            return ERR_READ_INT;
        }
        else
        {
            count++;
        }

        if (count % 5 == 0) { 
            char buffer[MAX_DIGIT_LEN + 1];
            char *check;
            check = strncpy(buffer, &str[i - count], MAX_DIGIT_LEN);

            value[digit] = atoi(buffer);
            count = 0;
            digit++;
        }
    }

    return STATUS_OK;
}

// int float_validation() {

// }

// int get_int_number(big_int num)
// {
//     int symbol; // Current symbol
//     int exp = 10000;
//     size_t digit_index = MAX_INT - 1; // Текущий разряд числа num в 10000-СС
//     short significant = FALSE; // Для пропуска незначащих 0

//     while ((symbol = getchar()) != '\n' && symbol != EOF) 
//     {
//         if (digit_index > MAX_INT)
//         {
//             return ERR_BUFFER_OVERFLOW;
//         }

//         if (!isdigit(symbol)) 
//         {
//             return ERR_READ_INT;
//         }
//         else if (symbol == '0' && !significant )
//         {
//             continue;
//         }
//         else
//         {
//             significant = TRUE;

//             num[digit_index] += (symbol - '0') * exp;
//             exp /= 10;

//             if (!exp) {
//                 exp = 10000;
//                 digit_index++;
//             }
//         }

//     }

//     return STATUS_OK;
// }

int get_str(char *str, size_t max, size_t *len)
{
    int symbol;
    short significant = FALSE;
    size_t i = 0;

    while ((symbol = getchar()) != '\n' && symbol != EOF)
    {
        if (symbol != '0')
        {
            significant = TRUE;
        }
        else 
        {
            continue;
        }

        if (i > max - 1)
        {
            return ERR_BUFFER_OVERFLOW;
        }
        str[i++] = symbol;
    }
    str[i] = '\0';
    *len = i;

    return STATUS_OK;
}

int read_data(big_int int_num, struct big_float *float_num) 
{
    int err;
    char buff_int[MAX_BUFFER_INT_LEN + 1];
    char buff_float[MAX_BUFFER_FLOAT_LEN + 1];
    size_t len_int = 0, len_float = 0;

    // sendStartInfo();

    printf("Введите целое число: ");
    err = get_str(int_num, MAX_BUFFER_INT_LEN, &len_int);
    if (err)
    {
        return err;
    }



    for (int i = 0; i < MAX_INT; i++) 
    {
        printf("%d", int_num[i]);
    }
    printf("\n");

    printf("%c\n", float_num->mantissa_sign);

    return STATUS_OK;
}


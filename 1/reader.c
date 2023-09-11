#include "reader.h"

#define MAX_BUFFER_INT_LEN 40 
#define MAX_BUFFER_FLOAT_LEN 50
#define MAX_DIGIT_LEN 4

int get_int_number(char *str, struct big_int *val, int len) {
 
    size_t count = 0;
    size_t digit = 0;
    short sign = FALSE;

    val->sign = '+';

    for (int i = len - 1; i >= 0; i--)
    {
        if ((str[i] == '+' || str[i] == '-') && !sign)
        {
            val->sign = str[i];
            sign = TRUE;
            continue;
        }

        if (!isdigit(str[i])) 
        {
            return ERR_READ_INT;
        }

        sign = TRUE; 

        count++;
        if (count == 4 || i == 0)
        {
            char buffer[MAX_DIGIT_LEN + 1];
            char *check;
            check = strncpy(buffer, &str[i], count);
            buffer[count] = '\0';
            if (check == NULL)
            {
                return ERR_STR_CMD;
            }

            val->num[digit] = atoi(buffer);
            count = 0;
            digit++;
        }
    }

    return STATUS_OK;
}

int get_float_number(char *str, struct big_float *val, int len)
{
    int e_letter;
    int err = check_float(str, &e_letter);
    if (err)
    {
        return err;
    }

    // Стандартные знаки
    val->mantissa_sign = '+';
    val->exp_sign = '+';

    int count_special[2] = {0, 0}; // первый элемент - кол-во знаков +/-, второй - кол-во Е/e
    size_t count_digits = 0; // Счетчик цифр одного порядка
    size_t digit = 0; // Счетчик порядков
    
    char *check; // Для проверки результа выполнения функций по обработке строк
    
    for (int i = len - 1; i >= 0; i--)
    {
        printf("%c\n", str[i]);
        switch (check_symbol(str[i]))
        {
        case IS_PLUS_MINUS:
            if (count_special[0] == 1)
            {
                val->mantissa_sign = str[i];
            }
            else 
            {
                val->exp_sign = str[i];
                count_special[0]++;
            }
            break;
        
        case IS_DOT:
            val->point = i;
            break;
        
        case IS_E_LETTER:
            count_special[1]++;
        
            if (count_digits > MAX_EXP)
            {
                return ERR_READ_FLOAT;
            }

            char buffer1[MAX_EXP + 2];
            if (count_special[0] > 0 )
            {
                count_digits++;
            }
            check = strncpy(buffer1, &str[i+1], count_digits);
            printf("Buff1: %s\n", buffer1);
            if (check == NULL)
            {
                return ERR_STR_CMD;
            }
            buffer1[count_digits] = '\0';

            val->exp = atoi(buffer1);
            count_digits = 0;
            break;

        case IS_DIGIT:
            count_digits++;

            if ((count_special[1] == 0 && e_letter) || (count_digits != 4 && i != 0))
            {
                continue;
            }

            char buffer[MAX_DIGIT_LEN + 1];
            check = strncpy(buffer, &str[i], count_digits);
            printf("Buff2: %s\n", buffer);
            if (check == NULL)
            {
                return ERR_STR_CMD;
            }
            buffer[count_digits] = '\0';

            val->mantissa[digit] = atoi(buffer);
            count_digits = 0;
            digit++;
            break;
        }
    }

    return STATUS_OK;
}

int get_str(char *str, size_t max, int *len)
{
    int symbol;
    short significant = FALSE;
    size_t i = 0;

    while ((symbol = getchar()) != '\n' && symbol != EOF)
    {   
        if (symbol == ' ')
        {
            return ERR_INVALID_CHAR;
        }
        if ( symbol == '0' && !significant)
        {
            continue;
        }
        else if (symbol != '0' || symbol == '+' || symbol == '-')
        {
            significant = TRUE;
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

int read_data(struct big_int *int_num, struct big_float *float_num) 
{
    int err;
    char buff_int[MAX_BUFFER_INT_LEN + 1] = "\0";
    char buff_float[MAX_BUFFER_FLOAT_LEN + 1] = "\0";
    int len_int = 0, len_float = 0;

    // sendStartInfo();

    printf("Введите целое число: ");
    err = get_str(buff_int, MAX_BUFFER_INT_LEN, &len_int);
    if (err)
    {
        return err;
    }

    printf("%s\n", buff_int);

    err = get_int_number(buff_int, int_num, len_int);
    if (err)
    {
        return err;
    }

    printf("%c", int_num->sign);
    for (int i = 0; i < MAX_INT; i++) 
    {
        printf("%d ", int_num->num[i]);
    }
    printf("\n");


    printf("Введите вещественное число: ");
    err = get_str(buff_float, MAX_BUFFER_FLOAT_LEN, &len_float);
    if (err)
    {
        return err;
    }

    printf("\n\n%s\n", buff_float);

    err = get_float_number(buff_float, float_num, len_float);
    if (err)
    {
        return err;
    }

    printf("%c", float_num->mantissa_sign);
    for (int i = 0; i < MAX_FLOAT; i++) 
    {
        printf("%d ", float_num->mantissa[i]);
    }
    printf("\n");
    printf("%c", float_num->exp_sign);
    printf("%d", float_num->exp);
    printf("\n");
    printf("%d\n", float_num->point);

    return STATUS_OK;
}

float a = 23e-3;
#include "reader.h"


int get_int_number(char *str, big_float *num, int len) {
 
    num->mantissa_sign = true;
    int end = 0;
    if (str[0] == '+' || str[0] == '-') 
    {
        if (str[0] == '-') 
        {
            num->mantissa_sign = false;
        }
        end = 1;
    }

    if (len - end > MAX_MANTISSA)
    {
        return ERR_BUFFER_OVERFLOW;
    } 

    int count = 0;
    int digit_count = 0; // Счетчик кол-ва разрядов в 10000-ой С/С

    for (int i = len - 1; i >= end; i--)
    {
        if (!isdigit(str[i])) 
        {
            return ERR_READ_INT;
        }
        
        count++;
    
        if (count == 4 || i == end)
        {
            char buffer[MAX_DIGIT_LEN + 1];
            char *check;
            check = strncpy(buffer, &str[i], count);

            if (check == NULL)
            {
                return ERR_STR_CMD;
            }

            buffer[count] = '\0';
            num->mantissa[digit_count] = atoi(buffer);
            count = 0;
            digit_count++;
        }
    }

    num->len = digit_count;
    num->exp = len - end;

    return STATUS_OK;
}


int get_mantissa(char *str, big_float *num)
{
    // Определение знака мантиссы
    num->mantissa_sign = true;
    int end = 0;
    if (str[0] == '+' || str[0] == '-') 
    {
        if (str[0] == '-') 
        {
            num->mantissa_sign = false;
        }
        end = 1;
    }

    if (strlen(&str[end]) > MAX_FLOAT_MANTISSA + 1)
    {
        return ERR_BUFFER_OVERFLOW;
    }

    // Определение местоположения точки
    int point_index = -1;
    int point_count = 0;
    bool is_significant = false;
    for (size_t i = end; i < strlen(str); i++)
    {
        if (str[i] != '.' && str[i] != '0')
        {
            is_significant = true;
        }
        point_count = i - end;
        if (str[i] == '.' && (is_significant || i == 0))
        {
            point_index = i;
            break;
        }
    }

    // Получаем мантиссу без точки
    char mantissa[MAX_FLOAT_MANTISSA + 2] = "\0";
    if (point_index == 0)
    {
        for (size_t i = 1; i < strlen(str); i++)
        {
            if (str[i] != '0')
            {
                break;
            }
            else
            {
                point_index = i;
                point_count--;
            }
        }

        strcat(mantissa, &str[point_index + 1]);

    } else if (point_index != -1)
    {
        strncat(mantissa, &str[end], point_index - end);
        strcat(mantissa, &str[point_index + 1]);
    }
    else
    {
        point_count++;
        strcat(mantissa, &str[end]);
    }

    if (strlen(mantissa) > MAX_FLOAT_MANTISSA)
    {
        return ERR_BUFFER_OVERFLOW;
    }

    int count = 0;
    int digit_count = 0; // Счетчик кол-ва разрядов в 10000-ой С/С

    for (int i = strlen(mantissa) - 1; i >= 0; i--)
    {
        if (!isdigit(mantissa[i])) 
        {
            return ERR_READ_MANTISSA;
        }
        
        count++;
    
        if (count == 4 || i == 0)
        {
            char buffer[MAX_DIGIT_LEN + 1];
            char *check;
            check = strncpy(buffer, &mantissa[i], count);

            if (check == NULL)
            {
                return ERR_STR_CMD;
            }

            buffer[count] = '\0';
            num->mantissa[digit_count] = atoi(buffer);
            count = 0;
            digit_count++;
        }
    }

    num->len = digit_count;
    num->exp += point_count;

    return STATUS_OK;
}

int get_exp(char *str, big_float *num)
{    
    int end = 0;
    int is_negative = false;
    if (str[0] == '+' || str[0] == '-') 
    {
        if (str[0] == '-') 
        {
            is_negative = true;
        }
        end = 1;
    }

    if (strlen(str) - end > MAX_EXP)
    {
        return ERR_BUFFER_OVERFLOW;
    }


    for (size_t i = end; i < strlen(str); i++)
    {
        if (!isdigit(str[i])) 
        {
            return ERR_READ_EXP;
        }
    }

    int exp = atoi(&str[end]);
    if (exp > MAX_EXP_NUM) {
        return ERR_BUFFER_OVERFLOW;
    }
    if (is_negative)
    {
        exp *= -1;
    }

    num->exp += exp;

    return STATUS_OK;
}

int get_float_number(char *str, big_float *num, int len)
{
    // Поиск E/e
    int e_index = -1;
    for (int i = 0; i < len; i++)
    {
        if (str[i] == 'E' || str[i] == 'e') 
        {
            e_index = i;
        }
    }

    if (e_index == 0 || e_index == len - 1)
    {
        return ERR_READ_FLOAT;
    }
    if (e_index == len - 2 && (str[strlen(str)-1] == '-' || str[strlen(str)-1] == '+'))
    {
        return ERR_READ_FLOAT;
    }


    int count;
    if (e_index == -1)
    {
        count = strlen(str);
    }
    else
    {
        count = e_index;
    }


    // Получение строк, содержащих мантиссу и порядок
    char mantissa[MAX_FLOAT_LEN + 1] = "\0";
    char exp[MAX_FLOAT_LEN + 1] = "\0";

    char *check = strncpy(mantissa, str, count);
    if (check == NULL)
    {
        return ERR_STR_CMD;
    }
    mantissa[count] = '\0';


    if (e_index != -1)
    {
        check = strcpy(exp, &str[e_index+1]);
        if (check == NULL)
        {
            return ERR_STR_CMD;
        }
        exp[strlen(str) - e_index] = '\0';
    }

    // Получение мантиссы и порядка
    int err = get_mantissa(mantissa, num);
    if (err)
    {
        return err;
    }


    if (e_index != -1)
    {
        err = get_exp(exp, num);
        if (err)
        {
            return err;
        }
    }

    return STATUS_OK;
}

int get_str(char *str, size_t max, int *len)
{
    int symbol, last = '\0';
    bool significant = false;
    size_t i = 0;

    while ((symbol = getchar()) != '\n' && symbol != EOF)
    {   
        if (symbol == ' ')
        {
            return ERR_INVALID_CHAR;
        }

        if (symbol == '0' && !significant)
        {
            last = symbol;
            continue;
        }
        else if (last == '0' && (symbol == 'e' || symbol == 'E'))
        {
            str[i++] = '0';
        }
        else if ((symbol == '+' || symbol == '-') && (last != 'e' && last != 'E' && last != ' ' && last != '\0')) 
        {
            return ERR_INVALID_CHAR;
        }
        else if (symbol != '+' && symbol != '-')
        {
            significant = true;
        }

        if (i > max - 1)
        {
            return ERR_BUFFER_OVERFLOW;
        }
        str[i++] = symbol;
        last = symbol;
    }
    
    if (i == 0 && last == '0')
    {
        str[i++] = last;
    }
    else if (i == 0)
    {
        return ERR_EMPTY_INPUT;
    }
    *len = i;

    str[i] = '\0';

    return STATUS_OK;
}


// Целое число будет представлено в виде вещественного числа для упрощения деления
int read_data(big_float *int_num, big_float *float_num) 
{
    int err;
    char buff_int[MAX_INT_LEN + 1] = "\0";
    int len_int = 0;
    char buff_float[MAX_FLOAT_LEN + 1] = "\0";
    int len_float = 0;

    init_bigfloat(int_num);
    message(INPUT_INT);
    err = get_str(buff_int, MAX_INT_LEN, &len_int);
    if (err)
    {
        return err;
    }

    err = get_int_number(buff_int, int_num, len_int);
    if (err)
    {
        return err;
    }

    init_bigfloat(float_num);
    message(INPUT_FLOAT);
    err = get_str(buff_float, MAX_FLOAT_LEN, &len_float);
    if (err)
    {
        return err;
    }

    err = get_float_number(buff_float, float_num, len_float);
    if (err)
    {
        return err;
    }
   
    return STATUS_OK;
}

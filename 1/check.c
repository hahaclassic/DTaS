#include "check.h"

unsigned short check_symbol(int curr)
{
    if (curr == '.')
        return IS_DOT;
    if (curr == 'E' || curr == 'e')
        return IS_E_LETTER;
    if (curr == '+' || curr == '-')
        return IS_PLUS_MINUS;
    if (isdigit(curr))
        return IS_DIGIT;
    if (isspace(curr))
        return IS_SPACE;
    
    return INVALID_SYMBOL;
}

int check_count(int count[])
{
    if (count[0] > 1 || count[1] > 1 || count[2] > 1 || count[3] > 2)
        return TOO_MANY_SPECIAL_CHAR_ERR;
    
    return STATUS_OK;
}

int check_float(char *str, int *is_e_letter_exist)
{
    int count[5] = {0, 0, 0, 0, 0}; // 0 - space, 1 - dot, 2 - e/E, 3 - +/-, 4 - numbers
    unsigned short last = START, curr; 

    for (size_t i = 0; str[i] != '\0'; i++)
    {
        curr = check_symbol(str[i]);
        switch (curr)
        {
            case IS_SPACE:
                if (last != IS_SPACE && last != START)
                {
                    count[0]++;
                }
                break;
            
            case IS_DOT:
                if (count[2] > 0)
                {
                    return INVALID_SEQUENCE;
                }
                count[1]++;
                break;

            case IS_E_LETTER:
                if (last == START || last == IS_PLUS_MINUS)
                {
                    return INVALID_SEQUENCE;
                }
                else if (last == IS_DOT && count[4] == 0)
                {
                    return INVALID_SEQUENCE;
                }
                count[2]++;
                break;

            case IS_PLUS_MINUS:
                if (last != START && last != IS_E_LETTER && last != IS_SPACE)
                {
                    return INVALID_SEQUENCE;
                }
                count[3]++;
                break;

            case IS_DIGIT:
                count[4] = 1;
                break;

            default:
                return INVALID_SEQUENCE;
        }

        // Проверка на существование пробелов между символами, которые не являются пробелами
        if (last == IS_SPACE && curr != IS_SPACE)
        {
            if (count[0] == 1)
            {
                return TOO_MANY_SPECIAL_CHAR_ERR;
            }
            else
            {
                count[0] = 0;
            }
        }

        // Проверка на количество точек, Е/е, +/- 
        if (check_count(count))
        {
            return TOO_MANY_SPECIAL_CHAR_ERR;
        }

        last = curr;
    }
    
    if (last == IS_E_LETTER || last == IS_PLUS_MINUS || count[4] == 0)
    {
        return INVALID_SEQUENCE;
    }

    *is_e_letter_exist = count[2] > 0;

    return STATUS_OK;
}

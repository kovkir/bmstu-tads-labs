#include <stdio.h>
#include <string.h>

#define MAXIMUM_STRING_LENGHT 39
#define MAXIMUM_LENGTH_OF_MANTISA 30
#define MAXIMUM_ORDER_LENGTH 5
#define MAXIMUM_ORDER_VALUE 99999

#define OK 0
#define TOO_LONG_NUMBER_ENTER 1
#define EMPTY_LINE 2
#define INVALID_CHARACTER 3
#define THERE_MUST_BE_ONE_POINT 4
#define THERE_MUST_BE_TWO_SIGNS 5
#define THERE_SHOULD_BE_ONE_LETTER_E 6
#define NUMBER_MUST_START_WITH_A_SIGN 7
#define ERROR_IN_MANTISSA_NUMBER 8
#define POINT_OUT_OF_PLACE 9
#define WRONG_LENGTH_OF_MANTISSA 10
#define NO_SIGN_IN_FRONT_OF_THE_ORDER_VALUE 11
#define WRONG_ORDER_LENGTH 12
#define OVERFLOW_OCCURRED 13

int string_input_with_validation(char *s, const int n)
{
    int ch, i = 0, points = 0, pros = 0, minuses = 0, quantity_E = 0;
    
    s[0] = 'P';
    
    while ((ch = getchar()) != '\n' && (ch != EOF))
    {
        if (('9' < ch || ch < '0') && ch != '.' && ch != '-' && ch != '+' && ch != 'E')
        {
            printf("В записи числа содержится недопустимый символ! '%c'\n", ch);
            return INVALID_CHARACTER;
        }
        else if (ch == '.')
        {
            points++;
        }
        else if (ch == '+')
        {
            pros++;
        }
        else if (ch == '-')
        {
            minuses++;
        }
        else if (ch == 'E')
        {
            quantity_E++;
        }
            
        if (i == n - 1)
        {
            printf("Слишком длинная запись числа!\n");
            return TOO_LONG_NUMBER_ENTER;
        }
        
        s[i] = ch;
        i++;
    }
    
    if (s[0] == 'P')
    {
        printf("Введена пустая строка!\n");
        return EMPTY_LINE;
    }
    else if (points != 1)
    {
        printf("В записи числа должна быть одна точка! \n\
(по правилам ввода число не может не содержать дробную часть)\n");
        return THERE_MUST_BE_ONE_POINT;
    }
    else if (pros + minuses != 2)
    {
        printf("В записи числа должно быть два знака! \n\
(по правилам ввода число и его порядок должны начинаться со знака)\n");
        return THERE_MUST_BE_TWO_SIGNS;
    }
    else if (quantity_E != 1)
    {
        printf("В записи числа должна быть одна буква E!\n\
(по правилам ввода число вводится только в экспоненциальной форме)\n");
        return THERE_SHOULD_BE_ONE_LETTER_E;
    }
    
    s[i] = '\0';

    return OK;
}

int string_validation(const char *str, int *position_E)
{
    int i = 1, k = 0, points = 0, quantity_E = 0;
    
    if (str[0] != '-' && str[0] != '+')
    {
        printf("Число должно начинаться с знака!\n");
        return NUMBER_MUST_START_WITH_A_SIGN;
    }
    
    while (str[i] != '\0')
    {
        if (quantity_E == 0)
        {
            while (str[i] != 'E')
            {
                if ((str[i] > '9' || str[i] < '0') && str[i] != '.')
                {
                    printf("Ошибка в мантиссе числа. \
Встречен недопустимый символ '%c'\n", str[i]);
                    return ERROR_IN_MANTISSA_NUMBER;
                }
            
                if (str[i] == '.')
                {
                    points++;
                }
            
                k++;
                i++;
            }
        
            if (str[i] == 'E')
            {
                quantity_E = 1;
                *position_E = i;
            }
        
            if (k == 0 || k > MAXIMUM_LENGTH_OF_MANTISA + 1)
            {
                printf("Суммарная длина мантиссы должна иметь от 2 до 30 цифр!\n");
                return WRONG_LENGTH_OF_MANTISSA;
            }
            else if (points == 0 || str[1] == '.' || str[k] == '.')
            {
                printf("Точка находится не на своём месте. \n\
(по правилам ввода мантисса не может не иметь целую или дробную части)\n");
                return POINT_OUT_OF_PLACE;
            }
            else
            {
                k = 0;
            }
        }
        else
        {
            if (str[*position_E + 1] != '+' && str[*position_E + 1] != '-')
            {
                printf("Перед величиной порядка должен идти знак!\n");
                return NO_SIGN_IN_FRONT_OF_THE_ORDER_VALUE;
            }
            else if(i == *position_E + 1)
            {
                i++;
            }
            
            if (str[i] != '\0')
            {
                k++;
            }
        }
        
        i++;
    }

    if (k == 0 || k > MAXIMUM_ORDER_LENGTH)
    {
        printf("Величина порядка должна иметь от 1 до 5 цифр!\n");
        return WRONG_ORDER_LENGTH;
    }
    
    return OK;
}

int convert_string_to_number(const char *string)
{
    int number = 0, n = 1;
    
    if (*string == '-')
    {
        n = -1;
    }
    
    string++;
    
    while (*string != '\0')
    {
        number = number * 10 + *string - '0';
        string++;
    }

    number *= n;
    
    return number;
}

int number_normalization(char *string, const int position_E)
{
    string[position_E] = '0';
    string[position_E + 1] = '\0';
    string++;
    
    size_t i = 0;
    int number_of_shifts = 0;
    char c;
    
    while (string[0] == '0' && string[1] != '.')
    {
        for (int j = 0; string[j] != '\0'; j++)
        {
            string[j] = string[j + 1];
        }
    }
    
    if (string[0] != '0')
    {
        while (string[i] != '.')
        {
            i++;
        }
        
        number_of_shifts += i;
        
        while (i > 0)
        {
            c = string[i - 1];
            string[i - 1] = string[i];
            string[i] = c;
            i--;
        }
        
        i = strlen(string) - 1;
        
        while (i > 0)
        {
            string[i] = string[i - 1];
            i--;
        }
        
        string[0] = '0';
    }
    
    i = strlen(string) - 1;
    
    while (string[i] == '0')
    {
        string[i] = '\0';
        i--;
    }
    
    while (string[2] == '0')
    {
        for (int j = 2; string[j] != '\0'; j++)
        {
            string[j] = string[j + 1];
        }
        
        number_of_shifts--;
    }
    
    if (string[2] == '\0')
    {
        string[2] = '0';
    }
    
    return number_of_shifts;
}

void fill_with_zeros(char *result, const int n)
{
    for (int i = 0; i < n; i++)
    {
        result[i] = '0';
    }
}

void rounding(char *result)
{
    if (result[MAXIMUM_LENGTH_OF_MANTISA] >= '5')
    {
        for (int i = MAXIMUM_LENGTH_OF_MANTISA - 1; i >= 0; i--)
        {
            if (result[i] == '9')
            {
                result[i] = '0';
            }
            else
            {
                result[i]++;
                break;
            }
        }
    }
    
    result[MAXIMUM_LENGTH_OF_MANTISA] = '\0';
    
    int i = MAXIMUM_LENGTH_OF_MANTISA - 1;
    
    while (result[i] == '0')
    {
        result[i] = '\0';
        i--;
    }
}

int multiplication(char *result, int *order, const char *string_1, const char *string_2,
    const int order_1, const int order_2)
{
    *order = order_1 + order_2;

    if (*order > MAXIMUM_ORDER_VALUE || *order * (-1) > MAXIMUM_ORDER_VALUE)
    {
        printf("Произошло переполнение!\n");
        return OVERFLOW_OCCURRED;
    }
    
    result[MAXIMUM_LENGTH_OF_MANTISA * 2] = '\0';
    fill_with_zeros(result, MAXIMUM_LENGTH_OF_MANTISA * 2);
    
    int i = MAXIMUM_LENGTH_OF_MANTISA * 2, remainder, whole_part = 0,
    intermediate_result, k = 0;
    size_t str1, str2, j, u;
    
    str1 = strlen(string_1);
    str2 = strlen(string_2);
    u = str2 -1;
    
    while(u > 2)
    {
        i = MAXIMUM_LENGTH_OF_MANTISA * 2 - 1 - k;
        j = str1 - 1;
        
        while(j > 2)
        {
            intermediate_result = (string_1[j] - '0') * (string_2[u] - '0') + whole_part;
            whole_part = intermediate_result / 10;
            remainder = intermediate_result % 10;
            result[i] += remainder;
            
            if (result[i] > '9')
            {
                result[i] -= 10;
                result[i - 1]++;
            }
            
            i--;
            j--;
        }
        
        if (whole_part != 0)
        {
            result[i] += whole_part;
            
            if (result[i] > '9')
            {
                result[i] -= 10;
                result[i - 1] ++;
            }
        }
        
        whole_part = 0;
        k++;
        u--;
    }
    
    if (result[i - 1] != '0' && i - 2 >= 0)
    {
        result[i - 2] = 'p';
    }
    else if (result[i - 1] == '0')
    {
        result[i - 1] = 'p';
    }
    
    while (result[0] == '0')
    {
        for (int i = 0; result[i] != '\0'; i++)
        {
            result[i] = result[i + 1];
        }
    }
    
    if (result[0] == 'p')
    {
        for (int i = 0; result[i] != '\0'; i++)
        {
            result[i] = result[i + 1];
        }
    }
    
    for (int i = 0; result[i] == '0'; i = 0)
    {
        while (result[i + 1] != '\0')
        {
            result[i] = result[i + 1];
            i++;
        }
        
        *order -= 1;
        result[i] = '\0';
    }
    
    size_t length_str;
    
    length_str = strlen(result);

    if (length_str > MAXIMUM_LENGTH_OF_MANTISA)
    {
        rounding(result);
    }

    return OK;
}

int main(void)
{
    char string_1[MAXIMUM_STRING_LENGHT + 1],
         string_2[MAXIMUM_STRING_LENGHT + 1];
    int r, position_E1 = 0, position_E2 = 0, order_1, order_2, change_of_order;
    
    printf("Смоделировать операцию умножения действительного числа на действительное число.\n\n\
                                   Правила ввода:\n\
1)Числа вводятся только в экспоненциальной форме; \n\
2)Оба числа вводятся со знаком (+) или (-);\n\
3)Порядок числа вводится со знаком (+) или (-);\n\
4)Длина мантиссы не должна превышать 30 цифр;\n\
5)Величина порядка не должна превышать 5 цифр;\n\
6)Латинская буква E должна быть заглавной;\n\
7)В числе должна быть точка;\n\
8)В записи числа не должно быть пробелов;\n\
9)Каждое число вводится на отдельной строке;\n\
10)Перед и после точки должна идти цифра.\n\
                                   Пример:\n\
Введите первое число:\n\
-9.12E+5\n\
Введите второе число:\n\
+0.2E-1\n\
Произведение двух чисел равно:\n\
-0.1824 E +5\n\n\
+-   10        20        31   . E+-5   \n\
-|--------|---------|----------|--|---|\n\n");
    
    printf("Введите первое число:\n");
    r = string_input_with_validation(string_1, MAXIMUM_STRING_LENGHT + 1);
    
    if (r != OK)
    {
        return r;
    }
    
    r = string_validation(string_1, &position_E1);
    
    if (r != OK)
    {
        return r;
    }
    
    order_1 = convert_string_to_number(string_1 + position_E1 + 1);
    change_of_order = number_normalization(string_1, position_E1);
    order_1 += change_of_order;
    
    printf("Введите второе число:\n");
    r = string_input_with_validation(string_2, MAXIMUM_STRING_LENGHT + 1);
    
    if (r != OK)
    {
        return r;
    }
    
    r = string_validation(string_2, &position_E2);
    
    if (r != OK)
    {
        return r;
    }

    order_2 = convert_string_to_number(string_2 + position_E2 + 1);
    change_of_order = number_normalization(string_2, position_E2);
    order_2 += change_of_order;
    
    if (string_1[3] == '0' || string_2[3] == '0')
    {
        printf("Произведение двух чисел равно:\n");
        printf("+0.0 E +0\n");
        return OK;
    }
    
    char result[MAXIMUM_LENGTH_OF_MANTISA * 2 + 1];
    int order;
    
    r = multiplication(result, &order, string_1, string_2, order_1, order_2);
    
    if (r == OVERFLOW_OCCURRED)
    {
        return OVERFLOW_OCCURRED;
    }
    
    printf("Произведение двух чисел равно:\n");
    
    if (string_1[0] != string_2[0])
    {
        printf("-");
    }
    else
    {
        printf("+");
    }
    
    printf("0.%s E ", result);
    
    if (order > 0)
    {
        printf("+");
    }
    
    printf("%d\n", order);
    
    return OK;
}

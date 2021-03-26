#include <stdio.h>
#include <string.h>
#include "../inc/read.h"

int read_the_number_of_records(FILE * f, int * size, const int max_size)
{
    int r;
    char ch;
    
    r = fscanf(f, "%d%c", size, &ch); 

    if (r != 2 || ch != '\n')
    {
        printf("Не удалось прочитать кол-во записей в файле\n");
        return UNKNOWN_NUMBER_OF_ENTRIES_IN_FILE;
    }
    else if (*size <= 0 || *size > max_size)
    {
        printf("Недопустимое кол-во записей в файле\n");
        return INACCEPTABLE_NUMBER_OF_RECORDS_IN_FILE;
    }
    
    return SUCCESS;
}

int read_a_word(FILE * f, const int max_len, char word[])
{
    int r, i = 0;
    
    while (i <= max_len)
    {
        r = fscanf(f, "%c", &word[i]);
        
        if (r != 1)
        {
            return UNABLE_TO_READ_THE_WORD;
        }
        else if (word[i] == ' ' )
        {
            if (i == 0)
            {
                continue;;
            }
            else
            {
                break;
            }
        }
        else if (!((word[i] >= 'A' && word[i] <= 'Z') ||
                   (word[i] >= 'a' && word[i] <= 'z') ||
                   ((word[i] == '-' || word[i] == '_') && i != 0)))
        {
            printf("Встречен недопустимый символ '%c' ", word[i]);
            return ERROR_IN_WORD;
        }
        i++;
    }
    
    if (i == max_len + 1 && word[i] != ' ')
    {
        return WORD_TOO_LONG;
    }
    
    word[i] = '\0';
    
    return SUCCESS;
}

int read_the_price_range(FILE *f, int * const min_price, int * const max_price)
{
    int r;
    
    r = fscanf(f, "%d", min_price);
    
    if (r != 1)
    {
        printf("Не удалось считать минимальную цену билета\n");
        return UNABLE_TO_COUNT_THE_MINIMUM_TICKET_PRICE;
    }
    
    r = fscanf(f, "%d", max_price);
    
    if (r != 1)
    {
        printf("Не удалось считать максимальную цену билета\n");
        return UNABLE_TO_COUNT_THE_MAXIMUM_TICKET_PRICE;
    }
    
    if (*min_price <= 0 || *max_price <= 0)
    {
        printf("Цена билета должна быть больше 0\n");
        return ICKET_PRICE_MUST_BE_GREATER_THAN_ZERO;
    }
    else if (*min_price > *max_price)
    {
        printf("Минимальная цена билета не может превосходить максимальную\n");
        return MINIMUM_TICKET_PRICE_SHOULD_NOT_EXCEED_THE_MAXIMUM;
    }
    
    return SUCCESS;
}

int fill_in_the_information_about_the_child_performance(FILE * f, child_t * child)
{
    int r;
    
    r = fscanf(f, "%d", &(*child).min_age);
    
    if (r != 1)
    {
        printf("Не удалось считать минимальный возраст\n");
        return FAILED_TO_COUNT_THE_MINIMUM_AGE;
    }
    
    if ((*child).min_age < 0)
    {
        printf("Возраст не может быть отрицательным\n");
        return AGE_CANNOT_BE_NEGATIVE;
    }
    else if ((*child).min_age > MAXIMUM_AGE_OF_CHILD)
    {
        printf("Возраст ребёнка не должен превышать 17 лет\n");
        return CHILDS_AGE_TOO_GREAT;
    }
    
    r = fscanf(f, "%6s", (*child).type);
    
    if (strcmp((*child).type, "story") && strcmp((*child).type, "play"))
    {
        printf("Введён неверный тип спектакля для детей\n");
        return WRONG_TYPE_OF_PERFORMANCE_FOR_CHILDREN;
    }
    
    char ch;
    
    r = fscanf(f, "%c", &ch);
    
    if (r == 1 && ch !='\n')
    {
        printf("В строке содержится избыточная информация\n");
        return EXCESSIVE_INFORMATION;
    }
    
    return SUCCESS;
}

int fill_in_the_information_about_the_adult_performance(FILE * f, adult_t * adult)
{
    int r;
    
    r = fscanf(f, "%7s", (*adult).type);
    
    if (strcmp((*adult).type, "play") &&
        strcmp((*adult).type, "drama") && strcmp((*adult).type, "comedy"))
    {
        printf("Введён неверный тип спектакля для взрослых\n");
        return WRONG_TYPE_OF_PERFORMANCE_FOR_ADULT;
    }
    
    char ch;
    
    r = fscanf(f, "%c", &ch);
    
    if (r == 1 && ch !='\n')
    {
        printf("В строке содержится избыточная информация\n");
        return EXCESSIVE_INFORMATION;
    }
    
    return SUCCESS;
}

int fill_in_the_information_about_the_musical_performance(FILE * f, musical_t * musical)
{
    int r;
    
    r = read_a_word(f, MAXIMUM_COMPOSER_NAME_LENGTH, (*musical).composer);

    if (r)
    {
        if (r == UNABLE_TO_READ_THE_WORD)
        {
            printf("Ошибка в имени композитора\n");
            return ERROR_IN_THE_NAME_OF_THE_COMPOSER;
        }
        else if (r == ERROR_IN_WORD)
        {
            printf("(Ошибка в имени композитора)\n");
            return ERROR_IN_THE_NAME_OF_THE_COMPOSER;
        }
        else if (r == WORD_TOO_LONG)
        {
            printf("Превышена максимальная длина имени композитора\n");
            return TOO_LONG_COMPOSER_NAME;
        }
    }
    
    r = read_a_word(f, MAXIMUM_COUNTRY_NAME_LENGTH, (*musical).country);

    if (r)
    {
        if (r == UNABLE_TO_READ_THE_WORD)
        {
            printf("Ошибка в названии страны\n");
            return ERROR_IN_THE_NAME_OF_THE_COUNTRY;
        }
        else if (r == ERROR_IN_WORD)
        {
            printf("(Ошибка в названии страны)\n");
            return ERROR_IN_THE_NAME_OF_THE_COUNTRY;
        }
        else if (r == WORD_TOO_LONG)
        {
            printf("Превышена максимальная длина названия страны\n");
            return TOO_LONG_COUNTRY_NAME;
        }
    }
    
    r = fscanf(f, "%d", &(*musical).min_age);
    
    if (r != 1)
    {
        printf("Не удалось считать минимальный возраст\n");
        return FAILED_TO_COUNT_THE_MINIMUM_AGE;
    }
    
    if ((*musical).min_age <= 0)
    {
        printf("Возраст должен быть положительным числом\n");
        return AGE_CANNOT_BE_NEGATIVE;
    }
    
    if ((*musical).min_age > MAXIMUM_AGE_FOR_MUSIC)
    {
        printf("Минимальный возраст не может быть больше 23 лет "
               "(для посещения музыкального спектакля)\n");
        return AGE_TOO_GREAT; 
    }
    
    r = fscanf(f, "%d", &(*musical).duration);
    
    if (r != 1)
    {
        printf("Не удалось считать продолжительность спектакля\n");
        return UNABLE_TO_READ_THE_DURATION_OF_THE_PERFORMANCE;
    }
    
    if ((*musical).duration <= 0)
    {
        printf("Продолжительность спектакля должна быть больше 0\n");
        return DURATION_OF_THE_PERFORMANCE_CANNOT_BE_NEGATIVE;
    }
    
    char ch;
    
    r = fscanf(f, "%c", &ch);
    
    if (r == 1 && ch !='\n')
    {
        printf("В строке содержится избыточная информация\n");
        return EXCESSIVE_INFORMATION;
    }
    
    return SUCCESS;
}

int read_the_type_of_performance(FILE *f, char str_type_of_performance[], type_of_performance_t * type_of_performance)
{
    int r;
    
    r = fscanf(f, "%8s", str_type_of_performance);
    
    if (r != 1)
    {
        printf("Введён неверный тип спектакля\n");
        return WRONG_TYPE_OF_PERFORMANCE;
    }
    if (!strcmp(str_type_of_performance, "child"))
    {
        r = fill_in_the_information_about_the_child_performance(f, &(*type_of_performance).child);
    }
    else if (!strcmp(str_type_of_performance, "adult"))
    {
        r = fill_in_the_information_about_the_adult_performance(f, &(*type_of_performance).adult);
    }
    else if (!strcmp(str_type_of_performance, "musical"))
    {
        r = fill_in_the_information_about_the_musical_performance(f, &(*type_of_performance).musical);
    }
    else
    {
        printf("Введён неверный тип спектакля\n");
        return WRONG_TYPE_OF_PERFORMANCE;
    }
    
    if (r)
    {
        return r;
    }
        
    return SUCCESS;
}

int read_number_action(int *number_action)
{
    int r;
    
    printf("Введите номер команды: ");
    r = scanf("%d", number_action);
    printf("\n");
    
    if (r != 1 )
    {
        printf("Не удалось прочитать номер команды\n");
        return FAILED_TO_READ_COMMAND_NUMBER;
    }
    
    if ( *number_action < MIN_COMMAND_NUMBER || *number_action > MAX_COMMAND_NUMBER)
    {
        printf("Номер команды должен быть >= 0 и <= 9\n");
        return WRONG_COMMAND_NUMBER;
    }
    
    return SUCCESS;
}


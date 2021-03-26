#include <stdio.h>
#include <string.h>
#include "../inc/commands.h"

int fill_out_the_theater_repertoire(FILE * f, theaters_t * theather)
{
    int r;
    
    r = read_a_word(f, MAXIMUM_LENGTH_OF_THEATER_NAME, (*theather).theater_name); 
    
    if (r)
    {
        if (r == UNABLE_TO_READ_THE_WORD)
        {
            printf("Ошибка в названии театра\n");
            return MISTAKE_IN_THE_NAME_OF_THE_THEATER;
        }
        else if (r == ERROR_IN_WORD)
        {
            printf("(Ошибка в названии театра)\n");
            return MISTAKE_IN_THE_NAME_OF_THE_THEATER;
        }
        else if (r == WORD_TOO_LONG)
        {
            printf("Превышена максимальная длина названия театра\n");
            return TOO_LONG_THEATER_NAME;
        }
        
        return r;
    }
    
    r = read_a_word(f, MAXIMUM_LENGTH_OF_PERFORMANCE_NAME, (*theather).performance);

    if (r)
    {
        if (r == UNABLE_TO_READ_THE_WORD)
        {
            printf("Ошибка в названии спектакля\n");
            return MISTAKE_IN_THE_NAME_OF_THE_PERFORMANCE;
        }
        else if (r == ERROR_IN_WORD)
        {
            printf("(Ошибка в названии спектакля)\n");
            return MISTAKE_IN_THE_NAME_OF_THE_PERFORMANCE;
        }
        else if (r == WORD_TOO_LONG)
        {
            printf("Превышена максимальная длина названия спектакля\n");
            return TOO_LONG_PERFOMANCE_NAME;
        }
        
        return r;
    }
    
    r = read_a_word(f, MAXIMUM_LENGTH_OF_PRODUCER_NAME, (*theather).producer);

    if (r)
    {
        if (r == UNABLE_TO_READ_THE_WORD)
        {
            printf("Ошибка в имени режиссёра\n");
            return ERROR_IN_THE_NAME_OF_THE_PRODUCER;
        }
        else if (r == ERROR_IN_WORD)
        {
            printf("(Ошибка в имени режиссёра)\n");
            return ERROR_IN_THE_NAME_OF_THE_PRODUCER;
        }
        else if (r == WORD_TOO_LONG)
        {
            printf("Превышена максимальная длина имени режиссёра\n");
            return TOO_LONG_PRODUCER_NAME;
        }
    }
    
    r = read_the_price_range(f, &(*theather).min_price, &(*theather).max_price);
    
    if (r)
    {
        return r;
    }
    
    r = read_the_type_of_performance(f, (*theather).str_type_of_performance, &(*theather).type_of_performance);
    
    if (r)
    {
        return r;
    }
    
    return SUCCESS;
}

void create_an_array_of_keys(table_t * table)
{
    for (int i = 0; i < (*table).size; i++)
    {
        (*table).keys[i].index = i;
        strcpy((*table).keys[i].array, (*table).theaters[i].performance);
    }
}

int fill_in_the_table(const char *name_file, const int max_size, table_t * table)
{
    FILE * f;
    int r;
    
    f = fopen(name_file, "r");
    
    if (f == NULL)
    {
        printf("Не удалось открыть файл\n");
        return ERROR_WHEN_OPENING_FILE;
    }
    
    r = read_the_number_of_records(f, &((*table).size), MAXIMUM_TABLE_SIZE);
    
    if (r)
    {
        return r;
    }
    
    for (int i = 0; i < (*table).size; i++)
    {
        r = fill_out_the_theater_repertoire(f, &((*table).theaters[i]));
        
        if (r)
        {
            printf("Ошибка в '%d' строке\n", i + 2);
            return r;
        }
    }
    
    fclose(f);
    
    create_an_array_of_keys(table);
    
    return SUCCESS;
}

int add_a_performance(table_t * table)
{
    int r;
    
    if (++((*table).size) > MAXIMUM_TABLE_SIZE)
    {
        printf("Нельзя добавить новый спектакль, так как таблица уже содержит максимальное кол-во строк\n");
        return TABLE_IS_FULL;
    }
    
    char ch;
    scanf("%c", &ch);
    
    printf("Введите репертуар театра по следующим правилам: \n\n"
           "1. Максимальная длина названия театра - 23 символа;\n"
           "2. Максимальная длина названия спектакля - 20 символов;\n"
           "3. Максимальная длина фамилии режиссёра - 20 символов;\n"
           "4. Минимальная цена билета > 0;\n"
           "5. Максимальная цена билета > 0 и > Минимальной цены;\n"
           "6. Возможно только три типа спектакля: child, adult, musical;\n"
           "7. Минимальный возраст ребёнка - целое число в промежутке от 0 до 17 лет;\n"
           "8. Возможно только два типа спектакля для детей: story, play;\n"
           "9. Возможно только три типа спектакля для взрослых: play, drama, comedy;\n"
           "10. Максимальная длина фамилии композитора - 20 символов;\n"
           "11. Максимальная длина названия страны - 15 символа;\n"
           "12. Минимальный возраст для посещения музыкального спектакля - целое число в промежутке от 0 до 23 лет;\n"
           "13. Продолжительность музыкального спектакля должна быть больше нуля;\n"
           "14. Допустимые символы в словах:\n"
           "    - латинские буквы от 'a' до 'z';\n"
           "    - латинские буквы от 'A' до 'Z';\n"
           "    - символы '-', '_' не в начале слова ('_' вместо символа ' ');\n"
           "15. Слова в строке должны быть разделены пробелами;\n\n"
           "Шаблон:\n"
           "1) Название театра;\n"
           "2) Название спектакля;\n"
           "3) Фамилия режиссёра;\n"
           "4) Минимальная цена билета;\n"
           "5) Максимальная цена билета;\n"
           "6) Тип спектакля:\n"
           "    6.1. (child)\n"
           "        - минимальный возраст\n"
           "        - тип детского спектакля (story, play)\n"
           "    6.2. (adult)\n"
           "        - тип спектакля для взрослых(play, drama, comedy)\n"
           "    6.3. (musical)\n"
           "        - фамилия композитора\n"
           "        - название страны\n"
           "        - минимальный возраст\n"
           "        - продолжительность\n\n");

    r = fill_out_the_theater_repertoire(stdin, &((*table).theaters[(*table).size - 1]));
    
    if (r)
    {
        return r;
    }
    
    return SUCCESS;
}

int delete_specific_lines(table_t * table)
{
    int r, min_price;
    
    printf("Введите верхнюю границу минимальной цены билета: ");
    r = scanf("%d", &min_price);
    
    if (r != 1)
    {
        printf("\nНе удалось считать верхнюю границу минимальной цены билета\n");
        return UNABLE_TO_COUNT_THE_MINIMUM_TICKET_PRICE;
    }
    
    if (min_price <= 0)
    {
        printf("\nВерхняя граница минимальной цены билета должна быть больше 0\n");
        return ICKET_PRICE_MUST_BE_GREATER_THAN_ZERO;
    }
    
    int quantity = 0, i = 0;
    theaters_t c;
    
    while (i < (*table).size - quantity)
    {
        if ((*table).theaters[i].min_price > min_price)
        {
            for (int j = i; j < (*table).size - 1 - quantity; j++)
            {
                c = (*table).theaters[j];
                (*table).theaters[j] = (*table).theaters[j + 1];
                (*table).theaters[j + 1] = c;
            }
            
            quantity++;
            continue;
        }
        
        i++;
    }
    
    (*table).size -= quantity;;
    printf("\nКол-во удалённых спектаклей - %d\n", quantity);
    
    return SUCCESS;
}

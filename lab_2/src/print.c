#include <stdio.h>
#include "../inc/print.h"

void print_line(const int i, theaters_t * theaters)
{
    printf("\n");
    printf("| %-23s| %-20s| %-20s| %-9d | %-9d | %-7s | ", theaters[i].theater_name,
           theaters[i].performance, theaters[i].producer,
           theaters[i].min_price, theaters[i].max_price,
           theaters[i].str_type_of_performance);
    
    if (theaters[i].str_type_of_performance[0] == 'c')
    {
        printf("%-3d | %-5s | %6c | %20c| %15c| %3c | %6c |\n",
               theaters[i].type_of_performance.child.min_age,
               theaters[i].type_of_performance.child.type,
               ' ', ' ', ' ', ' ', ' ');
    }
    else if (theaters[i].str_type_of_performance[0] == 'a')
    {
        printf("%3c | %5c | %-6s | %20c| %15c| %3c | %6c |\n",
               ' ', ' ', theaters[i].type_of_performance.adult.type,
               ' ', ' ', ' ', ' ');
    }
    else
    {
        printf("%3c | %5c | %6c | %-20s| %-15s| %-3d | %-6d |\n", ' ', ' ', ' ',
               theaters[i].type_of_performance.musical.composer,
               theaters[i].type_of_performance.musical.country,
               theaters[i].type_of_performance.musical.min_age,
               theaters[i].type_of_performance.musical.duration);
    }
    
    printf("| %-23c| %-20c| %-20c| %-9c | %-9c | %-7c |%5c|%6c | %-6c | %-20c| %-15c|%-5c|%-8c|\n",
           ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    
    for (int j = 181; j > 0; j--)
    {
        printf("%c", '-');
    }
}

void print_table(table_t * table) 
{
    if ((*table).size == 0)
    {
        printf("Таблица пуста\n");
        return;
    }
    
    char str1[] = "THEATER", str2[] = "PERFOMANCE", str3[] = "PRODUCER", str4[] = "MIN_PRICE",
         str5[] = "MAX_PRICE", str6[] = "TYPE", str7[] = "AGE_C",
         str8[] = "TYPE_C", str9[] = "TYPE_A", str10[] = "COMPOSER",
         str11[] = "COUNTRY", str12[] = "AGE_M", str13[] = "DURATION";
    
    for (int j = 181; j > 0; j--)
    {
        printf("%c", '-');
    }
    
    printf("\n| %-23c| %-20c| %-20c| %-9c | %-9c | %-7c |%5c|%6c | %-6c | %-20c| %-15c|%-5c|%-8c|\n"
             "| %-23s| %-20s| %-20s| %-9s | %-9s | %-7s |%5s|%6s | %-6s | %-20s| %-15s|%-5s|%-8s|\n"
             "| %-23c| %-20c| %-20c| %-9c | %-9c | %-7c |%5c|%6c | %-6c | %-20c| %-15c|%-5c|%-8c|\n",
           ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
           str1, str2, str3, str4, str5, str6, str7, str8, str9, str10, str11, str12, str13,
           ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    
    for (int j = 181; j > 0; j--)
    {
        printf("%c", '-');
    }
    
    for (int i = 0; i < (*table).size; i++)
    {
        print_line(i, (*table).theaters);
    }
    
    printf("\n");
}

void print_menu(void)
{
    printf("\nКоманды: \n"
           "1. Загрузить список спектаклей из файла;\n"
           "2. Вывести таблицу;\n"
           "3. Добавить спектакль в конец таблицы;\n"
           "4. Удалить спектакли, минимальная цена билетов которых больше указанного значения;\n"
           "5. Вывести список всех музыкальных спектаклей для детей указанного возраста с продолжительностью меньше указанной;\n"
           "6. Вывести массив ключей (Ключ - название спектакля);\n"
           "7. Отсортировать массив ключей методом 'qsort' (Ключ - название спектакля);\n"
           "8. Отсортировать массив ключей методом 'выбором' (Ключ - название спектакля);\n"
           "9. Отсортировать таблицу методом 'qsort' (по названию спектакля);\n"
           "10. Отсортировать таблицу методом 'выбором' (по названию спектакля);\n"
           "11. Вывести отсортированную (по названию спектакля) таблицу, используя упорядоченный массив ключей;\n"
           "12. Вывести результаты сравнения эффективности программы (при обработке таблицы и массива ключей);\n"
           "0. Выйти из программы.\n\n");
}

int print_of_the_required_performances(table_t * table)
{
    int r, min_age;
    
    printf("Введите минимально допустимый возраст для посещения музыкального спектакля (от 0 до 23 лет): ");
    r = scanf("%d", &min_age);
    
    if (r != 1)
    {
        printf("\nНе удалось считать минимальный возраст\n");
        return FAILED_TO_COUNT_THE_MINIMUM_AGE;
    }
    
    if (min_age < 0)
    {
        printf("\nВозраст не может быть отрицательным\n");
        return AGE_CANNOT_BE_NEGATIVE;
    }
    
    if (min_age > MAXIMUM_AGE_FOR_MUSIC)
    {
        printf("\nМинимальный возраст не может быть больше 23\n");
        return AGE_TOO_GREAT;
    }
    
    int duration;
    
    printf("Введите максимальную продолжительность спектакля: ");
    r = scanf("%d", &duration);
    
    if (r != 1)
    {
        printf("\nНе удалось считать продолжительность спектакля\n");
        return UNABLE_TO_READ_THE_DURATION_OF_THE_PERFORMANCE;
    }
    
    if (duration < 0)
    {
        printf("\nПродолжительность спектакля не может быть отрицательной\n");
        return DURATION_OF_THE_PERFORMANCE_CANNOT_BE_NEGATIVE;
    }
    
    int quantity = 0;
    
    for (int i = 0; i < (*table).size; i++)
    {
        if ((*table).theaters[i].str_type_of_performance[0] == 'm' &&
            (*table).theaters[i].type_of_performance.musical.min_age >= min_age &&
            (*table).theaters[i].type_of_performance.musical.duration <= duration)
        {
            quantity++;
        }
    }
    
    if (!quantity)
    {
        printf("\nПодходящих спектаклей не найдено\n");
        return SUCCESS;
    }
    
    char str1[] = "THEATER", str2[] = "PERFOMANCE", str3[] = "PRODUCER", str4[] = "MIN_PRICE",
         str5[] = "MAX_PRICE", str6[] = "TYPE", str7[] = "AGE_C",
         str8[] = "TYPE_C", str9[] = "TYPE_A", str10[] = "COMPOSER",
         str11[] = "COUNTRY", str12[] = "AGE_M", str13[] = "DURATION";
    
    for (int j = 181; j > 0; j--)
    {
        printf("%c", '-');
    }
    
    printf("\n| %-23c| %-20c| %-20c| %-9c | %-9c | %-7c |%5c|%6c | %-6c | %-20c| %-15c|%-5c|%-8c|\n"
             "| %-23s| %-20s| %-20s| %-9s | %-9s | %-7s |%5s|%6s | %-6s | %-20s| %-15s|%-5s|%-8s|\n"
             "| %-23c| %-20c| %-20c| %-9c | %-9c | %-7c |%5c|%6c | %-6c | %-20c| %-15c|%-5c|%-8c|\n",
           ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
           str1, str2, str3, str4, str5, str6, str7, str8, str9, str10, str11, str12, str13,
           ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    
    for (int j = 181; j > 0; j--)
    {
        printf("%c", '-');
    }
    
    for (int i = 0; i < (*table).size; i++)
    {
        if ((*table).theaters[i].str_type_of_performance[0] == 'm' &&
            (*table).theaters[i].type_of_performance.musical.min_age >= min_age &&
            (*table).theaters[i].type_of_performance.musical.duration <= duration)
        {
            print_line(i, (*table).theaters);
        }
    }
    
    printf("\nКол-во подходящих спектаклей - %d\n", quantity);
    
    return SUCCESS;
}

void print_an_array_of_keys(table_t * table)
{
    
    if ((*table).size == 0)
    {
        printf("Таблица пуста\n");
        return;
    }
    
    char str1[] = "INDEX", str2[] = "PERFOMANCE";
    
    printf("%-5c", ' ');
    
    for (int j = 32; j > 0; j--)
    {
        printf("%c", '-');
    }
    
    printf("\n%-5c| %-5c | %-20c |\n"
             "%-5c| %-5s | %-20s |\n"
             "%-5c| %-5c | %-20c | \n",
           ' ', ' ', ' ', ' ', str1, str2, ' ', ' ', ' ');
    
    printf("%-5c", ' ');
    
    for (int j = 32; j > 0; j--)
    {
        printf("%c", '-');
    }
    
    for (int i = 0; i < (*table).size; i++)
    {
        printf("\n%-5c| %-5d | %-20s |\n", ' ', (*table).keys[i].index, (*table).keys[i].array);
        printf("%-5c| %-5c | %-20c |\n", ' ', ' ', ' ');
        
        printf("%-5c", ' ');
        
        for (int j = 32; j > 0; j--)
        {
            printf("%c", '-');
        }
    }
}
 

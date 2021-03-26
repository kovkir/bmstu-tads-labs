#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../inc/sort.h"

int compare_k(const keys_t * arg_1, const keys_t * arg_2)
{
    return (strcmp((*arg_1).array, (*arg_2).array));
}

void sorting_an_array_of_keys_qsort(table_t * table) 
{
    if ((*table).size == 0)
    {
        printf("Таблица пуста\n");
        return;
    }
    
    qsort((*table).keys, (*table).size, sizeof(keys_t), (int(*) (const void *, const void *))  compare_k);
//    printf("Массив ключей успешно отсортирован\n");
}
 
void sorting_an_array_of_keys_choice(table_t * table)
{
    if ((*table).size == 0)
    {
        printf("Таблица пуста\n");
        return;
    }
    
    int min;
    keys_t c;

    for (int i = 0; i < (*table).size - 1; i++)
    {
        min = i;
        
        for (int j = i + 1; j < (*table).size; j++)
        {
            if (strcmp((*table).keys[j].array, (*table).keys[min].array) < 0)
            {
                min = j;
            }
        }

        c = (*table).keys[i];
        (*table).keys[i] = (*table).keys[min];
        (*table).keys[min] = c;
    }
    
//    printf("Массив ключей успешно отсортирован\n");
}

int compare_t(const theaters_t * arg_1, const theaters_t * arg_2) 
{
    return (strcmp((*arg_1).performance, (*arg_2).performance));
}

void sort_the_table_qsort(table_t * table)
{
    if ((*table).size == 0)
    {
        printf("Таблица пуста\n");
        return;
    }
    
    qsort((*table).theaters, (*table).size, sizeof(theaters_t), (int(*) (const void *, const void *)) compare_t);
//    printf("Таблица успешно отсортирована\n");
}

void sort_the_table_choice(table_t * table)
{
    if ((*table).size == 0)
    {
        printf("Таблица пуста\n");
        return;
    }
    
    int min;
    theaters_t c;

    for (int i = 0; i < (*table).size - 1; i++)
    {
        min = i;
        
        for (int j = i + 1; j < (*table).size; j++)
        {
            if (strcmp((*table).theaters[j].performance, (*table).theaters[min].performance) < 0)
            {
                min = j;
            }
        }

        c = (*table).theaters[i];
        (*table).theaters[i] = (*table).theaters[min];
        (*table).theaters[min] = c;
    }
    
//    printf("Таблица успешно отсортирована\n");
}

void sort_the_array_using_keys(table_t * table)
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
        print_line((*table).keys[i].index, (*table).theaters);
    }
    
    printf("\n");
}

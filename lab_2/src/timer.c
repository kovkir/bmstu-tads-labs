#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "../inc/timer.h"

uint64_t tick(void)
{
    uint32_t high, low;
    __asm__ __volatile__ (
        "rdtsc\n"
        "movl %%edx, %0\n"
        "movl %%eax, %1\n"
        : "=r" (high), "=r" (low)
        :: "%rax", "%rbx", "%rcx", "%rdx"
        );

    uint64_t ticks = ((uint64_t)high << 32) | low;

    return ticks;
}

void print_result(int64_t start, int64_t end)
{
    printf("\n      %lld тактов, %.10lf секунд\n\n", end - start, (double)(end - start)/HZ);  
}

int compare_sorts(const char name_file[], table_t * table)
{
    int64_t start = 0, end = 0;
    int r;
    
    r = fill_in_the_table(name_file, MAXIMUM_TABLE_SIZE, table);
    
    if (r)
    {
        return r;
    }
    
    printf("                    Сравнение методов сортировки на массиве из %d элементов\n\n", (*table).size);
    printf("Сортировка таблицы методом 'qsort'\n");
    
    for (int i = 0; i < NUMBER_OF_RUNS; i++)
    {
        start += tick();
        sort_the_table_qsort(table);
        end += tick();
        
        r = fill_in_the_table(name_file, MAXIMUM_TABLE_SIZE, table);
        
        if (r)
        {
            return r;
        }
    }
    
    print_result(start / NUMBER_OF_RUNS, end / NUMBER_OF_RUNS);
    
    printf("Сортировка таблицы методом 'выбором'\n");
    
    start = 0;
    end = 0;
    
    for (int i = 0; i < NUMBER_OF_RUNS; i++)
    {
        start += tick();
        sort_the_table_choice(table);
        end += tick();
        
        r = fill_in_the_table(name_file, MAXIMUM_TABLE_SIZE, table);
        
        if (r)
        {
            return r;
        }
    }
    
    print_result(start / NUMBER_OF_RUNS, end / NUMBER_OF_RUNS);
    
    printf("Сортировка массива ключей методом 'qsort'\n");
    
    start = 0;
    end = 0;
    
    for (int i = 0; i < NUMBER_OF_RUNS; i++)
    {
        start += tick();
        sorting_an_array_of_keys_qsort(table);
        end += tick();
        
        r = fill_in_the_table(name_file, MAXIMUM_TABLE_SIZE, table);
        
        if (r)
        {
            return r;
        }
    }
    
    print_result(start / NUMBER_OF_RUNS, end / NUMBER_OF_RUNS);
    
    printf("Сортировка массива ключей методом 'выбором'\n");
    
    start = 0;
    end = 0;
    
    for (int i = 0; i < NUMBER_OF_RUNS; i++)
    {
        start += tick();
        sorting_an_array_of_keys_choice(table);
        end += tick();
        
        r = fill_in_the_table(name_file, MAXIMUM_TABLE_SIZE, table);
        
        if (r)
        {
            return r;
        }
    }
    
    print_result(start / NUMBER_OF_RUNS, end / NUMBER_OF_RUNS);
    
    printf("\nПамять для хранения таблицы - %lu\n", (*table).size * sizeof(*(*table).theaters));
    printf("\nПамять для хранения массива ключей - %lu\n", (*table).size * sizeof(*(*table).keys));
    
    return SUCCESS;
}

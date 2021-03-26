#include <stdio.h>
#include <stdlib.h>
#include "../inc/constants_and_errors.h"
#include "../inc/structures.h"
#include "../inc/read.h"
#include "../inc/print.h"
#include "../inc/commands.h"
#include "../inc/sort.h"
#include "../inc/timer.h"

int main(void)
{
    printf("\nПрограмма для обработки спектаклей, хранящихся в таблице.\n");
    
    int r, number_action;
    char name_file[] = "data.txt";
    table_t table;
    
    table.size = 0;
    
    while (1)
    {
        print_menu();
        r = read_number_action(&number_action);
//        system("clear");
        
        if (r)
        {
            return r;
        }
        
        if (number_action == 1)
        {
            r = fill_in_the_table(name_file, MAXIMUM_TABLE_SIZE, &table);
        }
        else if (number_action == 2)
        {
            print_table(&table);
        }
        else if (number_action == 3)
        {
            r = add_a_performance(&table);
        }
        else if (number_action == 4)
        {
            r = delete_specific_lines(&table);
        }
        else if (number_action == 5)
        {
            r = print_of_the_required_performances(&table); 
        }
        else if (number_action == 6)
        {
            print_an_array_of_keys(&table);
        }
        else if (number_action == 7)
        {
            sorting_an_array_of_keys_qsort(&table); 
        }
        else if (number_action == 8)
        {
            sorting_an_array_of_keys_choice(&table);
        }
        else if (number_action == 9)
        {
            sort_the_table_qsort(&table);
        }
        else if (number_action == 10)
        {
            sort_the_table_choice(&table); 
        }
        else if (number_action == 11)
        {
            sort_the_array_using_keys(&table);
        }
        else if (number_action == 12)
        {
            r = compare_sorts(name_file, &table);  
        }
        else if (number_action == 0)
        {
            break;
        }
        
        if (r)
        {
            return r;
        }
    }
    
    return SUCCESS;
}

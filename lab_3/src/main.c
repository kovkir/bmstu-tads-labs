#include "../inc/main.h"

int main(void)
{   
    int number_action, r;

    system("clear");

    while(TRUE)
    {
        print_menu();
        r = read_number_action(&number_action);
        
        if (r)
        {
            return r;
        }
        
        system("clear");

        if (number_action == 1)
        {
            r = special_multiplication();
        }
        else if (number_action == 2)
        {
            r = ordinary_multiplication();
        }
        else if (number_action == 3)
        {
            r = comparison_time_memory();
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

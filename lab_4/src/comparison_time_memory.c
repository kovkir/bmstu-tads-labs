#include"../inc/comparison_time_memory.h"

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
    printf("%lld тактов, %.10lf секунд\n", end - start, (double)(end - start)/HZ);  
}

int compare_stacks(void)
{
    int number_action, r;
    int array[MAXIMUM_STACK_SIZE];
    stack_array_t stack_array;

    stack_array.size = 0;
    stack_array.ptr = array - 1;

    elem_stack_list_t *elem_stack_list = NULL;
    
    int64_t start = 0, end = 0;

    printf("\nПервый стек - массив;\n"
           "Второй стек - список.\n");

    while(TRUE)
    {
        print_menu_time();

        r = read_number_action_time(&number_action);
        
        if (r)
        {
            free_stack_list(&elem_stack_list);
            return r;
        }
        
        // system("clear");

        if (number_action == 2)
        {
            int numb_add_elem;

            r = read_number_of_add_elem_to_stack_array(&numb_add_elem, stack_array.size);

            if (r)
            {
                free_stack_list(&elem_stack_list);
                return r;
            }

            if (stack_array.size != MAXIMUM_STACK_SIZE)
            {
                for (int i = 0; i < NUMBER_OF_RUNS; i++)
                {
                    start += tick();
                    fill_stack_array_randomly(&stack_array, numb_add_elem);
                    end += tick();

                    remove_elem_from_stack_array(&stack_array, numb_add_elem);
                }
                
                fill_stack_array_randomly(&stack_array, numb_add_elem);

                print_result(start / NUMBER_OF_RUNS, end / NUMBER_OF_RUNS);
                printf("Затраченная память под стек (массив) - %lu байт\n\n", 
                    MAXIMUM_STACK_SIZE * sizeof(int) + sizeof(stack_array_t));

                start = 0;
                end = 0;

                for (int i = 0; i < NUMBER_OF_RUNS; i++)
                {
                    start += tick();
                    fill_stack_list_randomly(&elem_stack_list, numb_add_elem);
                    end += tick();

                    remove_elem_from_stack_list(&elem_stack_list, numb_add_elem);
                }

                fill_stack_list_randomly(&elem_stack_list, numb_add_elem);

                print_result(start / NUMBER_OF_RUNS, end / NUMBER_OF_RUNS);
                printf("Затраченная память под стек (список) - %lu байт\n\n", 
                    elem_stack_list->numb_elem * sizeof(elem_stack_list_t));

                start = 0;
                end = 0;
            }
        }
        else if (number_action == 3)
        {
            int numb_remove_elem;

            r = read_number_of_remove_elem_from_stack_array(&numb_remove_elem, stack_array.size);

            if (r)
            {
                free_stack_list(&elem_stack_list);
                return r;
            }

            printf("\n");

            if (stack_array.size != 0)
            {
                for (int i = 0; i < NUMBER_OF_RUNS; i++)
                {
                    start += tick();
                    remove_elem_from_stack_array(&stack_array, numb_remove_elem);
                    end += tick();

                    fill_stack_array_randomly(&stack_array, numb_remove_elem);
                }
                
                remove_elem_from_stack_array(&stack_array, numb_remove_elem);

                print_result(start / NUMBER_OF_RUNS, end / NUMBER_OF_RUNS);

                start = 0;
                end = 0;

                printf("\n");
                
                for (int i = 0; i < NUMBER_OF_RUNS; i++)
                {
                    start += tick();
                    remove_elem_from_stack_list(&elem_stack_list, numb_remove_elem);
                    end += tick();

                    fill_stack_list_randomly(&elem_stack_list, numb_remove_elem);
                }

                remove_elem_from_stack_list(&elem_stack_list, numb_remove_elem);

                print_result(start / NUMBER_OF_RUNS, end / NUMBER_OF_RUNS);

                start = 0;
                end = 0;
            }
        }
        else if (number_action == 4)
        {
            print_stack_array(&stack_array);
            printf("\n");
            print_stack_list(&elem_stack_list);
        }
        else if (number_action == 5)
        {
            FILE *f = fopen("test_print.txt", "w");

            if (!f)
            {
                printf("Не удалось открыть файл\n");
                free_stack_list(&elem_stack_list);
                return FILE_OPEN_ERROR;
            }

            for (int i = 0; i < NUMBER_OF_RUNS; i++)
            {
                start += tick();
                print_descend_sequen_stack_array(stack_array, f);
                end += tick();
            }
        
            print_result(start / NUMBER_OF_RUNS, end / NUMBER_OF_RUNS);

            start = 0;
            end = 0;

            printf("\n");

            for (int i = 0; i < NUMBER_OF_RUNS; i++)
            {
                start += tick();
                print_descend_sequen_stack_list(elem_stack_list, f);
                end += tick();
            }

            print_result(start / NUMBER_OF_RUNS, end / NUMBER_OF_RUNS);

            start = 0;
            end = 0;

            // print_descend_sequen_stack_array(stack_array, stdout);
            // printf("\n");
            // print_descend_sequen_stack_list(elem_stack_list, stdout);
        }
        else if (number_action == 0)
        {
            free_stack_list(&elem_stack_list);
            break;
        }
       
        if (r)
        {
            free_stack_list(&elem_stack_list);
            return r;
        }
    }

    return SUCCESS;
}

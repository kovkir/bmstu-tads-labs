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
    printf("%lld тактов, %.10lf секунд\n", end - start, (double)(end - start) / HZ);  
}

int compare_turns(void)
{
    int number_action, r;
    int array[MAXIMUM_TURN_SIZE];

    turn_array_t turn_array;

    turn_array.size = 0;
    turn_array.head = array + MAXIMUM_TURN_SIZE - 1;
    turn_array.tail = turn_array.head;

    turn_list_t list;

    list.size = 0;
    list.head = NULL;

    array_of_freed_areas_t freed_array;

    freed_array.array = NULL;
    freed_array.size = 0;

    int64_t start = 0, end = 0;

    printf("\nПервая очередь - массив;\n"
           "Вторая очередь - список.\n");

    while(TRUE)
    {
        print_menu();

        r = read_number_action(&number_action);
        
        if (r)
        {
            free(freed_array.array);
            free_turn_list(&list);
            return r;
        }
        
        // system("clear");
        if (number_action == 1)
        {
            int numb_add_elem;

            r = read_number_of_add_elem_to_turn_array(&numb_add_elem, turn_array.size);

            if (r)
            {
                free(freed_array.array);
                free_turn_list(&list);
                return r;
            }

            r = add_elem_to_turn_array(&turn_array, numb_add_elem);

            if (r)
            {
                free(freed_array.array);
                free_turn_list(&list);
                return r;
            }

            r = add_elem_to_turn_list(&list, numb_add_elem, &turn_array);

            if (r)
            {
                free(freed_array.array);
                free_turn_list(&list);
                return r;
            }
        }
        else if (number_action == 2)
        {
            int numb_add_elem;

            r = read_number_of_add_elem_to_turn_array(&numb_add_elem, turn_array.size);

            if (r)
            {
                free(freed_array.array);
                free_turn_list(&list);
                return r;
            }
            
            int test_array[MAXIMUM_TURN_SIZE];

            turn_array_t test_turn_array;

            test_turn_array.size = 0;
            test_turn_array.head = test_array + MAXIMUM_TURN_SIZE - 1;
            test_turn_array.tail = test_turn_array.head;

            for (int i = 0; i < NUMBER_OF_RUNS; i++)
            {
                start += tick();
                fill_turn_array_randomly(&test_turn_array, numb_add_elem);
                end += tick();

                remove_elem_from_turn_array(&test_turn_array, numb_add_elem);
            }
                
            fill_turn_array_randomly(&turn_array, numb_add_elem);

            print_result(start / NUMBER_OF_RUNS, end / NUMBER_OF_RUNS);
            printf("Затраченная память под очередь (массив) - %lu байт\n\n", 
                MAXIMUM_TURN_SIZE * sizeof(int) + sizeof(turn_array_t));

            start = 0;
            end = 0;

            turn_list_t test_list;

            test_list.size = 0;
            test_list.head = NULL;

            for (int i = 0; i < NUMBER_OF_RUNS; i++)
            {
                start += tick();
                r = fill_turn_list_randomly(&test_list, numb_add_elem);
                end += tick();
                
                if (r)
                {
                    free(freed_array.array);
                    free_turn_list(&list);
                    return r;
                }

                remove_elem_from_turn_list(&test_list, numb_add_elem);
            }

            r = fill_turn_list_randomly(&list, numb_add_elem);

            if (r)
            {
                free(freed_array.array);
                free_turn_list(&list);
                return r;
            }

            print_result(start / NUMBER_OF_RUNS, end / NUMBER_OF_RUNS);
            printf("Затраченная память под очередь (список) - %lu байт\n\n", 
                list.head == NULL ? 0 : 
                list.size * sizeof(elem_turn_list_t) + sizeof(turn_list_t) - sizeof(int64_t));

            start = 0;
            end = 0;
        }
        else if (number_action == 3)
        {
            int numb_remove_elem;

            r = read_number_of_remove_elem_from_turn_array(&numb_remove_elem, turn_array.size);

            if (r)
            {
                free(freed_array.array);
                free_turn_list(&list);
                return r;
            }

            printf("\n");

            int test_array[MAXIMUM_TURN_SIZE];

            turn_array_t test_turn_array;

            test_turn_array.size = 0;
            test_turn_array.head = test_array + MAXIMUM_TURN_SIZE - 1;
            test_turn_array.tail = test_turn_array.head;

            for (int i = 0; i < NUMBER_OF_RUNS; i++)
            {
                fill_turn_array_randomly(&test_turn_array, numb_remove_elem);
                
                start += tick();
                remove_elem_from_turn_array(&test_turn_array, numb_remove_elem);
                end += tick();
            }

            r = add_addresses_of_removed_elem_to_array(&freed_array, numb_remove_elem, &list);

            if (r)
            {
                free_turn_list(&list);
                return r;
            }
                
            remove_elem_from_turn_array(&turn_array, numb_remove_elem);

            print_result(start / NUMBER_OF_RUNS, end / NUMBER_OF_RUNS);

            start = 0;
            end = 0;

            printf("\n");
            
            turn_list_t test_list;

            test_list.size = 0;
            test_list.head = NULL;

            for (int i = 0; i < NUMBER_OF_RUNS; i++)
            {
                r = fill_turn_list_randomly(&test_list, numb_remove_elem);

                if (r)
                {
                    free(freed_array.array);
                    free_turn_list(&list);
                    return r;
                }
                
                start += tick();
                remove_elem_from_turn_list(&test_list, numb_remove_elem);
                end += tick();
            }

            remove_elem_from_turn_list(&list, numb_remove_elem);

            print_result(start / NUMBER_OF_RUNS, end / NUMBER_OF_RUNS);

            start = 0;
            end = 0;
        }
        else if (number_action == 4)
        {
            print_turn_array(&turn_array);
        }
        else if (number_action == 5)
        {
            print_turn_list(&list);
        }
        else if (number_action == 6)
        {
            print_freed_array(&freed_array);
        }
        else if (number_action == 0)
        {
            free(freed_array.array);
            free_turn_list(&list);
            break;
        }
    }

    return SUCCESS;
}

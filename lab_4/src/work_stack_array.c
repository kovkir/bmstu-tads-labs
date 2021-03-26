#include "../inc/work_stack_array.h"

int work_with_stack_array(void)
{
    int number_action, r;
    int array[MAXIMUM_STACK_SIZE];
    stack_array_t stack_array;

    stack_array.size = 0;
    stack_array.ptr = array - 1;

    while(TRUE)
    {
        print_menu();

        r = read_number_action(&number_action);
        
        if (r)
            return r;
        
        // system("clear");

        if (number_action == 1)
        {   
            int numb_add_elem;

            r = read_number_of_add_elem_to_stack_array(&numb_add_elem, stack_array.size);

            if (r)
                return r;
            
            if (stack_array.size != MAXIMUM_STACK_SIZE)
                r = add_elem_to_stack_array(&stack_array, numb_add_elem);
        }
        else if (number_action == 2)
        {
            int numb_add_elem;

            r = read_number_of_add_elem_to_stack_array(&numb_add_elem, stack_array.size);

            if (r)
                return r;

            if (stack_array.size != MAXIMUM_STACK_SIZE)
                fill_stack_array_randomly(&stack_array, numb_add_elem);
        }
        else if (number_action == 3)
        {
            int numb_remove_elem;

            r = read_number_of_remove_elem_from_stack_array(&numb_remove_elem, stack_array.size);

            if (r)
                return r;

            if (stack_array.size != 0)
                remove_elem_from_stack_array(&stack_array, numb_remove_elem);
        }
        else if (number_action == 4)
        {
            print_stack_array(&stack_array);
        }
        else if (number_action == 5)
        {
            print_descend_sequen_stack_array(stack_array, stdout);
        }
        else if (number_action == 0)
        {
            break;
        }
       
        if (r)
            return r;
    }

    return SUCCESS;
}

int add_elem_to_stack_array(stack_array_t *stack_array, int numb_add_elem)
{
    int r;

    printf("Введите %d элемент(a, ов) стека.\n", numb_add_elem);

    for (int i = 0; i < numb_add_elem; i++)
    {
        stack_array->ptr++;

        r = read_new_elem(stack_array->ptr);

        if (r)
            return r;

        stack_array->size++;
    }

    return SUCCESS;
}

void remove_elem_from_stack_array(stack_array_t *stack_array, int numb_remove_elem)
{
    for (int i = 0; i < numb_remove_elem; i++)
    {
        stack_array->ptr--;
        stack_array->size--;
    }

    // printf("%d элемент(а, ов) успешно удалено из стека.\n", numb_remove_elem);
}

void fill_stack_array_randomly(stack_array_t *stack_array, int numb_add_elem)
{
    srand(time(NULL));

    for (int i = 0; i < numb_add_elem; i++)
    {
        stack_array->ptr++;
        stack_array->size++;

        *stack_array->ptr = MIN_BORDER + rand() % (MAX_BORDER - MIN_BORDER + 1);
    }
}
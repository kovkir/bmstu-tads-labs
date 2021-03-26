#include "../inc/read.h"

int read_stack_type(int *stack_type)
{
    printf("Введите число (1 или 2), чтобы выбрать тип стека:\n"
           "    1 - стек, реализованный с помощью массива;\n"
           "    2 - стек, реализонаееый с помощью списка;\n"
           "Введите 3 для сравнения времени и памяти двух типов стеков\n\n");
    
    int r = scanf("%d", stack_type);

    if (r != 1 )
    {
        printf("Не удалось прочитать тип стека\n");
        return FAILED_TO_READ_STACK_TYPE;
    }
    
    if (*stack_type < 1 || *stack_type > 3)
    {
        printf("Номер команды - числа 1, 2 или 3\n");
        return WRONG_STACK_TYPE;
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
        printf("Номер команды должен быть >= %d и <= %d\n",
        MIN_COMMAND_NUMBER, MAX_COMMAND_NUMBER);

        return WRONG_COMMAND_NUMBER;
    }
    
    return SUCCESS;
}

int read_number_of_add_elem_to_stack_array(int *numb_add_elem, int size)
{
    if (size == MAXIMUM_STACK_SIZE)
    {
        printf("Стек заполнен.\n");
        return SUCCESS;
    }

    printf("Введите кол-во добавляемых элементов (не более %d): ", MAXIMUM_STACK_SIZE - size);

    int r = scanf("%d", numb_add_elem);

    printf("\n");

    if (r != 1)
    {
        printf("Не удалось прочитать кол-во добавляемых элементов.\n");
        return FAILED_TO_READ_ADDED_ELEMENTS;
    }

    if (*numb_add_elem < 0)
    {
        printf("Кол-во добавляемых элементов не может быть отрицательным.\n");
        return NUMBER_OF_ADDED_ELEM_IS_NEGATIVE;
    }
    else if (size + *numb_add_elem > MAXIMUM_STACK_SIZE)
    {
        printf("Произошло переполнение стека.\n");
        return STACK_OVERFLOW;
    }

    return SUCCESS;
}

int read_new_elem(int *new_elem)
{
    int r = scanf("%d", new_elem);

    if (r != 1)
    {
        printf("Не удалось прочитать элемент стека\n");
        return FAILED_TO_READ_STACK_ELEMENT;
    }

    return SUCCESS;
}

int read_number_of_remove_elem_from_stack_array(int *numb_remove_elem, int size)
{
    if (size == 0)
    {
        printf("Стек пуст.\n");
        return SUCCESS;
    }

    printf("Введите кол-во удаляемых элементов (не более %d): ", size);

    int r = scanf("%d", numb_remove_elem);

    if (r != 1)
    {
        printf("Не удалось прочитать кол-во удаляемых элементов.\n");
        return FAILED_TO_READ_REMOVED_ELEMENTS;
    }

    if (*numb_remove_elem < 0)
    {
        printf("Кол-во удаляемых элементов не может быть отрицательным.\n");
        return NUMBER_OF_REMOVED_ELEM_IS_NEGATIVE;
    }
    else if (*numb_remove_elem > size)
    {
        printf("В стеке нет столько элементов.\n");
        return TOO_MANY_REMOVABLE_ELEMENTS;
    }

    return SUCCESS;
}

int read_number_of_add_elem_to_stack_list(int *numb_add_elem, elem_stack_list_t *elem_stack_list)
{
    if (elem_stack_list != NULL && elem_stack_list->numb_elem == MAXIMUM_STACK_SIZE)
    {
        printf("Стек заполнен.\n");
        return SUCCESS;
    }

    if (elem_stack_list != NULL)
        printf("Введите кол-во добавляемых элементов (не более %d): ", 
        MAXIMUM_STACK_SIZE - elem_stack_list->numb_elem);
    else
        printf("Введите кол-во добавляемых элементов (не более 10000): ");

    int r = scanf("%d", numb_add_elem);

    printf("\n");

    if (r != 1)
    {
        printf("Не удалось прочитать кол-во добавляемых элементов.\n");
        return FAILED_TO_READ_ADDED_ELEMENTS;
    }

    if (*numb_add_elem < 0)
    {
        printf("Кол-во добавляемых элементов не может быть отрицательным.\n");
        return NUMBER_OF_ADDED_ELEM_IS_NEGATIVE;
    }

    if (elem_stack_list == NULL)
    {
        if (*numb_add_elem > MAXIMUM_STACK_SIZE)
        {
            printf("Произошло переполнение стека.\n");
            return STACK_OVERFLOW;
        }
    }
    else if (elem_stack_list->numb_elem + *numb_add_elem > MAXIMUM_STACK_SIZE)
    {
        printf("Произошло переполнение стека.\n");
        return STACK_OVERFLOW;
    }

    return SUCCESS;
}

int read_number_of_remove_elem_from_stack_list(int *numb_remove_elem, 
elem_stack_list_t *elem_stack_list)
{
    if (elem_stack_list == NULL)
    {
        printf("Стек пуст.\n");
        return SUCCESS;
    }

    printf("Введите кол-во удаляемых элементов (не более %d): ", elem_stack_list->numb_elem);

    int r = scanf("%d", numb_remove_elem);

    if (r != 1)
    {
        printf("Не удалось прочитать кол-во удаляемых элементов.\n");
        return FAILED_TO_READ_REMOVED_ELEMENTS;
    }

    if (*numb_remove_elem < 0)
    {
        printf("Кол-во удаляемых элементов не может быть отрицательным.\n");
        return NUMBER_OF_REMOVED_ELEM_IS_NEGATIVE;
    }
    
    if (*numb_remove_elem > elem_stack_list->numb_elem)
    {
         printf("В стеке нет столько элементов.\n");
        return TOO_MANY_REMOVABLE_ELEMENTS;
    }

    return SUCCESS;
}

int read_action(int *action)
{
    printf("\nВведите 1, чтобы вывести массив адресов освобождённых элементов стека;\n"
           "Введите 0 в ином случае.\n\n");

    int r = scanf("%d", action);
    
    if (r != 1 )
    {
        printf("Не удалось прочитать номер команды\n");
        return FAILED_TO_READ_COMMAND_NUMBER;
    }
    
    if ( *action != 1 && *action != 0)
    {
        printf("Номер команды - число 0 или 1\n");
        return WRONG_COMMAND_NUMBER;
    }

    return SUCCESS;
}

int read_number_action_time(int *number_action)
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
        printf("Номер команды должен быть >= %d и <= %d (и не равно 1)\n",
        MIN_COMMAND_NUMBER, MAX_COMMAND_NUMBER);

        return WRONG_COMMAND_NUMBER;
    }
    
    return SUCCESS;
}
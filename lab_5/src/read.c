#include "../inc/read.h"

int read_start_number_action(int *st_num_act)
{
    printf("Введите число (1 или 2):\n"
           "    1 - для сравнения работы двух очередей (списка и массива) "
           "по памяти и времени;\n"
           "    2 - для решения задачи;\n"
           "Введите 0 для выхода из программы\n\n");
    
    int r = scanf("%d", st_num_act);

    if (r != 1 )
    {
        printf("Не удалось прочитать номер команды\n");
        return FAILED_TO_READ_COMMAND_NUMBER;
    }
    
    if ( *st_num_act < 0 || *st_num_act > 2)
    {
        printf("Номер команды должен быть >= %d и <= %d\n", 0, 2);
        return WRONG_COMMAND_NUMBER;
    }

    return SUCCESS;
}

int read_number_action(int *number_action)
{
    int r;
    
    printf("Введите номер команды: ");
    r = scanf("%d", number_action);
    printf("\n");
    
    if (r != 1)
    {
        printf("Не удалось прочитать номер команды\n");
        return FAILED_TO_READ_COMMAND_NUMBER;
    }
    
    if (*number_action < MIN_COMMAND_NUMBER || *number_action > MAX_COMMAND_NUMBER)
    {
        printf("Номер команды должен быть >= %d и <= %d\n",
        MIN_COMMAND_NUMBER, MAX_COMMAND_NUMBER);

        return WRONG_COMMAND_NUMBER;
    }
    
    return SUCCESS;
}

int read_number_of_add_elem_to_turn_array(int *numb_add_elem, int size)
{
    if (size == MAXIMUM_TURN_SIZE)
    {
        printf("Очередь заполнена.\n");
        return SUCCESS;
    }

    printf("Введите кол-во добавляемых элементов (не более %d): ", MAXIMUM_TURN_SIZE - size);

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
    else if (size + *numb_add_elem > MAXIMUM_TURN_SIZE)
    {
        printf("Произошло переполнение очереди.\n");
        return TURN_OVERFLOW;
    }

    return SUCCESS;
}

int read_new_elem(int *new_elem)
{
    int r = scanf("%d", new_elem);

    if (r != 1)
    {
        printf("Не удалось прочитать элемент очереди\n");
        return FAILED_TO_READ_TURN_ELEMENT;
    }

    return SUCCESS;
}

int read_number_of_remove_elem_from_turn_array(int *numb_remove_elem, int size)
{
    if (size == 0)
    {
        printf("Очередь пуста.\n");
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
        printf("В очереди нет столько элементов.\n");
        return TOO_MANY_REMOVABLE_ELEMENTS;
    }

    return SUCCESS;
}

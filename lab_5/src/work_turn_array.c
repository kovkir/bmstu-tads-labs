#include "../inc/work_turn_array.h"

int add_elem_to_turn_array(turn_array_t *turn_array, int numb_add_elem)
{
    int r;

    printf("Введите %d элемент(a, ов) очереди.\n", numb_add_elem);

    for (int i = 0; i < numb_add_elem; i++)
    {
        r = read_new_elem(turn_array->tail);

        if (r)
            return r;

        turn_array->tail--;
        turn_array->size++;
    }

    return SUCCESS;
}

void fill_turn_array_randomly(turn_array_t *turn_array, int numb_add_elem)
{
    srand(time(NULL));

    for (int i = 0; i < numb_add_elem; i++)
    {
        *turn_array->tail = MIN_BORDER + rand() % (MAX_BORDER - MIN_BORDER + 1);
        turn_array->tail--;
        turn_array->size++;
    }
}

void remove_elem_from_turn_array(turn_array_t *turn_array, int numb_remove_elem)
{
    for (int i = 0; i < numb_remove_elem; i++)
    {
        for (int j = 0; j < turn_array->size - 1; j++)
        {
            turn_array->head[-j] = turn_array->head[-j - 1];
        }

        turn_array->size--;
        turn_array->tail++;
    }
}

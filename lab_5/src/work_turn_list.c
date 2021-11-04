#include "../inc/work_turn_list.h"

int fill_turn_list_randomly(turn_list_t *list, int numb_add_elem)
{
    elem_turn_list_t *new_elem, **elem_turn_list = &list->head;

    while (*elem_turn_list != NULL)
    {
        elem_turn_list = &((*elem_turn_list)->next);
    }

    srand(time(NULL));

    for (int i = 0; i < numb_add_elem; i++)
    {
        new_elem = malloc(sizeof(elem_turn_list_t));

        if (!new_elem)
        {
            printf("Не удалось выделить память\n");
            return FAILED_TO_ALLOCATE_MEMORY;
        }

        new_elem->elem = MIN_BORDER + rand() % (MAX_BORDER - MIN_BORDER + 1);

        new_elem->next = NULL;
        new_elem->start = tick();
        
        *elem_turn_list = new_elem;
        elem_turn_list = &(*elem_turn_list)->next;
    }

    list->size += numb_add_elem;

    return SUCCESS;
}

void remove_elem_from_turn_list(turn_list_t *list, int numb_remove_elem)
{
    elem_turn_list_t *elem;

    for (int i = 0; i < numb_remove_elem; i++)
    {
        elem = list->head->next;
        free(list->head);
        list->head = elem;

        list->size--;
    }
}

int add_elem_to_turn_list(turn_list_t *list, int numb_add_elem, turn_array_t *array)
{
    elem_turn_list_t *new_elem, **elem_turn_list = &list->head;

    while (*elem_turn_list != NULL)
    {
        elem_turn_list = &((*elem_turn_list)->next);
    }

    for (int i = 0; i < numb_add_elem; i++)
    {
        new_elem = malloc(sizeof(elem_turn_list_t));

        if (!new_elem)
        {
            printf("Не удалось выделить память\n");
            return FAILED_TO_ALLOCATE_MEMORY;
        }

        new_elem->elem = array->head[-list->size];
        new_elem->next = NULL;

        *elem_turn_list = new_elem;
        elem_turn_list = &(*elem_turn_list)->next;

        list->size++;
    }

    return SUCCESS;
}

void free_turn_list(turn_list_t *list)
{
    elem_turn_list_t *p;

    while (list->head != NULL)
    {
        p = list->head->next;

        free(list->head);
        list->head = p;
    }
}

int add_addresses_of_removed_elem_to_array(array_of_freed_areas_t *array,
int numb_remove_elem, turn_list_t *list)
{
    elem_turn_list_t **p, *elem = list->head;

    for (int i = 0; i < numb_remove_elem; i++)
    {
        p = realloc(array->array, (array->size + 1) * sizeof(elem_turn_list_t*));

        if (!p)
        {
            free(array->array);
            printf("Не удалось выделить память\n");
            return FAILED_TO_ALLOCATE_MEMORY;
        }

        array->array = p;
        array->array[array->size] = elem;
        array->size++;
        elem = elem->next;
    }

    return SUCCESS;
}
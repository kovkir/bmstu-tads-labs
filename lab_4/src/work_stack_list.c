#include "../inc/work_stack_list.h"

int work_with_stack_list(void)
{
    int number_action, r;

    elem_stack_list_t *elem_stack_list = NULL;
    array_of_freed_areas_t array;

    array.array = NULL;
    array.size = 0;

    while(TRUE)
    {
        print_menu();

        r = read_number_action(&number_action);
        
        if (r)
        {
            free_stack_list(&elem_stack_list);
            free(array.array);
            return r;
        }
        
        // system("clear");

        if (number_action == 1)
        {   
            int numb_add_elem;

            r = read_number_of_add_elem_to_stack_list(&numb_add_elem, elem_stack_list);

            if (r)
            {
                free_stack_list(&elem_stack_list);
                free(array.array);
                return r;
            }
            
            if ((elem_stack_list != NULL && elem_stack_list->numb_elem != MAXIMUM_STACK_SIZE) ||
                 elem_stack_list == NULL)
            {
                r = add_elem_to_stack_list(&elem_stack_list, numb_add_elem);
            }
        }
        else if (number_action == 2)
        {
            int numb_add_elem;

            r = read_number_of_add_elem_to_stack_list(&numb_add_elem, elem_stack_list);

            if (r)
            {
                free_stack_list(&elem_stack_list);
                free(array.array);
                return r;
            }

            if ((elem_stack_list != NULL && elem_stack_list->numb_elem != MAXIMUM_STACK_SIZE) ||
                 elem_stack_list == NULL)
            {
                fill_stack_list_randomly(&elem_stack_list, numb_add_elem);
            }
        }
        else if (number_action == 3)
        {
            int numb_remove_elem;

            r = read_number_of_remove_elem_from_stack_list(&numb_remove_elem, elem_stack_list);

            if (r)
            {
                free_stack_list(&elem_stack_list);
                free(array.array);
                return r;
            }

            if (elem_stack_list != NULL)
            {
                r = add_addresses_of_removed_elem_to_array(&array, 
                numb_remove_elem, elem_stack_list);

                if (r)
                {
                    free_stack_list(&elem_stack_list);
                    return r;
                }

                remove_elem_from_stack_list(&elem_stack_list, numb_remove_elem);
            }
        }
        else if (number_action == 4)
        {
            print_stack_list(&elem_stack_list);

            int action;

            r = read_action(&action);

            if (r)
            {
                free_stack_list(&elem_stack_list);
                free(array.array);
                return r;
            }

            if (action == 1)
                print_array(&array);
        }
        else if (number_action == 5)
        {
            print_descend_sequen_stack_list(elem_stack_list, stdout);
        }
        else if (number_action == 0)
        {
            free_stack_list(&elem_stack_list);
            free(array.array);
            break;
        }
       
        if (r)
        {
            free_stack_list(&elem_stack_list);
            free(array.array);
            return r;
        }
    }

    return SUCCESS;
}

int add_elem_to_stack_list(elem_stack_list_t **elem_stack_list, int numb_add_elem)
{
    elem_stack_list_t *new_elem;

    int r;

    printf("Введите %d элемент(a, ов) стека.\n", numb_add_elem);

    for (int i = 0; i < numb_add_elem; i++)
    {
        new_elem = malloc(sizeof(elem_stack_list_t));

        if (!new_elem)
        {
            printf("Не удалось выделить память\n");
            return MEMORY_ALIGNMENT_ERROR;
        }

        r = read_new_elem(&new_elem->elem);

        if (r)
        {
            free(new_elem);
            return r;
        }

        if (*elem_stack_list == NULL)
            new_elem->numb_elem = 1;
        else
            new_elem->numb_elem = (*elem_stack_list)->numb_elem + 1;
        
        new_elem->next = *elem_stack_list;
        *elem_stack_list = new_elem;
    }
    
    return SUCCESS;
}

void remove_elem_from_stack_list(elem_stack_list_t **elem_stack_list, int numb_remove_elem)
{
    elem_stack_list_t *new_elem;

    for (int i = 0; i < numb_remove_elem; i++)
    {
        new_elem = (*elem_stack_list)->next;
        free(*elem_stack_list);
        *elem_stack_list = new_elem;
    }

    // printf("%d элемент(а, ов) успешно удалено из стека.\n", numb_remove_elem);
}

int fill_stack_list_randomly(elem_stack_list_t **elem_stack_list, int numb_add_elem)
{
    elem_stack_list_t *new_elem;

    srand(time(NULL));

    for (int i = 0; i < numb_add_elem; i++)
    {
        new_elem = malloc(sizeof(elem_stack_list_t));

        if (!new_elem)
        {
            printf("Не удалось выделить память\n");
            return MEMORY_ALIGNMENT_ERROR;
        }

        new_elem->elem = MIN_BORDER + rand() % (MAX_BORDER - MIN_BORDER + 1);

        if (*elem_stack_list == NULL)
            new_elem->numb_elem = 1;
        else
            new_elem->numb_elem = (*elem_stack_list)->numb_elem + 1;
        
        new_elem->next = *elem_stack_list;
        *elem_stack_list = new_elem;
    }

    return SUCCESS;
}

void free_stack_list(elem_stack_list_t **elem_stack_list)
{
    elem_stack_list_t *p;

    while (*elem_stack_list != NULL)
    {
        p = (*elem_stack_list)->next;

        free(*elem_stack_list);
        *elem_stack_list = p;
    }
}

int add_addresses_of_removed_elem_to_array(array_of_freed_areas_t *array,
int numb_remove_elem, elem_stack_list_t *elem_stack_list)
{
    elem_stack_list_t **p;

    for (int i = 0; i < numb_remove_elem; i++)
    {
        p = realloc(array->array, (array->size + 1) * sizeof(elem_stack_list_t*));

        if (!p)
        {
            free(array->array);
            printf("Не удалось выделить память\n");
            return MEMORY_ALIGNMENT_ERROR;
        }

        array->array = p;
        array->array[array->size] = elem_stack_list;
        array->size++;
        elem_stack_list = elem_stack_list->next;
    }

    return SUCCESS;
}
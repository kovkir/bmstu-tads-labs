#include "../inc/print.h"

void print_menu(void)
{
    printf("\n"
        "1. Добавить элементы в очередь;\n"
        "2. Добавить случайные элементы в очередь;\n"
        "3. Удалить элементы из очереди;\n"
        "4. Вывести текущее состояние очереди (массив);\n"
        "5. Вывести текущее состояние очереди (список);\n"
        "6. Вывести массив освобождённых адресов;\n"
        "0. Выйти из программы.\n\n");
}

void print_turn_array(turn_array_t *turn_array)
{
    printf("Текущий размер очереди - %d\n\n", turn_array->size);

    if (turn_array->size == 0)
        return;

    int *p = turn_array->head;

    printf("HEAD\n");

    while(p > turn_array->tail)
    {
        printf("%d\n", *(p--));
    }

    printf("TAIL\n");
}

void print_turn_list(turn_list_t *list)
{
    if (list->size == 0)
    {
        printf("Текущий размер очереди - 0\n\n");
        return;
    }
    else
    {
        printf("Текущий размер очереди - %d\n\n", list->size);
    }
    
    elem_turn_list_t *p = list->head;

    printf("HEAD\n");

    while (p != NULL)
    {
        printf("%-10d %p\n", p->elem, p);
        p = p->next;
    }

    printf("TAIL\n");
}

void print_freed_array(array_of_freed_areas_t *array)
{
    printf("\nМассив адресов освобождённых элементов стека:\n\n[");

    for (int i = 0; i < array->size; i++)
    {
        printf("%p", array->array[i]);

        if (i != array->size - 1)
            printf(", ");
    }

    printf("]\n");
}

#include "../inc/print.h"

void print_menu(void)
{
    printf("\n"
        "1. Добавить элементы в стек;\n"
        "2. Добавить случайные элементы в стек;\n"
        "3. Удалить элементы из стека;\n"
        "4. Вывести текущее состояние стека;\n"
        "5. Распечатать убывающие серии последовательности целых чисел в обратном порядке;\n"
        "0. Выйти из программы.\n\n");
}

void print_stack_array(stack_array_t *stack_array)
{
    printf("Текущий размер стека - %d\n\n", stack_array->size);

    int *p = stack_array->ptr;

    for (int i = stack_array->size; i > 0; i--)
    {
        printf("%d\n", *(p--));
    }
}

void print_stack_list(elem_stack_list_t **elem_stack_list)
{
    if (*elem_stack_list == NULL)
    {
        printf("Текущий размер стека - 0\n\n");
        return;
    }
    else
    {
        printf("Текущий размер стека - %d\n\n", (*elem_stack_list)->numb_elem);
    }
    
    elem_stack_list_t *p = *elem_stack_list;

    while (p != NULL)
    {
        printf("%-10d %p\n", p->elem, p);
        p = p->next;
    }
}

void print_array(array_of_freed_areas_t *array)
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

void print_descend_sequen_stack_list(elem_stack_list_t *elem_stack_list, FILE *f)
{
    if (elem_stack_list == NULL)
    {
        fprintf(f, "Стек пуст.\n");
        return;
    }

    fprintf(f, "Убывающие серии последовательности целых чисел в обратном порядке "
           "(каждая серия на отдельной строке):\n\n");
    
    int prev_elem, k;

    while (elem_stack_list != NULL && elem_stack_list->next != NULL)
    {
        prev_elem = elem_stack_list->elem;
        k = 0;

        elem_stack_list = elem_stack_list->next;

        while (elem_stack_list != NULL &&
               elem_stack_list->elem > prev_elem)
        {
            fprintf(f, "%d ", prev_elem);

            prev_elem = elem_stack_list->elem;
            elem_stack_list = elem_stack_list->next;
            k = 1;
        }

        if (k == 1)
            fprintf(f, "%d\n", prev_elem);
    }
}

void print_descend_sequen_stack_array(stack_array_t stack_array, FILE *f)
{
    if (stack_array.size == 0)
    {
        fprintf(f, "Стек пуст.\n");
        return;
    }

    fprintf(f, "Убывающие серии последовательности целых чисел в обратном порядке "
           "(каждая серия на отдельной строке):\n\n");
    
    int prev_elem, k;

    while (stack_array.size > 1)
    {
        prev_elem = *stack_array.ptr;
        k = 0;

        stack_array.ptr--;
        stack_array.size--;

        while (stack_array.size > 0 && *stack_array.ptr > prev_elem)
        {
            fprintf(f, "%d ", prev_elem);

            prev_elem = *stack_array.ptr;
            stack_array.ptr--;
            stack_array.size--;

            k = 1;
        }

        if (k == 1)
            fprintf(f, "%d\n", prev_elem);
    }
}

void print_menu_time(void)
{
    printf("\n"
        "2. Добавить случайные элементы в стек;\n"
        "3. Удалить элементы из стека;\n"
        "4. Вывести текущее состояние стека;\n"
        "5. Распечатать убывающие серии последовательности целых чисел в обратном порядке;\n"
        "0. Выйти из программы.\n\n");
}
#include "../inc/read.h"

int read_number_of_elem_of_graph(int *number, FILE *f)
{
    if (f == stdin)
        printf("Введите кол-во вершин графа: ");

    int r = fscanf(f, "%d", number);

    if (r != 1)
    {
        printf("\n\x1B[31mНе удалось прочитать кол-во вершин графа\x1B[0m\n\n");
        return FAILED_TO_READ_NUMBER_OF_ELEM;
    }
    else if (*number <= 0)
    {
        printf("\n\x1B[31mКол-во вершин графа должно быть больше 0\x1B[0m\n\n");
        return NEGATIVE_NUMBER_OF_ELEM;
    }

    if (f == stdin)
        printf("\nВведите пары связанных вершин графа.\n"
            "Введите 0, как признак окончания ввода.\n\n");

    return SUCCESS;
}

int read_number(int *number, int min_number, int max_number, FILE *f)
{
    int r = fscanf(f, "%d", number);

    if (r != 1)
    {
        printf("\n\x1B[31mНе удалось прочитать вершину графа\x1B[0m\n\n");
        return FAILED_TO_READ_ELEM_OF_GRAPH;
    }
    else if (*number < min_number || *number > max_number)
    {
        printf("\n\x1B[31mТакой вершины в графе нет\x1B[0m\n\n");
        return INCORRECT_GRAPH_ITEM;
    }

    return SUCCESS;
}

int read_number_action(int *number_action, int max_command_number)
{
    int r;
    
    printf("Введите номер команды: ");
    r = scanf("%d", number_action);
    printf("\n");

    if (r != 1)
    {
        printf("\x1B[31mНе удалось прочитать номер команды\x1B[0m\n\n");
        return FAILED_TO_READ_COMMAND_NUMBER;
    }
    
    if (*number_action < MIN_COMMAND_NUMBER || *number_action > max_command_number)
    {
        printf("\x1B[31mНомер команды должен быть >= %d и <= %d\x1B[0m\n\n",
        MIN_COMMAND_NUMBER, max_command_number);

        return WRONG_COMMAND_NUMBER;
    }
    
    return SUCCESS;
}

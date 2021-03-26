#include "../inc/graph.h"

int fill_graph_matrix(graph_h *graph, FILE *f)
{
    int r, i = 0, j;

    while (i != -1)
    {
        r = read_number(&i, 0, graph->size, f);

        if (r)
        {
            free_matrix(graph->matrix, graph->size);
            return r;
        }

        if (i == 0)
            break;

        r = read_number(&j, 1, graph->size, f);

        if (r)
        {
            free_matrix(graph->matrix, graph->size);
            return r;
        }

        graph->matrix[i - 1][j -1] = 1;
    }

    if (f == stdin)
        printf("\n");
        
    return SUCCESS;
}

int elem_in_array(int number, int *array, int array_size)
{
    for (int i = 0; i < array_size; i++)
    {
        if (array[i] == number)
            return YES;
    }

    return NO;
}

void dfs(graph_h *graph, int *peaks_array, int *peaks_array_size, int vertex)
{
    for (int j = 0; j < graph->size; j++)
    {
        if (graph->matrix[vertex][j] == 1)
        {
            if (elem_in_array(j + 1, peaks_array, *peaks_array_size) == NO)
            {
                peaks_array[*peaks_array_size] = j + 1;
                (*peaks_array_size)++;

                dfs(graph, peaks_array, peaks_array_size, j);
            }
        }
    }
}

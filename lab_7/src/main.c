#include "../inc/main.h"

int main(void)
{
    system("clear");

    graph_h graph;

    print_start_menu();

    int action, r;

    r = read_number_action(&action, 4);

    if (r)
        return r;

    char name_file_5[] = "./data/data5.txt",
        name_file_10[] = "./data/data10.txt",
        name_file_15[] = "./data/data15.txt";

    FILE *f;

    if (action == 1)
    {
        f = fopen(name_file_5, "r");
    }
    else if (action == 2)
    {
        f = fopen(name_file_10, "r");
    }
    else if (action == 3)
    {
        f = fopen(name_file_15, "r");
    }
    else if (action == 4)
    {
        f = stdin;
    }
    else
    {
        return SUCCESS;
    }

    if (!f)
    {
        printf("\x1B[31mНе удалось открыть файл\x1B[0m\n\n");
        return FILE_OPENING_ERROR;
    }

    r = read_number_of_elem_of_graph(&graph.size, f);
    
    if (r)
        return r;

    graph.matrix = allocate_matrix(graph.size, graph.size);

    if (!graph.matrix)
        return FAILED_TO_ALLOCATE_MEMORY;

    r = fill_graph_matrix(&graph, f);

    if (r)
        return r;

    if (action != 4)
    {
        if (fclose(f))
        {
            free_matrix(graph.matrix, graph.size);
            return FILE_CLOSING_ERROR;
        }   
    }

    // print_matrix(&graph);

    int *peaks_array = malloc(graph.size * sizeof(int));

    if (!peaks_array)
    {
        free_matrix(graph.matrix, graph.size);
        return FAILED_TO_ALLOCATE_MEMORY;
    }

    int peaks_array_size, vertex;
    
    while (TRUE)
    {
        printf("Введите одну из вершин графа: ");
        r = read_number(&vertex, 1, graph.size, stdin);

        if (r)
        {
            free(peaks_array);
            free_matrix(graph.matrix, graph.size);
            return r;
        }

        peaks_array_size = 0;
        dfs(&graph, peaks_array, &peaks_array_size, vertex - 1);

        // for (int i = 0; i < peaks_array_size; printf("%d ", peaks_array[i]), i++);
        // printf("\n");

        f = fopen("graph.dot", "w");

        if (!f)
        {
            free(peaks_array);
            free_matrix(graph.matrix, graph.size);
            return FILE_OPENING_ERROR;
        }

        print_graph(&graph, vertex, peaks_array, peaks_array_size, f);

        if (fclose(f))
        {
            free(peaks_array);
            free_matrix(graph.matrix, graph.size);
            return FILE_CLOSING_ERROR;
        }

        system("dot -Tpng -O graph.dot && open graph.dot.png");

        print_menu();

        r = read_number_action(&action, 1);

        if (r)
        {
            free(peaks_array);
            free_matrix(graph.matrix, graph.size);
            return r;
        }

        if (action == 0)
            break;
    }

    free(peaks_array);
    free_matrix(graph.matrix, graph.size);
    
    return 0;
}

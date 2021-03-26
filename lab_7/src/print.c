#include "../inc/print.h"

char str_beg[] = "digraph g{\n"
        "    node[style=|filled|, fillcolor=|lightpink|, color=|red|,fontsize=14];\n"
        "    edge[color=|red|,fontsize=14];\n\n";

char str_color_node[] = " [style=|filled|, fillcolor=|lightgreen|, color=|darkgreen|];\n";
char str_color_vertex[] = " [style=|filled|, fillcolor=|lightblue|, color=|darkblue|];\n";
char str_color_edge[] = "[color=|darkgreen|]\n";

void print_start_menu(void)
{
    printf("\n\x1B[32m"
        "1. Загрузить данные из файла (5 элементов в графе);\n"
        "2. Загрузить данные из файла (10 элементов в графе);\n"
        "3. Загрузить данные из файла (15 элементов в графе);\n"
        "4. Ввести данные вручную;\n"
        "0. Выйти из программы.\x1B[0m\n\n");
}

void print_menu(void)
{
    printf("\n\x1B[32m"
        "1. Задать новую вершину;\n"
        "0. Выйти из программы.\x1B[0m\n\n");
}

void print_matrix(graph_h *graph)
{
    for (int i = 0; i < graph->size; i++)
    {
        for (int j = 0; j < graph->size; j++)
        {
            printf("% d ", graph->matrix[i][j]);
        }
        printf("\n");
    }
}

void print_graph(graph_h *graph, int vertex, int *peaks_array, int peaks_array_size, FILE *f)
{
    for (int i = 0; str_beg[i] != '\0'; i++)
    {
        if (str_beg[i] == '|')
        {
            fprintf(f, "%c", '"');
        }
        else
        {
            fprintf(f, "%c", str_beg[i]);
        }
    }

    for (int i = 0; i < peaks_array_size; i++)
    {
        fprintf(f, "    %c%d%c", '"', peaks_array[i], '"');

        for (int j = 0; str_color_node[j] != '\0'; j++)
        {   
            if (str_color_node[j] == '|')
            {
                fprintf(f, "%c", '"');
            }
            else
            {
                fprintf(f, "%c", str_color_node[j]);
            }
        }
    }

    fprintf(f, "    %c%d%c", '"', vertex, '"');

    for (int j = 0; str_color_vertex[j] != '\0'; j++)
    {   
        if (str_color_vertex[j] == '|')
        {
            fprintf(f, "%c", '"');
        }
        else
        {
            fprintf(f, "%c", str_color_vertex[j]);
        }
    }

    fprintf(f, "\n");

    for (int i = 0; i < graph->size; i++)
    {
        for (int j = 0; j < graph->size; j++)
        {
            if (graph->matrix[i][j] == 1)
            {
                fprintf(f, "    %d -> %d", i + 1, j + 1);

                if (elem_in_array(i + 1, peaks_array, peaks_array_size) == YES || i + 1 == vertex)
                {
                    for (int u = 0; str_color_edge[u] != '\0'; u++)
                    {   
                        if (str_color_edge[u] == '|')
                        {
                            fprintf(f, "%c", '"');
                        }
                        else
                        {
                            fprintf(f, "%c", str_color_edge[u]);
                        }
                    }
                }
                else
                {
                    fprintf(f, "\n");
                }
            }
        }   
    }

    fprintf(f, "}");
}

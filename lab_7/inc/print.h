#ifndef PRINT_H
#define PRINT_H

#include <stdio.h>
#include <stdlib.h>

#include "errors.h"
#include "struct.h"
#include "graph.h"

void print_start_menu(void);

void print_menu(void);

void print_matrix(graph_h *graph);

void print_graph(graph_h *graph, int vertex, int *peaks_array, int peaks_array_size, FILE *f);

#endif

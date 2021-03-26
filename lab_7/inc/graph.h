#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>

#include "errors.h"
#include "struct.h"
#include "read.h"
#include "alloc_free_memory.h"

#define YES 1
#define NO 0

int fill_graph_matrix(graph_h *graph, FILE *f);

int elem_in_array(int number, int *array, int array_size);

void dfs(graph_h *graph, int *peaks_array, int *peaks_array_size, int vertex);

#endif

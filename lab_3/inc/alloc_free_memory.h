#ifndef ALLOC_FREE_MEMORY_H
#define ALLOC_FREE_MEMORY_H

#include <stdio.h>
#include <stdlib.h>

#include "errors.h"
#include "structures.h"

#define MAX(a, b) a > b ? a : b

void free_matrix(int **data, int n);

int **allocate_matrix(int n, int m);

int create_ordinary_matrix(matrix_t *matrix);

int create_special_matrix(special_matrix_t *matrix);

void free_special_matrix(special_matrix_t *matrix);

#endif

#ifndef WORK_WITH_MATRIX_H
#define WORK_WITH_MATRIX_H

#include <stdio.h>
#include <stdlib.h>

#include "structures.h" 
#include "errors.h"

int convert_linked_list(special_matrix_t *matrix);

void sort(special_matrix_t *matrix);

int find_matrix_element(matrix_t *const matrix_a, matrix_t *const matrix_b,
const int i, const int j);

int find_number_non_zero_elem(special_matrix_t *matrix, const int fill_percentage);

#endif

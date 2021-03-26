#ifndef READ_H
#define READ_H

#include <stdio.h>
#include <stdlib.h>

#include "errors.h"
#include "constants.h" 
#include "structures.h"
#include "work_with_matrix.h"

int read_number_action(int *number_action);

int read_rows_and_columns_of_matrix(int *number_rows, int *number_columns);

int read_ord_matrix_input_method(int *input_method, int *fill_percentage);

int read_spec_matrix_input_method(int *input_method, int *fill_percentage);

int read_whole_matrix(matrix_t *const matrix);

int read_non_zero_elem_of_matrix(matrix_t *const matrix);

int read_number_non_zero_elem(special_matrix_t *matrix);

int read_vector_a_elem(special_matrix_t *matrix, const int i);

int read_vector_ja_elem(special_matrix_t *matrix, const int i);

int read_linked_list_elem(special_matrix_t *matrix, const int i);

int read_special_matrix(special_matrix_t *matrix);

#endif

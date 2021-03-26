#ifndef MATRIX_MULTIPLICATION_H
#define MATRIX_MULTIPLICATION_H

#include <stdlib.h>
#include <stdio.h>

#include "macrologger.h"

#include "errors.h"
#include "constants.h"
#include "alloc_free_memory.h"
#include "structures.h"
#include "read.h"
#include "print.h"
#include "random_filling.h"
#include "work_with_matrix.h"

void ordinary_matrix_multiplication(matrix_t *const res_matrix,
matrix_t *const matrix_a, matrix_t *const matrix_b);

int ordinary_multiplication(void);

int special_matrix_multiplication(special_matrix_t *const res_matrix,
special_matrix_t *const matrix_a, special_matrix_t *const matrix_b);

int special_multiplication(void);

#endif

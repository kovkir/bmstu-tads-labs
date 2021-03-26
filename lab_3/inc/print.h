#ifndef PRINT_H
#define PRINT_H

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#include "errors.h"
#include "constants.h"
#include "structures.h"

void print_menu(void);

void print_ordinary_matrix(matrix_t *matrix);

void print_special_matrix(special_matrix_t *matrix);

void print_result(int64_t start, int64_t end);

#endif

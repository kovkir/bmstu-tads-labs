#ifndef RANDOM_FILLING_H
#define RANDOM_FILLING_H

#include <stdlib.h>
#include <time.h>

#include "structures.h"
#include "constants.h"
#include "errors.h"
#include "read.h"

int random_fill_ord_matrix(matrix_t *matrix, const int fill_percentage);

int random_fill_spec_matrix(special_matrix_t *matrix);

#endif

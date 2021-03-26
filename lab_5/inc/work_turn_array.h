#ifndef WORK_TURN_ARRAY_H
#define WORK_TURN_ARRAY_H

#include <stdlib.h>
#include <time.h>

#include "errors.h"
#include "structures.h"
#include "comparison_time_memory.h"

int add_elem_to_turn_array(turn_array_t *turn_array, int numb_add_elem);

void fill_turn_array_randomly(turn_array_t *turn_array, int numb_add_elem);

void remove_elem_from_turn_array(turn_array_t *turn_array, int numb_remove_elem);

#endif
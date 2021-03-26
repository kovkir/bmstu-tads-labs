#ifndef WORK_TURN_LIST_H
#define WORK_TURN_LIST_H

#include <stdlib.h>
#include <time.h>

#include "errors.h"
#include "structures.h"
#include "comparison_time_memory.h"
#include "macrologger.h"

int fill_turn_list_randomly(turn_list_t *list, int numb_add_elem);

void remove_elem_from_turn_list(turn_list_t *list, int numb_remove_elem);

int add_elem_to_turn_list(turn_list_t *list, int numb_add_elem, turn_array_t *array);

void free_turn_list(turn_list_t *list);

int add_addresses_of_removed_elem_to_array(array_of_freed_areas_t *array,
int numb_remove_elem, turn_list_t *list);

#endif

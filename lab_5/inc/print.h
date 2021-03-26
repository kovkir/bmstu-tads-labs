#ifndef PRINT_H
#define PRINT_H

#include <stdio.h>

#include "errors.h"
#include "structures.h"

void print_menu(void);

void print_turn_array(turn_array_t *turn_array);

void print_turn_list(turn_list_t *list);

void print_freed_array(array_of_freed_areas_t *array);

#endif

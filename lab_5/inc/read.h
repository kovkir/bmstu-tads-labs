#ifndef READ_H
#define READ_H

#include <stdio.h>

#include "errors.h"
#include "structures.h"

#define MIN_COMMAND_NUMBER 0
#define MAX_COMMAND_NUMBER 6

int read_start_number_action(int *st_num_act);

int read_number_action(int *number_action);

int read_number_of_add_elem_to_turn_array(int *numb_add_elem, int size);

int read_new_elem(int *new_elem);

int read_number_of_remove_elem_from_turn_array(int *numb_remove_elem, int size);

#endif

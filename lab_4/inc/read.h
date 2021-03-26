#ifndef READ_H
#define READ_H

#include <stdio.h>

#include "errors.h"
#include "structures.h"

#define MIN_COMMAND_NUMBER 0
#define MAX_COMMAND_NUMBER 5

int read_stack_type(int *stack_type);

int read_number_action(int *number_action);

int read_number_of_add_elem_to_stack_array(int *numb_add_elem, int size);

int read_new_elem(int *new_elem);

int read_number_of_remove_elem_from_stack_array(int *numb_remove_elem, int size);

int read_number_of_add_elem_to_stack_list(int *numb_add_elem, elem_stack_list_t *elem_stack_list);

int read_number_of_remove_elem_from_stack_list(int *numb_remove_elem, 
elem_stack_list_t *elem_stack_list);

int read_action(int *action);

int read_number_action_time(int *number_action);

#endif

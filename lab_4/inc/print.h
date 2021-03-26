#ifndef PRINT_H
#define PRINT_H

#include <stdio.h>

#include "errors.h"
#include "structures.h"

void print_menu(void);

void print_stack_array(stack_array_t *stack_array);

void print_stack_list(elem_stack_list_t **elem_stack_list);

void print_array(array_of_freed_areas_t *array);

void print_descend_sequen_stack_list(elem_stack_list_t *elem_stack_list, FILE *f);

void print_descend_sequen_stack_array(stack_array_t stack_array, FILE *f);

void print_menu_time(void);

#endif

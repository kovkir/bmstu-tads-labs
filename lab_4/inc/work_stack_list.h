#ifndef WORK_STACK_LIST_H
#define WORK_STACK_LIST_H

#include <stdlib.h>
#include <time.h>

#include "errors.h"
#include "structures.h"
#include "read.h"
#include "print.h"
#include "work_stack_array.h"

int work_with_stack_list(void);

int add_elem_to_stack_list(elem_stack_list_t **elem_stack_list, int numb_add_elem);

void remove_elem_from_stack_list(elem_stack_list_t **elem_stack_list, int numb_remove_elem);

int fill_stack_list_randomly(elem_stack_list_t **elem_stack_list, int numb_add_elem);

void free_stack_list(elem_stack_list_t **elem_stack_list);

int add_addresses_of_removed_elem_to_array(array_of_freed_areas_t *array,
int numb_remove_elem, elem_stack_list_t *elem_stack_list);

#endif

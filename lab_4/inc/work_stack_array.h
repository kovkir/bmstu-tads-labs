#ifndef WORK_STACK_ARRAY_H
#define WORK_STACK_ARRAY_H

#include <stdlib.h>
#include <time.h>

#include "structures.h"
#include "errors.h"
#include "read.h"
#include "print.h"

#define MIN_BORDER -100
#define MAX_BORDER 100

#define TRUE 1

int work_with_stack_array(void);

int add_elem_to_stack_array(stack_array_t *stack_array, int numb_add_elem);

void remove_elem_from_stack_array(stack_array_t *stack_array, int numb_remove_elem);

void fill_stack_array_randomly(stack_array_t *stack_array, int numb_add_elem);

#endif
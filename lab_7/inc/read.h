#ifndef READ_H
#define READ_H

#include <stdio.h>

#include "errors.h"
#include "struct.h"

#define MIN_COMMAND_NUMBER 0

int read_number_of_elem_of_graph(int *number, FILE *f);

int read_number(int *number, int min_number, int max_number, FILE *f);

int read_number_action(int *number_action, int max_command_number);

#endif

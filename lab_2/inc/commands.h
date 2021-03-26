#ifndef COMMANDS_H
#define COMMANDS_H

#include "constants_and_errors.h"
#include "structures.h"
#include "read.h"

int fill_out_the_theater_repertoire(FILE * f, theaters_t * theather);

int fill_in_the_table(const char *name_file, const int max_size, table_t * table);

int add_a_performance(table_t * table);

int delete_specific_lines(table_t * table);

void create_an_array_of_keys(table_t * table);

#endif

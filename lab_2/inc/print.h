#ifndef PRINT_H
#define PRINT_H

#include "structures.h"

void print_table(table_t * table);

void print_menu(void);

void print_line(const int i, theaters_t * theaters);

int print_of_the_required_performances(table_t * table);

void print_an_array_of_keys(table_t * table);

#endif

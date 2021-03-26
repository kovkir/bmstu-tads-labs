#ifndef SORT_H
#define SORT_H

#include "structures.h"
#include "print.h"

void sorting_an_array_of_keys_qsort(table_t * table);

int compare_k(const keys_t * arg_1, const keys_t * arg_2);

void sorting_an_array_of_keys_choice(table_t * table);

void sort_the_table_qsort(table_t * table);

int compare_t(const theaters_t * arg_1, const theaters_t * arg_2);

void sort_the_table_choice(table_t * table);

void sort_the_array_using_keys(table_t * table);

#endif

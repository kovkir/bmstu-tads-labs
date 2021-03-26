#ifndef WORK_WITH_TABLE_H
#define WORK_WITH_TABLE_H

#include <stdio.h>
#include <stdlib.h>

#include "errors.h"
#include "struct.h"
#include "work_with_tree.h"

int add_item_to_table(hash_table_t *table, int number);

int search_elem_in_hash_table(hash_table_t *table, int number, int *total_compare);

void remove_item_from_table(hash_table_t *table, int number, int index);

void calculate_number_of_comparisons(int *buf, int size_buf, hash_table_t *table);

#endif

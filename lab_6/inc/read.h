#ifndef READ_H
#define READ_H

#include <stdio.h>
#include <stdlib.h>

#include "errors.h"
#include "struct.h"
#include "work_with_tree.h"

#define MAX_NUMBER_OF_ELEM_IN_FILE 1000

#define MIN_COMMAND_NUMBER 0

int fill_buffer(int *buf, int *size_buf, FILE *f);

int read_tree(tree_t *tree, int *buf, int size_buf);

int read_balanced_tree_elem(vertex_t **root, int *buf, int size_buf, int height);

int read_balanced_tree(tree_t *tree, int *buf, int size_buf);

int read_number_action(int *number_action, int max_command_number);

int read_number(int *number);

int read_hash_table(hash_table_t *table, int *buf, int size_buf);

int read_number_of_comparisons(int *number);

#endif

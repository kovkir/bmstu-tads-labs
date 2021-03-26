#ifndef WORK_WITH_TREE_H
#define WORK_WITH_TREE_H

#include <stdio.h>
#include <stdlib.h>

#include "errors.h"
#include "struct.h"
#include "read.h"

#define YES 0
#define NO 1

void free_tree(vertex_t *root);

int create_vertex(vertex_t **vertex, int height);

int comparator(const void *var1, const void *var2);

int search_elem(int number, vertex_t *root, vertex_t **prev_elem, int *total_compare);

int insert_element_into_tree(vertex_t *prev_elem, int number, tree_t *tree);

void remove_item_from_buffer(int *buf, int *size_buf, int number);

int add_item_to_buffer(int *buf, int *size_buf, int number);

void remove_item_from_tree(vertex_t *prev_elem, int number, tree_t *tree);

void reduce_levels(vertex_t *next_elem);

int search_min_elem(vertex_t *root, vertex_t **prev_elem);

void tree_balance_check(vertex_t *root, int *fill_in_again, int max_height);

void calculate_number_of_comparisons_in_tree(int *buf, int size_buf, tree_t *tree);

#endif

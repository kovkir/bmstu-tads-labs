#ifndef PRINT_H
#define PRINT_H

#include <stdio.h>
#include <math.h>

#include "struct.h"

void print_start_menu(void);

void print_tree_menu(void);

void print_hash_table_menu(void);

int print_tree_level(vertex_t *root, int height, int max_height, int *print_elem, FILE *f);

int print_tree(vertex_t *root, int *max_height, FILE *f);

void print_tree_table_level(vertex_t *root, int height, int *print_elem, vertex_t *prev_vertex);

void print_tree_table(vertex_t *root, int max_height);

void print_hash_table(hash_table_t *table);

void print_tree_sideways_level(vertex_t *root, int place);

void print_tree_sideways(vertex_t *root, int place);

#endif

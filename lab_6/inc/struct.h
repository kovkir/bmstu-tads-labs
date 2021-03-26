#ifndef STRUCT_H
#define STRUCT_H

typedef struct vertex
{
    struct vertex *left;
    struct vertex *right;
    int number;
    int height;
} vertex_t;

typedef struct tree
{
    vertex_t *root;
    int size;
    int height;
    int total_compare;
} tree_t;

typedef struct hash_elem
{
    int number;
    char bool;
} hash_elem_t;

typedef struct hash_table
{
    hash_elem_t *array;
    int size;
    int divider;
    int elements;
    int total_compare;
} hash_table_t;

#endif

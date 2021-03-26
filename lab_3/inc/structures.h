#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct matrix
{
    int **matrix;
    int numb_rows;
    int numb_columns;
} matrix_t;

typedef struct special_matrix
{
    int *vector_a;
    int *vector_ja;
    int *linked_list;
    int numb_rows;
    int numb_columns;
    int numb_non_zero_elem;
} special_matrix_t;

#endif

#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <stdint.h>
#include <inttypes.h>

#define MAXIMUM_TURN_SIZE 1000

typedef struct turn_array
{
    int *head;
    int *tail;
    int size;
} turn_array_t;

typedef struct elem_turn_list
{   
    int64_t start;
    int elem;
    struct elem_turn_list *next;
} elem_turn_list_t;

typedef struct turn_list
{
    elem_turn_list_t *head;
    int size;
} turn_list_t;

typedef struct array_of_freed_areas
{
    elem_turn_list_t **array;
    int size;
} array_of_freed_areas_t;

#endif

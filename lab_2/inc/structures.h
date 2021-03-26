#ifndef STRUCTURES_H
#define STRUCTURES_H

#include "constants_and_errors.h"

typedef struct
{
    int min_age;
    char type[MAXIMUM_LENGTH_TYPE_OF_PERFOMANCE_FOR_CHILDREN + 2];
} child_t;

typedef struct
{
    char type[MAXIMUM_LENGTH_TYPE_OF_PERFOMANCE_FOR_ADULTS + 2];
} adult_t;

typedef struct
{
    char composer[MAXIMUM_COMPOSER_NAME_LENGTH + 1];
    char country[MAXIMUM_COUNTRY_NAME_LENGTH + 1];
    int min_age;
    int duration;
} musical_t;

typedef union
{
    child_t child;
    adult_t adult;
    musical_t musical;
} type_of_performance_t;

typedef struct
{
    char theater_name[MAXIMUM_LENGTH_OF_THEATER_NAME + 1];
    char performance[MAXIMUM_LENGTH_OF_PERFORMANCE_NAME + 1];
    char producer[MAXIMUM_LENGTH_OF_PRODUCER_NAME + 1];
    int min_price;
    int max_price;
    char str_type_of_performance[MAXIMUM_LENGTH_TYPE_OF_SPECTACL + 2];
    type_of_performance_t type_of_performance;
} theaters_t;

typedef struct
{
    int index;
    char array[MAXIMUM_LENGTH_OF_PERFORMANCE_NAME + 1];
} keys_t;

typedef struct
{
    theaters_t theaters[MAXIMUM_TABLE_SIZE];
    keys_t keys[MAXIMUM_TABLE_SIZE];
    int size;
} table_t;

#endif

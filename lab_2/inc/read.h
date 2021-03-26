#ifndef READ_H
#define READ_H

#include "constants_and_errors.h"
#include "structures.h"

int read_the_number_of_records(FILE * f, int * size, const int max_size); 

int read_a_word(FILE * f, const int max_len, char word[]);

int read_the_price_range(FILE *f, int * const min_price, int * const max_price);

int fill_in_the_information_about_the_child_performance(FILE * f, child_t * child);

int fill_in_the_information_about_the_adult_performance(FILE * f, adult_t * adult);

int fill_in_the_information_about_the_musical_performance(FILE * f, musical_t * musical);

int read_the_type_of_performance(FILE *f, char str_type_of_performance[], type_of_performance_t * type_of_performance);

int read_number_action(int *number_action);

#endif

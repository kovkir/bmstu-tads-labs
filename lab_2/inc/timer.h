#ifndef TIMER_H
#define TIMER_H

#include "structures.h"
#include "constants_and_errors.h"
#include "sort.h"
#include "commands.h"

uint64_t tick(void);

void print_result(int64_t start, int64_t end);

int compare_sorts(const char name_file[], table_t * table);

#endif

#ifndef TIME_H
#define TIME_H

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#include "errors.h"
#include "structures.h"
#include "work_stack_array.h"
#include "work_stack_list.h"
#include "read.h"
#include "print.h"

#define HZ 2300000000
#define NUMBER_OF_RUNS 1000

uint64_t tick(void);

void print_result(int64_t start, int64_t end);

int compare_stacks(void);

#endif
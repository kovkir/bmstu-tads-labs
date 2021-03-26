#ifndef TIME_H
#define TIME_H

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#include "errors.h"
#include "structures.h"
#include "read.h"
#include "print.h"
#include "work_turn_array.h"
#include "work_turn_list.h"

#define HZ 2300000000
#define NUMBER_OF_RUNS 1000

#define MIN_BORDER -100
#define MAX_BORDER 100

#define TRUE 1

uint64_t tick(void);

void print_result(int64_t start, int64_t end);

int compare_turns(void);

#endif
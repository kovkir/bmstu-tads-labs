#ifndef MEASUREMENTS_H
#define MEASUREMENTS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <time.h>

#include "errors.h"
#include "struct.h"
#include "read.h"
#include "print.h"
#include "work_with_tree.h"
#include "work_with_table.h"

#define HZ 2300000000

#define NUMBER_OF_RUNS 1000
#define STEP 2

uint64_t tick(void);

void print_result(int64_t start, int64_t end);

int measurements(int buf_size);

#endif

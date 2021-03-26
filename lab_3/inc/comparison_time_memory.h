#ifndef COMPARISON_TIME_MEMORY_H
#define COMPARISON_TIME_MEMORY_H

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#include "errors.h"
#include "constants.h"
#include "alloc_free_memory.h"
#include "structures.h"
#include "print.h"
#include "random_filling.h"
#include "matrix_multiplication.h"

uint64_t tick(void);

int comparison_time_memory(void);

#endif

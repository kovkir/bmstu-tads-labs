#ifndef SOLUTION_OF_PROBLEM_H
#define SOLUTION_OF_PROBLEM_H

#include <stdlib.h>
#include <time.h>

#include "structures.h"
#include "errors.h"
#include "read.h"
#include "print.h"
#include "work_turn_list.h"
#include "comparison_time_memory.h"

#define UNIT_OF_TIME 100000

#define MIN_T1 0 * UNIT_OF_TIME
#define MAX_T1 5 * UNIT_OF_TIME

#define MIN_T2 0 * UNIT_OF_TIME
#define MAX_T2 4 * UNIT_OF_TIME

#define MIN_T3 0 * UNIT_OF_TIME
#define MAX_T3 4 * UNIT_OF_TIME

int solution_of_problem(void);

#endif
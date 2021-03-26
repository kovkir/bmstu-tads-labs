#ifndef MAIN_ACTIONS_H
#define MAIN_ACTIONS_H

#include <stdio.h>
#include <stdlib.h>

#include "errors.h"
#include "struct.h"
#include "read.h"
#include "print.h"
#include "work_with_tree.h"
#include "work_with_table.h"

int work_with_trees(int *buf, int size_buf);

int work_with_hash_table(int *buf, int size_buf);

int add_item_to_file(int *buf, int size_buf, FILE *f);

#define TRUE 1

#endif

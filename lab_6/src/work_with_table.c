#include "../inc/work_with_table.h"

int add_item_to_table(hash_table_t *table, int number)
{
    int index;
    hash_elem_t *p;

    if (!table->array)
        index = -1;
    else
        index = number % table->divider;
    
    while(!table->array || table->array[index].bool == '1')
    {
        if (++index == table->size)
        {
            p = realloc(table->array, (++table->size) * sizeof(hash_elem_t));

            if (!p)
                return MEMORY_ALIGNMENT_ERROR;

            table->array = p;
            table->array[index].bool = '0';
        }
    }

    table->array[index].number = number;
    table->array[index].bool = '1';

    table->elements++;

    return SUCCESS;
}

int search_elem_in_hash_table(hash_table_t *table, int number, int *total_compare)
{
    if (!table->array)
        return -1;

    int index = number % table->divider;

    for (int i = index; i < table->size; i++)
    {   
        (*total_compare)++;

        if (table->array[i].bool == '1' && table->array[i].number == number)
            return i;
    }

    return -1;
}

void remove_item_from_table(hash_table_t *table, int number, int index)
{
    table->array[index].bool = '0';
    table->elements--;
}

void calculate_number_of_comparisons(int *buf, int size_buf, hash_table_t *table)
{   
    table->total_compare = 0;

    for (int i = 0; i < size_buf; i++)
    {
        search_elem_in_hash_table(table, buf[i], &table->total_compare);
    }
}

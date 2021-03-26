#include "../inc/comparison_time_memory.h"

uint64_t tick(void)
{
    uint32_t high, low;
    __asm__ __volatile__ (
        "rdtsc\n"
        "movl %%edx, %0\n"
        "movl %%eax, %1\n"
        : "=r" (high), "=r" (low)
        :: "%rax", "%rbx", "%rcx", "%rdx"
        );

    uint64_t ticks = ((uint64_t)high << 32) | low;

    return ticks;
}

int comparison(const int fill_percentage, const int numb_rows, const int numb_columns)
{
    int64_t start = 0, end = 0;
    int r;

    matrix_t matrix;

    matrix.numb_rows = numb_rows;
    matrix.numb_columns = numb_columns;

    r = create_ordinary_matrix(&matrix);

    if (r)
        return r;

    r = random_fill_ord_matrix(&matrix, fill_percentage);

    if (r == ZERO_MATRIX)
    {
        free_matrix(matrix.matrix, matrix.numb_rows);
        return SUCCESS;
    }

    matrix_t vector;

    vector.numb_rows = matrix.numb_columns;
    vector.numb_columns = 1;

    r = create_ordinary_matrix(&vector);

    if (r)
    {
        free_matrix(matrix.matrix, matrix.numb_rows);
        return r;
    }

    r = random_fill_ord_matrix(&vector, fill_percentage);

    if (r == ZERO_MATRIX)
    {
        free_matrix(matrix.matrix, matrix.numb_rows);
        free_matrix(vector.matrix, vector.numb_rows);
        return SUCCESS;
    }

    matrix_t res_matrix;

    res_matrix.numb_rows = matrix.numb_rows;
    res_matrix.numb_columns = vector.numb_columns;

    r = create_ordinary_matrix(&res_matrix);

    if (r)
    {
        free_matrix(matrix.matrix, matrix.numb_rows);
        free_matrix(vector.matrix, vector.numb_rows);
        return r;
    }

    printf("\nОбычные матрицы (%dx%d и %dx%d)            ",
        matrix.numb_rows, matrix.numb_columns, vector.numb_rows, vector.numb_columns);

    for (int i = 0; i < NUMBER_OF_RUNS; i++)
    {
        start += tick();
        ordinary_matrix_multiplication(&res_matrix, &matrix, &vector);
        end += tick();
    }

    free_matrix(matrix.matrix, matrix.numb_rows);
    free_matrix(vector.matrix, vector.numb_rows);
    free_matrix(res_matrix.matrix, res_matrix.numb_rows);

    print_result(start / NUMBER_OF_RUNS, end / NUMBER_OF_RUNS);
    printf("Затраченная память под массив %dx%d - %lu байт\n\n", 
        matrix.numb_rows, matrix.numb_columns, 
        sizeof(matrix.matrix[0][0]) * matrix.numb_rows * matrix.numb_columns);

    start = 0;
    end = 0;

    special_matrix_t s_matrix;

    s_matrix.numb_rows = numb_rows;
    s_matrix.numb_columns = numb_columns;

    r = find_number_non_zero_elem(&s_matrix, fill_percentage);

    if (r == ZERO_MATRIX)
        return SUCCESS;

    r = create_special_matrix(&s_matrix);

    if (r)
        return r;

    r = random_fill_spec_matrix(&s_matrix);

    if (r == ZERO_MATRIX)
    {
        free_special_matrix(&s_matrix);
        return SUCCESS;
    }

    special_matrix_t s_vector;

    s_vector.numb_rows = s_matrix.numb_columns;
    s_vector.numb_columns = 1;

    r = find_number_non_zero_elem(&s_vector, fill_percentage);

    if (r == ZERO_MATRIX)
    {
        free_special_matrix(&s_matrix);
        return SUCCESS;
    }

    r = create_special_matrix(&s_vector);

    if (r)
    {
        free_special_matrix(&s_matrix);
        return r;
    }

    r = random_fill_spec_matrix(&s_matrix);

    if (r == ZERO_MATRIX)
    {
        free_special_matrix(&s_matrix);
        free_special_matrix(&s_vector);
        return SUCCESS;
    }

    special_matrix_t s_res_matrix;

    s_res_matrix.numb_rows = s_matrix.numb_rows;
    s_res_matrix.numb_columns = s_vector.numb_columns;
    s_res_matrix.numb_non_zero_elem = s_res_matrix.numb_rows * s_res_matrix.numb_columns;

    r = create_special_matrix(&s_res_matrix);

    if (r)
    {
        free_special_matrix(&s_matrix);
        free_special_matrix(&s_vector);
        return r;
    }

    printf("Матрицы в особой форме (%dx%d и %dx%d)     ",
        s_matrix.numb_rows, s_matrix.numb_columns, s_vector.numb_rows, s_vector.numb_columns);

    for (int i = 0; i < NUMBER_OF_RUNS; i++)
    {
        start += tick();

        r = special_matrix_multiplication(&s_res_matrix, &s_matrix, &s_vector);

        if (r)
        {
            free_special_matrix(&s_matrix);
            free_special_matrix(&s_vector);
            free_special_matrix(&s_res_matrix);
            return r;
        }

        end += tick();
    }

    free_special_matrix(&s_matrix);
    free_special_matrix(&s_vector);
    free_special_matrix(&s_res_matrix);

    print_result(start / NUMBER_OF_RUNS, end / NUMBER_OF_RUNS);
    printf("Затраченная память под массив %dx%d - %lu байт\n\n", 
        s_matrix.numb_rows, s_matrix.numb_columns, 
        sizeof(s_matrix.vector_a[0]) * s_matrix.numb_non_zero_elem + 
        sizeof(s_matrix.vector_ja[0]) * s_matrix.numb_non_zero_elem + 
        sizeof(s_matrix.linked_list[0]) * (s_matrix.numb_rows + 1));

    return SUCCESS;
}

int comparison_time_memory(void)
{
    int r;

    printf("                                "
           "Матрицы заполнены на %d%%\n", FILL_PERCENTAGE_1);

    r = comparison(FILL_PERCENTAGE_1, NUMBER_ROWS_1, NUMBER_COLUMNS_1);

    if (r)
        return r;

    r = comparison(FILL_PERCENTAGE_1, NUMBER_ROWS_2, NUMBER_COLUMNS_2);

    if (r)
        return r;

    r = comparison(FILL_PERCENTAGE_1, NUMBER_ROWS_3, NUMBER_COLUMNS_3);

    if (r)
        return r;

    printf("                                "
           "Матрицы заполнены на %d%%\n", FILL_PERCENTAGE_2);

    r = comparison(FILL_PERCENTAGE_2, NUMBER_ROWS_1, NUMBER_COLUMNS_1);

    if (r)
        return r;

    r = comparison(FILL_PERCENTAGE_2, NUMBER_ROWS_2, NUMBER_COLUMNS_2);

    if (r)
        return r;

    r = comparison(FILL_PERCENTAGE_2, NUMBER_ROWS_3, NUMBER_COLUMNS_3);

    if (r)
        return r;

    printf("                                "
           "Матрицы заполнены на %d%%\n", FILL_PERCENTAGE_3);

    r = comparison(FILL_PERCENTAGE_3, NUMBER_ROWS_1, NUMBER_COLUMNS_1);

    if (r)
        return r;

    r = comparison(FILL_PERCENTAGE_3, NUMBER_ROWS_2, NUMBER_COLUMNS_2);

    if (r)
        return r;

    r = comparison(FILL_PERCENTAGE_3, NUMBER_ROWS_3, NUMBER_COLUMNS_3);

    if (r)
        return r;

    printf("                                "
           "Матрицы заполнены на %d%%\n", FILL_PERCENTAGE_4);

    r = comparison(FILL_PERCENTAGE_4, NUMBER_ROWS_1, NUMBER_COLUMNS_1);

    if (r)
        return r;

    r = comparison(FILL_PERCENTAGE_4, NUMBER_ROWS_2, NUMBER_COLUMNS_2);

    if (r)
        return r;

    r = comparison(FILL_PERCENTAGE_4, NUMBER_ROWS_3, NUMBER_COLUMNS_3);

    if (r)
        return r;

    printf("                                "
           "Матрицы заполнены на %d%%\n", FILL_PERCENTAGE_5);

    r = comparison(FILL_PERCENTAGE_5, NUMBER_ROWS_1, NUMBER_COLUMNS_1);

    if (r)
        return r;

    r = comparison(FILL_PERCENTAGE_5, NUMBER_ROWS_2, NUMBER_COLUMNS_2);

    if (r)
        return r;

    r = comparison(FILL_PERCENTAGE_5, NUMBER_ROWS_3, NUMBER_COLUMNS_3);

    if (r)
        return r;

    
    return SUCCESS;
}

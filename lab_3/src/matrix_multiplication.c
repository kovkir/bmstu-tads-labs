#include "../inc/matrix_multiplication.h"

void ordinary_matrix_multiplication(matrix_t *const res_matrix,
matrix_t *const matrix_a, matrix_t *const matrix_b)
{
    for (int i = 0; i < res_matrix->numb_rows; i++)
    {
        for (int j = 0; j < res_matrix->numb_columns; j++)
        {
            res_matrix->matrix[i][j] = find_matrix_element(matrix_a, matrix_b, i, j);
        }
    }
}

int ordinary_multiplication(void)
{
    matrix_t matrix;
    int r;

    r = read_rows_and_columns_of_matrix(&matrix.numb_rows, &matrix.numb_columns);

    if (r)
        return r;
        
    r = create_ordinary_matrix(&matrix);

    if (r)
        return r;

    int input_method, fill_percentage = 0;

    r = read_ord_matrix_input_method(&input_method, &fill_percentage);

    if (r)
    {
        free_matrix(matrix.matrix, matrix.numb_rows);
        return r;
    }

    if (input_method == 1)
    {
        r = read_whole_matrix(&matrix);

        if (r)
        {
            free_matrix(matrix.matrix, matrix.numb_rows);
            return r;
        }
    }
    else if (input_method == 2)
    {
        r = read_non_zero_elem_of_matrix(&matrix);

        if (r)
        {
            free_matrix(matrix.matrix, matrix.numb_rows);
            return r;
        }
    }
    else
    {
        r = random_fill_ord_matrix(&matrix, fill_percentage);

        if (r == ZERO_MATRIX)
        {
            free_matrix(matrix.matrix, matrix.numb_rows);
            return SUCCESS;
        }
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

    if (input_method == 1)
    {
        r = read_whole_matrix(&vector);

        if (r)
        {
            free_matrix(matrix.matrix, matrix.numb_rows);
            free_matrix(vector.matrix, vector.numb_rows);
            return r;
        }
    }
    else if (input_method == 2)
    {
        r = read_non_zero_elem_of_matrix(&vector);

        if (r)
        {
            free_matrix(matrix.matrix, matrix.numb_rows);
            free_matrix(vector.matrix, vector.numb_rows);
            return r;
        }
    }
    else
    {
        r = random_fill_ord_matrix(&vector, fill_percentage);

        if (r == ZERO_MATRIX)
        {
            free_matrix(matrix.matrix, matrix.numb_rows);
            free_matrix(vector.matrix, vector.numb_rows);
            return SUCCESS;
        }
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

    ordinary_matrix_multiplication(&res_matrix, &matrix, &vector);

    printf("\nИсходная матрица (размером %dx%d):\n",
        matrix.numb_rows, matrix.numb_columns);
    print_ordinary_matrix(&matrix);
    printf("Вектор (размером %dx%d):\n",
        vector.numb_rows, vector.numb_columns);
    print_ordinary_matrix(&vector);
    printf("Результат перемножения двух матриц (матрица %dx%d):\n",
        res_matrix.numb_rows, res_matrix.numb_columns);
    print_ordinary_matrix(&res_matrix);

    free_matrix(matrix.matrix, matrix.numb_rows);
    free_matrix(vector.matrix, vector.numb_rows);
    free_matrix(res_matrix.matrix, res_matrix.numb_rows);

    return SUCCESS;
}

int special_matrix_multiplication(special_matrix_t *const res_matrix,
special_matrix_t *const matrix_a, special_matrix_t *const matrix_b)
{
    int res_matrix_elem, numb_non_zero_elem = 0;

    for (int i = 0, j = 0; i < matrix_a->numb_rows; i++)
    {
        if (matrix_a->linked_list[i + 1] == matrix_a->linked_list[i])
            continue;
        
        res_matrix_elem = 0;

        int k = matrix_a->linked_list[i];

        while (k < matrix_a->linked_list[i + 1])
        {
            if (matrix_b->linked_list[matrix_a->vector_ja[j] - 1] ==
            matrix_b->linked_list[matrix_a->vector_ja[j]])
            {   
                j++;
                k++;
                continue;
            }

            res_matrix_elem += matrix_a->vector_a[j] * 
            matrix_b->vector_a[matrix_b->linked_list[matrix_a->vector_ja[j] - 1] - 1];
            LOG_DEBUG("res_matrix_elem = %d", res_matrix_elem);
            j++;
            k++;
        }

        if (res_matrix_elem != 0)
        {
            res_matrix->vector_a[numb_non_zero_elem] = res_matrix_elem;
            res_matrix->linked_list[numb_non_zero_elem] = numb_non_zero_elem + 1;
            res_matrix->vector_ja[numb_non_zero_elem] = 1;
            numb_non_zero_elem++;
        }
    }

    res_matrix->numb_non_zero_elem = numb_non_zero_elem;

    int r = convert_linked_list(res_matrix);

    if (r)
        return r;

    int *p = realloc(res_matrix->vector_a, res_matrix->numb_non_zero_elem * sizeof(int));

    if (!p)
        return FAILED_TO_ALLOCATE_MEMORY;

    res_matrix->vector_a = p;

    p = realloc(res_matrix->vector_ja, res_matrix->numb_non_zero_elem * sizeof(int));

    if (!p)
        return FAILED_TO_ALLOCATE_MEMORY;

    res_matrix->vector_ja = p;

    p = realloc(res_matrix->linked_list, (res_matrix->numb_rows + 1) * sizeof(int));

    if (!p)
        return FAILED_TO_ALLOCATE_MEMORY;

    res_matrix->linked_list = p;
    
    return SUCCESS;
}

int special_multiplication(void)
{
    special_matrix_t matrix;
    int r;

    r = read_rows_and_columns_of_matrix(&matrix.numb_rows, &matrix.numb_columns);

    if (r)
        return r;
    
    int input_method, fill_percentage = 0;

    r = read_spec_matrix_input_method(&input_method, &fill_percentage);

    if (r)
        return r;

    if (input_method == 1)
    {   
        r = read_number_non_zero_elem(&matrix);

        if (r)
            return r;

        r = create_special_matrix(&matrix);

        if (r)
            return r;

        r = read_special_matrix(&matrix);

        if (r)
        {
            free_special_matrix(&matrix);
            return r;
        }
    }
    else
    {
        r = find_number_non_zero_elem(&matrix, fill_percentage);

        if (r == ZERO_MATRIX)
            return SUCCESS;

        r = create_special_matrix(&matrix);

        if (r)
            return r;

        r = random_fill_spec_matrix(&matrix);

        if (r)
        {
            free_special_matrix(&matrix);
            return r;
        }
    }

    special_matrix_t vector;

    vector.numb_rows = matrix.numb_columns;
    vector.numb_columns = 1;

    if (input_method == 1)
    {   
        r = read_number_non_zero_elem(&vector);

        if (r)
        {
            free_special_matrix(&matrix);
            return r;
        }

        r = create_special_matrix(&vector);

        if (r)
        {
            free_special_matrix(&matrix);
            return r;
        }

        r = read_special_matrix(&vector);

        if (r)
        {
            free_special_matrix(&matrix);
            free_special_matrix(&vector);
            return r;
        }
    }
    else
    {
        r = find_number_non_zero_elem(&vector, fill_percentage);

        if (r == ZERO_MATRIX)
        {
            free_special_matrix(&matrix);
            return SUCCESS;
        }

        r = create_special_matrix(&vector);

        if (r)
        {
            free_special_matrix(&matrix);
            return r;
        }

        r = random_fill_spec_matrix(&vector);

        if (r)
        {
            free_special_matrix(&matrix);
            free_special_matrix(&vector);
            return r;
        }
    }

    special_matrix_t res_matrix;

    res_matrix.numb_rows = matrix.numb_rows;
    res_matrix.numb_columns = vector.numb_columns;
    res_matrix.numb_non_zero_elem = res_matrix.numb_rows * res_matrix.numb_columns;

    r = create_special_matrix(&res_matrix);

    if (r)
    {
        free_special_matrix(&matrix);
        free_special_matrix(&vector);
        return r;
    }

    r = special_matrix_multiplication(&res_matrix, &matrix, &vector);

    if (r)
    {
        free_special_matrix(&matrix);
        free_special_matrix(&vector);
        free_special_matrix(&res_matrix);
        return r;
    }

    printf("        Исходная матрица (размером %dx%d):\n",
            matrix.numb_rows, matrix.numb_columns);
    print_special_matrix(&matrix);
    printf("        Вектор (размером %dx%d):\n",
            vector.numb_rows, vector.numb_columns);
    print_special_matrix(&vector);
    printf("        Результат перемножения двух матриц (матрица %dx%d):\n",
            res_matrix.numb_rows, res_matrix.numb_columns);
    print_special_matrix(&res_matrix);

    free_special_matrix(&matrix);
    free_special_matrix(&vector);
    free_special_matrix(&res_matrix);

    return SUCCESS;
}

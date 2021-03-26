#include "../inc/alloc_free_memory.h"

void free_matrix(int **data, int n)
{
    for (int i = 0; i < n; i++)
        free(data[i]);

    free(data);
}

int **allocate_matrix(int n, int m)
{
    int **data = calloc(n, sizeof(int*));

    if (!data)
        return NULL;

    for (int i = 0; i < n; i++)
    {
        data[i] = calloc(m * sizeof(int), sizeof(int));

        if (!data[i])
        {
            free_matrix(data, n);
            return NULL;
        }
    }
    return data;
}

int create_ordinary_matrix(matrix_t *matrix)
{   
    matrix->matrix = allocate_matrix(matrix->numb_rows, matrix->numb_columns);

    if (matrix->matrix == NULL)
    {
        printf("Не удалось выделить память мод матрицу\n");
        return FAILED_TO_ALLOCATE_MEMORY;
    }

    return SUCCESS;
}

int create_special_matrix(special_matrix_t *matrix)
{
    matrix->vector_a = calloc(matrix->numb_non_zero_elem * sizeof(int), sizeof(int));

    if (matrix->vector_a == NULL)
    {
        printf("Не удалось выделить память мод массив ненулевых элементов\n");
        return FAILED_TO_ALLOCATE_MEMORY;
    }

    matrix->vector_ja = calloc(matrix->numb_non_zero_elem * sizeof(int), sizeof(int));

    if (matrix->vector_ja == NULL)
    {
        printf("Не удалось выделить память мод массив, "
               "содержащий номера столбцов ненулевых элементов\n");
        free(matrix->vector_a);
        return FAILED_TO_ALLOCATE_MEMORY;
    }

    matrix->linked_list = 
    calloc((MAX(matrix->numb_rows, matrix->numb_non_zero_elem)+ 1) * sizeof(int), sizeof(int));

    if (matrix->linked_list == NULL)
    {
        printf("Не удалось выделить память под связный список\n");
        free(matrix->vector_a);
        free(matrix->vector_ja);
        return FAILED_TO_ALLOCATE_MEMORY;
    }

    return SUCCESS;
}

void free_special_matrix(special_matrix_t *matrix)
{
    free(matrix->vector_a);
    free(matrix->vector_ja);
    free(matrix->linked_list);
}

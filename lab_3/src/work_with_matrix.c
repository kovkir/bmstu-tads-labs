#include "../inc/work_with_matrix.h"

int convert_linked_list(special_matrix_t *matrix)
{   
    int *array = calloc((matrix->numb_non_zero_elem + 1) * sizeof(int), sizeof(int));

    if (!array)
        return ERROR_CONVERT_LINKED_LIST; 
    
    for (int i = 0; i < matrix->numb_non_zero_elem; i++)
    {
        array[i] = matrix->linked_list[i];
    }
    
    array[matrix->numb_non_zero_elem] = matrix->numb_rows + 1;

    for (int i = 0, j = 0; i < matrix->numb_rows; i++)
    {
        if (array[j] == i + 1)
        {
            matrix->linked_list[i] = array[j];

            do
            {
                j++;
            } while (array[j] == array[j - 1]);
        }
        else
        {
            matrix->linked_list[i] = 0;
        }
    }

    for (int i = 0; i < matrix->numb_rows; i++)
    {   
        if (matrix->linked_list[i] == 0)
            continue;
            
        for (int j = 0; j < matrix->numb_non_zero_elem; j++)
        {
            if (array[j] == matrix->linked_list[i])
            {
                matrix->linked_list[i] = j + 1;
                break;
            }
        }
    }

    matrix->linked_list[matrix->numb_rows] = matrix->numb_non_zero_elem + 1;

    for (int i = matrix->numb_rows - 1; i >= 0; i--)
    {
        if (matrix->linked_list[i] == 0)
            matrix->linked_list[i] = matrix->linked_list[i + 1];
    }

    free(array);

    return SUCCESS;
}

void sort(special_matrix_t *matrix)
{   
    int i_min, c;

    for (int i = 0; i < matrix->numb_non_zero_elem - 1; i++)
    {   
        i_min = i;

        for (int j = i + 1; j < matrix->numb_non_zero_elem; j++)
        {
            if (matrix->linked_list[j] < matrix->linked_list[i_min])
            {
                i_min = j;
            }
            else if (matrix->linked_list[j] == matrix->linked_list[i_min] &&
                matrix->vector_ja[j] < matrix->vector_ja[i_min])
            {
                i_min = j;
            }
        }

        c = matrix->vector_a[i_min];
        matrix->vector_a[i_min] = matrix->vector_a[i];
        matrix->vector_a[i] = c;

        c = matrix->vector_ja[i_min];
        matrix->vector_ja[i_min] = matrix->vector_ja[i];
        matrix->vector_ja[i] = c;

        c = matrix->linked_list[i_min];
        matrix->linked_list[i_min] = matrix->linked_list[i];
        matrix->linked_list[i] = c;
    }
}

int find_matrix_element(matrix_t *const matrix_a, matrix_t *const matrix_b,
const int i, const int j)
{
    int new_matr_elem = 0;

    for (int u = 0; u < matrix_a->numb_columns; u++)
    {
        new_matr_elem += matrix_a->matrix[i][u] * matrix_b->matrix[u][j];
    }

    return new_matr_elem;
}

int find_number_non_zero_elem(special_matrix_t *matrix, const int fill_percentage)
{
    matrix->numb_non_zero_elem = matrix->numb_rows * matrix->numb_columns * fill_percentage / 100;

    if (matrix->numb_non_zero_elem == 0)
    {
        printf("Все элементы итоговой матрицы (размером %dx1) равны 0\n", matrix->numb_rows);
        return ZERO_MATRIX;
    }

    return SUCCESS;
}

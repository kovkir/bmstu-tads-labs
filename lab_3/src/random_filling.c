#include "../inc/random_filling.h"

int random_fill_ord_matrix(matrix_t *matrix, const int fill_percentage)
{
    for (int i = 0; i < matrix->numb_rows; i++)
        for (int j = 0; j < matrix->numb_columns; j++)
            matrix->matrix[i][j] = 0;

    int numb_of_filled_elem;

    numb_of_filled_elem = matrix->numb_rows * matrix->numb_columns * fill_percentage / 100; 

    if (numb_of_filled_elem == 0)
    {
        printf("Все элементы итоговой матрицы (размером %dx1) равны 0\n", matrix->numb_rows);
        return ZERO_MATRIX;
    }

    int k = numb_of_filled_elem;

    srand(time(NULL));

    for (int i = 0; i < matrix->numb_rows; i++)
    {
        for (int j = 0; j < matrix->numb_columns; j++)
        {
            if (k-- > 0)
            {   
                while(!(matrix->matrix[i][j] = 
                MIN_BORDER + rand() % (MAX_BORDER - MIN_BORDER + 1)));
            }
            else
            {
                matrix->matrix[i][j] = 0;
            }
        }
    }

    int new_i, new_j, c;

    for (int i = 0; i < matrix->numb_rows; i++)
    {
        for (int j = 0; j < matrix->numb_columns; j++)
        {
            if (numb_of_filled_elem-- > 0)
            {
                new_i = 1 + rand() % matrix->numb_rows;
                new_j = 1 + rand() % matrix->numb_columns;
                
                c = matrix->matrix[new_i - 1][new_j - 1];
                matrix->matrix[new_i - 1][new_j - 1] = matrix->matrix[i][j];
                matrix->matrix[i][j] = c;
            }
            else
            {
                return SUCCESS;
            }
        }
    }

    return SUCCESS;
}

int random_fill_spec_matrix(special_matrix_t *matrix)
{
    srand(time(NULL));

    for (int i = 0; i < matrix->numb_non_zero_elem; i++)
    { 
        while(!(matrix->vector_a[i] = MIN_BORDER + rand() % (MAX_BORDER - MIN_BORDER + 1)));
    }

    int k = matrix->numb_non_zero_elem;

    for (int i = 0; i < matrix->numb_rows; i++)
    {
        for (int j = 0; j < matrix->numb_columns; j++)
        {
            if (k > 0)
            {
                matrix->linked_list[i * matrix->numb_columns + j] = i + 1;
                matrix->vector_ja[i * matrix->numb_columns + j] = j + 1;
                k--;
            }
            else
                break;
        }
    }
    
    int new_i, new_j;

    for (int i = 0; i < matrix->numb_non_zero_elem; i++)
    {
        new_i = 1 + rand() % matrix->numb_rows;
        new_j = 1 + rand() % matrix->numb_columns;

        for (int j = 0; j < matrix->numb_non_zero_elem; j++)
        {
            if (matrix->linked_list[j] == new_i &&
                matrix->vector_ja[j] == new_j)
            {
                break;
            }

            if (j == matrix->numb_non_zero_elem - 1)
            {
                matrix->linked_list[i] = new_i;
                matrix->vector_ja[i] = new_j;
            }
        }
    }

    sort(matrix);

    int r = convert_linked_list(matrix);

    if (r)
        return r;

    return SUCCESS;
}

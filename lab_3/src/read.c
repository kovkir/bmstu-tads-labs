#include "../inc/read.h"

int read_number_action(int *number_action)
{
    int r;
    
    printf("Введите номер команды: ");
    r = scanf("%d", number_action);
    printf("\n");
    
    if (r != 1 )
    {
        printf("Не удалось прочитать номер команды\n");
        return FAILED_TO_READ_COMMAND_NUMBER;
    }
    
    if ( *number_action < MIN_COMMAND_NUMBER || *number_action > MAX_COMMAND_NUMBER)
    {
        printf("Номер команды должен быть >= %d и <= %d\n",
        MIN_COMMAND_NUMBER, MAX_COMMAND_NUMBER);

        return WRONG_COMMAND_NUMBER;
    }
    
    return SUCCESS;
}

int read_rows_and_columns_of_matrix(int *number_rows, int *number_columns)
{
    int r;

    printf("Введите размер изначальной матрицы (кол-во строк и столбцов через пробел)\n"
        "Максимальный размер матрицы - %dx%d\n", MAX_MATRIX_SIZE, MAX_MATRIX_SIZE);

    r = scanf("%d", number_rows);

    if (r != 1)
    {
        printf("Не удалось прочитать кол-во строк матрицы\n");
        return ERROR_NUMBER_ROWS;
    }
    else if (*number_rows > MAX_MATRIX_SIZE)
    {
        printf("Превышено максимальное кол-во строк матрицы\n");
        return ERROR_NUMBER_ROWS;
    }
    else if (*number_rows <= 0)
    {
        printf("Кол-во строк матрицы должно быть больше 0\n");
        return ERROR_NUMBER_ROWS;
    }

    r = scanf("%d", number_columns);

    if (r != 1)
    {
        printf("Не удалось прочитать кол-во столбцов матрицы\n");
        return ERROR_NUMBER_COLUMNS;
    }
    else if (*number_columns > MAX_MATRIX_SIZE)
    {
        printf("Превышено максимальное кол-во столбцов матрицы\n");
        return ERROR_NUMBER_COLUMNS;
    }
    else if (*number_columns <= 0)
    {
        printf("Кол-во столбцов матрицы должно быть больше 0\n");
        return ERROR_NUMBER_ROWS;
    }

    return SUCCESS;
}

int read_ord_matrix_input_method(int *input_method, int *fill_percentage)
{   
    printf("Введите 1, если хотите заполнить ВСЮ матрицу вручную;\n"
           "Введите 2, если хотите заполнить ненулевые элементы вручную;\n"
           "Введите 3 для автозаполнения.\n");

    int r = scanf("%d", input_method);

    if (r != 1)
    {
        printf("Не удалось прочитать метод заполнения матрицы\n");
        return ERROR_INPUT_METHOD;
    }
    else if (*input_method < 1 || *input_method > 3)
    {
        printf("Метод заполнения матрицы - число от 1 до 3\n");
        return ERROR_INPUT_METHOD;
    }

    if (*input_method == 3)
    {
        printf("Введите процент заполнения матрицы\n");

        r = scanf("%d", fill_percentage);

        if (r != 1)
        {
            printf("Не удалось прочитать процент заполнения матрицы\n");
            return ERROR_FILL_PERCENTAGE;
        }
        else if (*fill_percentage > 100 || *fill_percentage <= 0)
        {
            printf("Процент заполнения матрицы - число от 1 до 100\n");
            return ERROR_FILL_PERCENTAGE;
        }
    }

    return SUCCESS;
}

int read_spec_matrix_input_method(int *input_method, int *fill_percentage)
{   
    printf("Введите 1, если хотите заполнить матрицу вручную;\n"
           "Введите 2 для автозаполнения.\n");

    int r = scanf("%d", input_method);

    if (r != 1)
    {
        printf("Не удалось прочитать метод заполнения матрицы\n");
        return ERROR_INPUT_METHOD;
    }
    else if (*input_method < 1 || *input_method > 2)
    {
        printf("Метод заполнения матрицы - число от 1 до 2\n");
        return ERROR_INPUT_METHOD;
    }

    if (*input_method == 2)
    {
        printf("Введите процент заполнения матрицы\n");

        r = scanf("%d", fill_percentage);

        if (r != 1)
        {
            printf("Не удалось прочитать процент заполнения матрицы\n");
            return ERROR_FILL_PERCENTAGE;
        }
        else if (*fill_percentage > 100 || *fill_percentage <= 0)
        {
            printf("Процент заполнения матрицы - число от 1 до 100\n");
            return ERROR_FILL_PERCENTAGE;
        }
    }

    return SUCCESS;
}

int read_whole_matrix(matrix_t *const matrix)
{
    int r;

    printf("Заполните матрицу размером %dx%d\n", matrix->numb_rows, matrix->numb_columns);

    for (int i = 0; i < matrix->numb_rows; i++) 
    {
        for (int j = 0; j < matrix->numb_columns; j++) 
        {
            r = scanf("%d", (matrix->matrix)[i] + j);

            if (r != 1)
            {   
                printf("Не удалось прочитать элемент матрицы\n");
                return MATRIX_READ_ERROR;
            }
        }
    }

    return SUCCESS;
}

int read_non_zero_elem_of_matrix(matrix_t *const matrix)
{
    int r, numb_non_zero_elem;

    printf("Введите кол-во ненулевых элементов матрицы "
           "(число от 1 до %d)\n", matrix->numb_rows * matrix->numb_columns);

    r = scanf("%d", &numb_non_zero_elem);

    if (r != 1)
    {
        printf("Не удалось прочитать кол-во ненулевых элементов матрицы\n");
        return ERROR_NUMBER_NON_ZERO_ELEM;
    }
    else if (numb_non_zero_elem <= 0 || 
             numb_non_zero_elem > matrix->numb_rows * matrix->numb_columns)
    {
        printf("Кол-во ненулевых элементов матрицы - число от 1 до %d\n",
        matrix->numb_rows * matrix->numb_columns);

        return ERROR_NUMBER_NON_ZERO_ELEM;
    }

    printf("Заполните матрицу (размером %dx%d), содержащую %d ненулевых элементов.\n"
           "На каждой строке (для каждого элемента) через пробел должны идти:\n"
           "    - сам ненулевой элемент;\n"
           "    - номер строки матрицы, в которой он расположен;\n"
           "    - номер столбца матрицы, в котором он расположен;\n",
           matrix->numb_rows, matrix->numb_columns, numb_non_zero_elem);

    int matrix_elem, i_elem, j_elem;

    for (int i = 0; i < numb_non_zero_elem; i++)
    {
        r = scanf("%d", &matrix_elem);

        if (r != 1)
        {   
            printf("Не удалось прочитать элемент матрицы\n");
            return MATRIX_READ_ERROR;
        }

        r = scanf("%d", &i_elem);

        if (r != 1)
        {   
            printf("Не удалось прочитать номер строки элемента матрицы\n");
            return ROW_NUMBER_READ_ERROR;
        }
        else if (i_elem < 1 || i_elem > matrix->numb_rows)
        {
            printf("Номер строки матрицы - число от 1 до %d\n", matrix->numb_rows);
            return ROW_NUMBER_READ_ERROR;
        }
        
        r = scanf("%d", &j_elem);
    
        if (r != 1)
        {   
            printf("Не удалось прочитать номер столбца элемента матрицы\n");
            return COLUMN_NUMBER_READ_ERROR;
        }
        else if(j_elem < 1 || j_elem > matrix->numb_columns)
        {
            printf("Номер столбца матрицы - число от 1 до %d\n", matrix->numb_columns);
            return COLUMN_NUMBER_READ_ERROR;
        }

        matrix->matrix[i_elem - 1][j_elem - 1] = matrix_elem;
    }

    return SUCCESS;
}

int read_number_non_zero_elem(special_matrix_t *matrix)
{
    printf("Введите кол-во ненулевых элементов матрицы "
           "(число от 1 до %d)\n", matrix->numb_rows * matrix->numb_columns);

    int r = scanf("%d", &matrix->numb_non_zero_elem);

    if (r != 1)
    {
        printf("Не удалось прочитать кол-во ненулевых элементов матрицы\n");
        return ERROR_NUMBER_NON_ZERO_ELEM;
    }
    else if (matrix->numb_non_zero_elem < 0 || 
             matrix->numb_non_zero_elem > matrix->numb_rows * matrix->numb_columns)
    {
        printf("Кол-во ненулевых элементов матрицы - число от 0 до %d\n",
        matrix->numb_rows * matrix->numb_columns);

        return ERROR_NUMBER_NON_ZERO_ELEM;
    }
    
    return SUCCESS;
}

int read_vector_a_elem(special_matrix_t *matrix, const int i)
{
    int r = scanf("%d", matrix->vector_a + i);
    
    if (r != 1)
    {   
        printf("Не удалось прочитать элемент матрицы\n");
        return VECTOR_A_ELEM_READ_ERROR;
    }

    return SUCCESS;
}

int read_vector_ja_elem(special_matrix_t *matrix, const int i)
{
    int r = scanf("%d", matrix->vector_ja + i);
    
    if (r != 1)
    {   
        printf("Не удалось прочитать номер столбца элемента матрицы\n");
        return VECTOR_JA_ELEM_READ_ERROR;
    }
    else if(matrix->vector_ja[i] < 1 || matrix->vector_ja[i] > matrix->numb_columns)
    {
        printf("Номер столбца матрицы - число от 1 до %d\n", matrix->numb_columns);
        return VECTOR_JA_ELEM_READ_ERROR;
    }

    return SUCCESS;
}

int read_linked_list_elem(special_matrix_t *matrix, const int i)
{
    int r = scanf("%d", matrix->linked_list + i);

    if (r != 1)
    {   
        printf("Не удалось прочитать номер строки элемента матрицы\n");
        return LINKED_LIST_ELEM_READ_ERROR;
    }
    else if (matrix->linked_list[i] < 1 || matrix->linked_list[i] > matrix->numb_rows)
    {
        printf("Номер строки матрицы - число от 1 до %d\n", matrix->numb_rows);
        return LINKED_LIST_ELEM_READ_ERROR;
    }

    for (int j = 0; j < i; j++)
    {
        if (matrix->vector_ja[j] == matrix->vector_ja[i] &&
            matrix->linked_list[j] == matrix->linked_list[i])
        {
            printf("Этот элемент уже задан\n");
            return LINKED_LIST_ELEM_READ_ERROR;
        }
    }

    return SUCCESS;
}

int read_special_matrix(special_matrix_t *matrix)
{
    printf("Заполните матрицу (размером %dx%d), хранящуюся в особой форме и "
           "содержащую %d ненулевых элементов.\n"
           "На каждой строке (для каждого элемента) через пробел должны идти:\n"
           "    - сам ненулевой элемент;\n"
           "    - номер строки матрицы, в которой он расположен;\n"
           "    - номер столбца матрицы, в котором он расположен;\n",
           matrix->numb_rows, matrix->numb_columns, matrix->numb_non_zero_elem);

    int r;

    for (int i = 0; i < matrix->numb_non_zero_elem; i++)
    {
        r = read_vector_a_elem(matrix, i);

        if (r)
            return r;
        
        r = read_linked_list_elem(matrix, i);

        if (r)
            return r;
        
        r = read_vector_ja_elem(matrix, i);

        if (r)
            return r;
    }

    sort(matrix);
   
    r = convert_linked_list(matrix);

    if (r)
        return r;

    return SUCCESS;
}

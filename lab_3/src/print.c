#include "../inc/print.h"

void print_menu(void)
{
    printf("\n"
        "1. Смоделировать операцию умножения матрицы и вектора-столбца,\n"
        "   хранящихся в особой форме, с получением результата в той же форме.\n"
        "2. Произвести операцию умножения, "
        "применяя стандартный алгоритм работы с матрицами.\n"
        "3. Сравнить время выполнения операций и объем памяти при использовании\n"
        "   этих 2-х алгоритмов при различном проценте заполнения матриц.\n"
        "0. Выйти из программы.\n\n"
        "Особая форма:\n"
        "Разреженная матрица хранится в форме 3-х объектов:\n"
        "   - вектор A содержит значения ненулевых элементов;\n"
        "   - вектор JA содержит номера столбцов для элементов вектора A;\n"
        "   - связный список IA, в элементе Nk которого находится номер компонент\n"
        "     в A и JA, с которых начинается описание строки Nk матрицы A.\n\n");
}

void print_ordinary_matrix(matrix_t *matrix)
{
    for (int i = 0; i < matrix->numb_rows; i++) 
    {
        for (int j = 0; j < matrix->numb_columns; j++) 
        {
            printf("%-5d", matrix->matrix[i][j]);
        }

        printf("\n\n");
    }
}

void print_special_matrix(special_matrix_t *matrix)
{
    printf("\nМассив из ненулевых элементов матрицы:\n");
    
    for (int i = 0; i < matrix->numb_non_zero_elem; i++)
    {
        printf("%d ", matrix->vector_a[i]);
    }
    printf("\n");

    printf("Массив из номеров столбцов ненулевых элементов матрицы:\n");
    
    for (int i = 0; i < matrix->numb_non_zero_elem; i++)
    {
        printf("%d ", matrix->vector_ja[i]);
    }
    printf("\n");
    
    printf("Связный список (элемент маассива - индекс ненулевого элемента матрицы,"
           " с которого начинается строка):\n");

    for (int i = 0; i <= matrix->numb_rows; i++)
    {
        printf("%d ", matrix->linked_list[i]);
    }
    printf("\n\n");
}

void print_result(int64_t start, int64_t end)
{
    printf("      %lld тактов, %.10lf секунд\n", end - start, (double)(end - start)/HZ);  
}
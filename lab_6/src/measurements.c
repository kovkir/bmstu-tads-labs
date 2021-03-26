#include "../inc/measurements.h"

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

void print_result(int64_t start, int64_t end)
{
    printf("%lld тактов, %.10lf секунд\n", end - start, (double)(end - start) / HZ);  
}

int measurements(int buf_size)
{
    printf("\x1B[36m            Размер исходных деревьев, хэш-таблицы и файла - %d"
        " элементов\x1B[0m\n\n", buf_size);

    int64_t start = 0, end = 0;  
    FILE *f;

//                                  Измерение времени в ДДП

    int buf[buf_size + 1];
    int size_buf = buf_size;

    tree_t tree;

    tree.size = 0;
    tree.height = 0;
    tree.root = NULL;

    int number, r;
    vertex_t *prev_elem = NULL;

    for (int i = 0; i < buf_size; i++)
        buf[i] = (i + 1) * STEP;

    r = read_tree(&tree, buf, size_buf);

    if (r)
        return SUCCESS;

    srand(time(NULL));

    for (int i = 0; i < NUMBER_OF_RUNS; i++)
    {
        number = rand() % (buf_size * STEP + 2);

        // printf("\x1B[35m%d\x1B[0m\n", number);

        while (search_elem(number, tree.root, &prev_elem, &tree.total_compare) == YES)
        {
            number = rand() % (buf_size * STEP + 2);
        }
        
        start += tick();

        search_elem(number, tree.root, &prev_elem, &tree.total_compare);

        r = insert_element_into_tree(prev_elem, number, &tree);

        if (r)
        {
            free_tree(tree.root);
            return r;
        }

        end += tick();

        remove_item_from_tree(prev_elem, number, &tree);
    }

    printf("\x1B[33m    Добавление элемента в ДДП\x1B[0m\n\n");
    print_result(start / NUMBER_OF_RUNS, end / NUMBER_OF_RUNS);
    printf("\n");

    start = 0;
    end = 0; 

//                                  Измерение времени в АВЛ-дереве

    f = fopen("test.txt", "w");

    if (!f)
    {
        free_tree(tree.root);
        return FILE_OPENING_ERROR;
    }

    tree_t bal_tree;

    bal_tree.size = 0;
    bal_tree.height = 0;
    bal_tree.root = NULL;

    r = read_balanced_tree(&bal_tree, buf, size_buf);

    if (r)
    {
        free_tree(tree.root);
        return r;
    }

    int empty_cells;

    for (int i = 0; i < NUMBER_OF_RUNS; i++)
    {
        empty_cells = print_tree(bal_tree.root, &bal_tree.height, f);

        if (fseek(f, 0 , SEEK_SET))
        {
            free_tree(tree.root);
            return POINT_OFFSET_ERROR;
        }
        
        number = rand() % (buf_size * STEP + 2);

        while (search_elem(number, bal_tree.root, &prev_elem, &bal_tree.total_compare) == YES)
        {
            number = rand() % (buf_size * STEP + 2);
        }

        r = add_item_to_buffer(buf, &size_buf, number);

        if (r)
        {
            free_tree(tree.root);
            free_tree(bal_tree.root);
            return r;
        }

        start += tick();
        
        search_elem(number, bal_tree.root, &prev_elem, &bal_tree.total_compare);

        if (prev_elem != NULL && 
            (prev_elem->height != bal_tree.height ||
            (prev_elem->height == bal_tree.height && empty_cells == 0)))
        {
            r = insert_element_into_tree(prev_elem, number, &bal_tree);

            if (r)
            {
                free_tree(tree.root);
                free_tree(bal_tree.root);
                return r;
            }

            end += tick();
        }
        else
        {
            r = insert_element_into_tree(prev_elem, number, &bal_tree);

            if (r)
            {
                free_tree(tree.root);
                free_tree(bal_tree.root);
                return r;
            }

            remove_item_from_tree(prev_elem, number, &bal_tree);

            end += tick();

            free_tree(bal_tree.root);
            qsort(buf, size_buf, sizeof(int), comparator);

            bal_tree.size = 0;
            bal_tree.height = 0;
            bal_tree.root = NULL;

            r = read_balanced_tree(&bal_tree, buf, size_buf);

            if (r)
            {
                free_tree(tree.root);
                return r;
            }
        }

        // end += tick();

        search_elem(number, bal_tree.root, &prev_elem, &bal_tree.total_compare);
        remove_item_from_tree(prev_elem, number, &bal_tree);

        remove_item_from_buffer(buf, &size_buf, number);
    }

    printf("\x1B[33m    Добавление элемента в АВЛ-дерево\x1B[0m\n\n");
    print_result(start / NUMBER_OF_RUNS, end / NUMBER_OF_RUNS);
    printf("\n");

    start = 0;
    end = 0;

    if (fclose(f))
    {
        free_tree(tree.root);
        return FILE_CLOSING_ERROR;
    }

//                                  Измерение времени в хеш-таблице

    hash_table_t table;

    table.array = NULL;
    table.size = 0;
    table.elements = 0;
    table.divider = 1;

    int index;

    qsort(buf, size_buf, sizeof(int), comparator);

    r = read_hash_table(&table, buf, size_buf);

    if (r)
    {
        free_tree(tree.root);
        free_tree(bal_tree.root);
        return r;
    }

    for (int i = 0; i < NUMBER_OF_RUNS; i++)
    {
        number = buf_size * STEP + 1 + rand() % (buf_size * STEP);

        start += tick();

        r = add_item_to_table(&table, number);

        if (r)
        {
            free_tree(tree.root);
            free_tree(bal_tree.root);
            free(table.array);
            return r;
        }

        index = search_elem_in_hash_table(&table, number, &table.total_compare);
        
        end += tick();

        remove_item_from_table(&table, number, index);
    }

    printf("\x1B[33m    Добавление элемента в Хеш-таблицу\x1B[0m\n\n");
    print_result(start / NUMBER_OF_RUNS, end / NUMBER_OF_RUNS);
    printf("\n");

//                                  Измерение времени в файле

    number = (buf_size + 1) * STEP;

    for (int i = 0; i < NUMBER_OF_RUNS; i++)
    {
        f = fopen("test.txt", "w");

        if (!f)
            return FILE_OPENING_ERROR;
        
        for (int i = 0; i < buf_size; i++)
            fprintf(f, "%d\n", (i + 1) * STEP);

        if (fclose(f))
            return FILE_CLOSING_ERROR;

        f = fopen("test.txt", "a");

        if (!f)
            return FILE_OPENING_ERROR;

        start += tick();
        fprintf(f, "%d", number);
        end += tick();

        if (fclose(f))
            return FILE_CLOSING_ERROR;
    }

    printf("\x1B[33m    Добавление элемента в файл\x1B[0m\n\n");
    print_result(start / NUMBER_OF_RUNS, end / NUMBER_OF_RUNS);
    printf("\n");

    start = 0;
    end = 0; 

//                                  Измерение среднего кол-ва сравнений

    calculate_number_of_comparisons_in_tree(buf, size_buf, &tree);

    printf("\nСреднее кол-во сравнений для нахождения нужного элемента в ДДП: %.3f\n\n",
        (double) tree.total_compare / tree.size);

    calculate_number_of_comparisons_in_tree(buf, size_buf, &bal_tree);

    printf("Среднее кол-во сравнений для нахождения нужного элемента в АВЛ-дереве: %.3f\n\n",
        (double) bal_tree.total_compare / bal_tree.size);

    calculate_number_of_comparisons(buf, size_buf, &table);

    printf("Среднее кол-во сравнений для нахождения нужного элемента в таблице: %.3f\n\n",
        (double) table.total_compare / table.elements);

    int total_compare_in_file = 0;

    for (int i = 1; i <= size_buf; i++)
        total_compare_in_file += i;

    printf("Среднее кол-во сравнений для нахождения нужного элемента в файле: %.3f\n\n",
        (double) total_compare_in_file / size_buf);

    free_tree(tree.root);
    free_tree(bal_tree.root);
    free(table.array);

    //                              Измерение памяти

    printf("\n\x1B[33m                  Требуемая память для:\x1B[0m\n\n");

    printf("    ДДП - %lu\n\n", sizeof(tree) + sizeof(*tree.root) * tree.size);
    printf("    АВЛ-дерева - %lu\n\n", sizeof(bal_tree) + sizeof(*bal_tree.root) * bal_tree.size);
    printf("    Хеш-таблицы - %lu\n\n", sizeof(table) + sizeof(table.array[0]) * table.elements);

    f = fopen("test.txt", "w");

    if (!f)
        return FILE_OPENING_ERROR;
        
    for (int i = 0; i < buf_size - 1; i++)
        fprintf(f, "%d\n", (i + 1) * STEP);

    fprintf(f, "%d", buf_size * STEP);

    long size_file = ftell(f);

    printf("    Файла - %lu\n\n", size_file);

    return SUCCESS;
}

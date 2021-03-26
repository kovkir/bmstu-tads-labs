#include "../inc/main_actions.h"

int work_with_trees(int *buf, int size_buf)
{
    qsort(buf, size_buf, sizeof(int), comparator);

    tree_t tree;

    tree.size = 0;
    tree.height = 0;
    tree.root = NULL;

    int r = read_tree(&tree, buf, size_buf);

    if (r)
        return r;

    // print_tree_table(tree.root, tree.height);
    print_tree_sideways(tree.root, 1);

    tree_t bal_tree;

    bal_tree.size = 0;
    bal_tree.height = 0;
    bal_tree.root = NULL;

    r = read_balanced_tree(&bal_tree, buf, size_buf);

    if (r)
        return r;

    int empty_cells = print_tree(bal_tree.root, &bal_tree.height, stdout);

    int action, number, fill_in_again;
    vertex_t *prev_elem = NULL;

    while(TRUE)
    {
        print_tree_menu();
        prev_elem = NULL;
        r = read_number_action(&action, 2);

        if (r)
        {
            free_tree(tree.root);
            free_tree(bal_tree.root);
            return r;
        }

        if (action == 1)
        {
            printf("Введите добавляемый элемент: ");
            r = read_number(&number);

            if (r)
            {
                free_tree(tree.root);
                free_tree(bal_tree.root);
                return r;
            }

            if (search_elem(number, tree.root, &prev_elem, &tree.total_compare) == YES)
            {
                printf("\x1B[33mТакой элемент уже существует\x1B[0m\n");
            }
            else
            {
                r = add_item_to_buffer(buf, &size_buf, number);

                if (r)
                {
                    free_tree(tree.root);
                    free_tree(bal_tree.root);
                    return r;
                }

                r = insert_element_into_tree(prev_elem, number, &tree);

                if (r)
                {
                    free_tree(tree.root);
                    free_tree(bal_tree.root);
                    return r;
                }

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
                }
                else
                {
                    free_tree(bal_tree.root);
                    qsort(buf, size_buf, sizeof(int), comparator);

                    bal_tree.size = 0;
                    bal_tree.height = 0;
                    bal_tree.root = NULL;

                    r = read_balanced_tree(&bal_tree, buf, size_buf);

                    if (r)
                        return r;
                }

                // print_tree_table(tree.root, tree.height);
                print_tree_sideways(tree.root, 1);
                empty_cells = print_tree(bal_tree.root, &bal_tree.height, stdout);
            }
        }
        else if (action == 2)
        {
            if (size_buf == 0)
            {
                printf("\x1B[33mДерево пусто\x1B[0m\n");
                continue;
            }

            printf("Введите удаляемый элемент: ");
            r = read_number(&number);

            if (r)
            {
                free_tree(tree.root);
                free_tree(bal_tree.root);
                return r;
            }

            if (search_elem(number, tree.root, &prev_elem, &tree.total_compare) == NO)
            {
                printf("\x1B[33mТакого элемента нет в дереве\x1B[0m\n");
            }
            else
            {
                remove_item_from_buffer(buf, &size_buf, number);
                remove_item_from_tree(prev_elem, number, &tree);

                search_elem(number, bal_tree.root, &prev_elem, &bal_tree.total_compare);
                remove_item_from_tree(prev_elem, number, &bal_tree);
                
                fill_in_again = 0;
                tree_balance_check(bal_tree.root, &fill_in_again, bal_tree.height);

                if (fill_in_again)
                {
                    free_tree(bal_tree.root);
                    qsort(buf, size_buf, sizeof(int), comparator);

                    bal_tree.size = 0;
                    bal_tree.height = 0;
                    bal_tree.root = NULL;

                    r = read_balanced_tree(&bal_tree, buf, size_buf);

                    if (r)
                        return r;
                }

                // print_tree_table(tree.root, tree.height);
                print_tree_sideways(tree.root, 1);
                empty_cells = print_tree(bal_tree.root, &bal_tree.height, stdout);

                // printf("size %d %d\n", tree.size, bal_tree.size);
                // printf("height %d %d\n", tree.height, bal_tree.height);
            }
        }
        else if (action == 0)
        {
            break;
        }
    }

    free_tree(tree.root);
    free_tree(bal_tree.root);

    return SUCCESS;
}

int work_with_hash_table(int *buf, int size_buf)
{
    qsort(buf, size_buf, sizeof(int), comparator);

    hash_table_t table;

    table.array = NULL;
    table.size = 0;
    table.elements = 0;
    table.divider = 1;

    int r = read_hash_table(&table, buf, size_buf);

    if (r)
        return r;

    calculate_number_of_comparisons(buf, size_buf, &table);

    print_hash_table(&table);

    int action, numb_compar, number, index;

    r = read_number_of_comparisons(&numb_compar);

    if (r)
    {
        free(table.array);
        return r;
    }

    while (TRUE)
    {
        print_hash_table_menu();

        r = read_number_action(&action, 2);

        if (r)
        {
            free(table.array);
            return r;
        }

        if (action == 1)
        {
            printf("Введите добавляемое число: ");
            r = read_number(&number);

            if (r)
            {
                free(table.array);
                return r;
            }

            if (search_elem_in_hash_table(&table, number, &table.total_compare) > -1)
            {
                printf("\x1B[33mТакой элемент уже существует\x1B[0m\n");
                continue;
            }

            r = add_item_to_table(&table, number);

            if (r)
            {
                free(table.array);
                return r;
            }

            r = add_item_to_buffer(buf, &size_buf, number);

            if (r)
            {
                free(table.array);
                return r;
            }
        }
        else if (action == 2)
        {
            printf("Введите удаляемое число: ");
            r = read_number(&number);

            if (r)
            {
                free(table.array);
                return r;
            }

            if ((index = search_elem_in_hash_table(&table, number, &table.total_compare)) == -1)
            {
                printf("\x1B[33mТакого элемента нет в хеш-таблице\x1B[0m\n");
                continue;
            }

            remove_item_from_buffer(buf, &size_buf, number);
            remove_item_from_table(&table, number, index);
        }
        else
        {
            break;
        }

        calculate_number_of_comparisons(buf, size_buf, &table);

        if ((double) table.total_compare / table.elements > numb_compar)
        {
            printf("\x1B[35mСреднее кол-во сравнений до реструктуризации - %.3f\x1B[0m\n\n",
                (double) table.total_compare / table.elements);

            free(table.array);
            qsort(buf, size_buf, sizeof(int), comparator);

            table.array = NULL;
            table.size = 0;
            table.elements = 0;
            table.divider = 1;

            int r = read_hash_table(&table, buf, size_buf);

            if (r)
                return r;
            
            calculate_number_of_comparisons(buf, size_buf, &table);
        }

        print_hash_table(&table);
    }
    
    free(table.array);

    return SUCCESS;
}

int add_item_to_file(int *buf, int size_buf, FILE *f)
{
    int number, r;

    for (int i = 0; i < size_buf - 1; i++)
        fprintf(f, "%d\n", buf[i]);

    if (size_buf)
        fprintf(f, "%d", buf[size_buf - 1]);

    printf("Введите добавляемый в файл элемент: ");

    r = read_number(&number);

    if (r)
        return r;

    for (int i = 0; i < size_buf; i++)
    {
        if (buf[i] == number)
        {
            printf("\x1B[36mТакой элемент уже есть в файле\x1B[0m\n");
            return SUCCESS;
        }
    }

    if (size_buf) 
        fprintf(f, "\n");  

    fprintf(f, "%d", number);

    printf("\x1B[32mЭлемент успешно добавлен в файл\x1B[0m\n");

    return SUCCESS;
}

#include "../inc/print.h"

void print_start_menu(void)
{
    printf("\n\x1B[32m"
        "1. Работа с деревьями;\n"
        "2. Работа с хеш-таблицей;\n"
        "3. Добавить элемент в файл;\n"
        "4. Замеры времени и памяти;\n"
        "0. Выйти из программы.\x1B[0m\n\n");
}

void print_tree_menu(void)
{
    printf("\n\x1B[32m"
        "1. Добавить элемент в дерево;\n"
        "2. Удалить элемент из дерева;\n"
        "0. Закончить работу с деревьями.\x1B[0m\n\n");
}

void print_hash_table_menu(void)
{
    printf("\n\x1B[32m"
        "1. Добавить элемент в хеш-таблицу;\n"
        "2. Удалить элемент из хеш-таблицы;\n"
        "0. Закончить работу с хеш-таблицей.\x1B[0m\n\n");
}

int print_tree_level(vertex_t *root, int height, int max_height, int *print_elem, FILE *f)
{
    int empty_cells = 0;
    
    int numb_beg = ((int) pow(2, max_height + 2 - height) - 4) / 2;
    int numb_end = (int) pow(2, max_height + 2 - height) - 4 - numb_beg;

    if (root) 
    {
        if (root->height == height)
        {
            for (int i = 0; i < numb_beg; fprintf(f, " "), i++);
            fprintf(f, "\x1B[36m%3d \x1B[0m", root->number);
            for (int i = 0; i < numb_end; fprintf(f, " "), i++);

            (*print_elem)++;
        }
        else
        {
            empty_cells += print_tree_level(root->left, height, max_height, print_elem, f);

            if (root->left == NULL)
            {
                for (int i = 0; i < numb_beg; fprintf(f, " "), i++);
                fprintf(f, "\x1B[36m%3c \x1B[0m", '.');
                for (int i = 0; i < numb_end; fprintf(f, " "), i++);

                empty_cells++;
            }

            empty_cells += print_tree_level(root->right, height, max_height, print_elem, f);

            if (root->right == NULL)
            {
                for (int i = 0; i < numb_beg; fprintf(f, " "), i++);
                fprintf(f, "\x1B[36m%3c \x1B[0m", '.');
                for (int i = 0; i < numb_end; fprintf(f, " "), i++);

                empty_cells++;
            }
        }
    }
    
    return empty_cells;
}

int print_tree(vertex_t *root, int *max_height, FILE *f)
{
    int empty_cells = 0, print_elem;

    fprintf(f, "\n\x1B[33mАВЛ-дерево\x1B[0m\n\n");

    if (root == NULL)
    {
        fprintf(f, "\x1B[36mДерево пусто\x1B[0m\n");
        return 1;
    }

    for (int i = 0; i <= *max_height; i++)
    {
        print_elem = 0;
        empty_cells += print_tree_level(root, i, *max_height, &print_elem, f);

        fprintf(f, "\n");
    }
    fprintf(f, "\n");

    if (print_elem == 0)
        (*max_height)--;

    return empty_cells;
}

void print_tree_table_level(vertex_t *root, int height, int *print_elem, vertex_t *prev_vertex)
{
    if (root) 
    {
        if (root->height == height)
        {
            if (prev_vertex)
            {
                if (prev_vertex->left == root)
                {
                    printf("\x1B[36m(%d)\x1B[0m [", prev_vertex->number);
                }
                else if (prev_vertex->right == root && prev_vertex->left == NULL)
                {
                    printf("\x1B[36m(%d)\x1B[0m [ - ", prev_vertex->number);
                }

                if (prev_vertex->left == root)
                    printf("%d", root->number);
                else if (prev_vertex->right == root)
                    printf(", %d", root->number);

                (*print_elem)++;

                if (prev_vertex->right == root)
                {
                    printf("] ");
                }
                else if (prev_vertex->left == root && prev_vertex->right == NULL)
                {
                    printf(", - ] ");
                }
            }
            else
            {
                printf("%d ", root->number);
                (*print_elem)++;
            }
        }
        else
        {
            print_tree_table_level(root->left, height, print_elem, root);
            print_tree_table_level(root->right, height, print_elem, root);
        }
    }
}

void print_tree_table(vertex_t *root, int max_height)
{
    int print_elem = 0;
    vertex_t *prev_vertex = NULL;

    printf("\n\x1B[33mДДП\x1B[0m\n\n");

    if (root == NULL)
    {
        printf("\x1B[36mДерево пусто\x1B[0m\n");
        return;
    }
    
    for (int i = 0; i <= max_height; i++)
    {
        print_tree_table_level(root, i, &print_elem, prev_vertex);
        printf("\n");
    }
}

void print_hash_table(hash_table_t *table)
{
    if (table->elements == 0)
    {
        printf("\x1B[36mХеш-таблица пуста\x1B[0m\n\n");
        return;
    }

    printf("\x1B[33mИндекс | Элемент\x1B[0m\n\n");

    for (int i = 0; i < table->size; i++)
    {
        if (table->array[i].bool == '1')
            printf("\x1B[36m%3d | %3d\x1B[0m\n", i, table->array[i].number);
        // else
        //     printf("%3d |  -\n", i);
    }

    printf("\n\x1B[33mСреднее кол-во сравнений для нахождения нужного элемента в таблице:"
        " %.3f\x1B[0m\n\n", (double) table->total_compare / table->elements);

    // printf("total_compare = %d\nelements = %d\n\n", table->total_compare, table->elements);
}

void print_tree_sideways_level(vertex_t *root, int place)
{
    int space = 5;

    if (root)
    {
        place += space;

        print_tree_sideways_level(root->right, place);

        printf("\n");

        for (int i = space; i < place; i++, printf(" "));

        printf("\x1B[36m%d\x1B[0m\n", root->number);

        print_tree_sideways_level(root->left, place);
    }
}

void print_tree_sideways(vertex_t *root, int place)
{
    printf("\n\x1B[33mДДП\x1B[0m\n\n");

    if (root == NULL)
    {
        printf("\x1B[36mДерево пусто\x1B[0m\n");
        return;
    }

    print_tree_sideways_level(root, place);
}

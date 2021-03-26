#include "../inc/read.h"

int fill_buffer(int *buf, int *size_buf, FILE *f)
{
    int r, i = 0;

    while (!feof(f))
    {   
        if (*size_buf >= MAX_NUMBER_OF_ELEM_IN_FILE)
        {
            printf("\n\x1B[31mБуфер переполнен\x1B[0m\n\n");
            return BUFFER_OVERFLOW;
        }

        r = fscanf(f, "%d", &buf[i++]);

        if (r != 1 && *size_buf == 0)
            return SUCCESS;

        if (r != 1)
        {
            printf("\n\x1B[31mНе удалось прочитать число из файла\x1B[0m\n\n");
            return FAILED_TO_READ_NUMBER;
        }
        
        (*size_buf)++;
    }

    return SUCCESS;
}

int read_tree(tree_t *tree, int *buf, int size_buf)
{
    if (size_buf == 0)
        return SUCCESS;

    int r = create_vertex(&tree->root, 0);

    if (r)
    {
        free_tree(tree->root);
        return r;
    }

    tree->size++;

    if (size_buf > 2)
        tree->root->number = buf[size_buf - 2];
    else  
        tree->root->number = buf[size_buf - 1];
    

    vertex_t *elem = tree->root;

    while (tree->size < size_buf)
    {
        tree->height++;
        tree->size++;

        if (tree->size == size_buf)
        {
            r = create_vertex(&elem->right, elem->height + 1);

            if (r)
            {
                free_tree(tree->root);
                return r;
            }

            elem->right->number = buf[size_buf - tree->size + 1];
            break;
        }

        r = create_vertex(&elem->left, elem->height + 1);

        if (r)
        {
            free_tree(tree->root);
            return r;
        }

        tree->size++;

        r = create_vertex(&elem->right, elem->height + 1);

        if (r)
        {
            free_tree(tree->root);
            return r;
        }

        elem->right->number = buf[size_buf - tree->size  + 2];

        if (tree->size != size_buf)
            elem->left->number = buf[size_buf - tree->size - 1];
        else
            elem->left->number = buf[size_buf - tree->size];

        elem = elem->left;
    }

    return SUCCESS;
}

int read_balanced_tree_elem(vertex_t **root, int *buf, int size_buf, int height)
{   
    if (size_buf == 0)
        return SUCCESS;

    int r = create_vertex(root, height);

    if (r)
        return r;

    (*root)->number = buf[size_buf / 2];

    r = read_balanced_tree_elem(&(*root)->left, buf, size_buf / 2, height + 1);

    if (r)
        return r;

    r = read_balanced_tree_elem(&(*root)->right, buf + size_buf / 2 + 1, 
        size_buf - size_buf / 2 - 1, height + 1);

    if (r)
        return r;

    return SUCCESS;
}

int read_balanced_tree(tree_t *tree, int *buf, int size_buf)
{
    tree->size = size_buf;

    int r = read_balanced_tree_elem(&tree->root, buf, size_buf, 0);

    if (r)
    {
        free_tree(tree->root);
        return r;
    }
    
    while (size_buf > 1)
    {
        size_buf /= 2;
        tree->height++;
    }

    return SUCCESS;
}

int read_number_action(int *number_action, int max_command_number)
{
    int r;
    
    printf("Введите номер команды: ");
    r = scanf("%d", number_action);
    printf("\n");
    
    if (r != 1)
    {
        printf("\x1B[31mНе удалось прочитать номер команды\x1B[0m\n\n");
        return FAILED_TO_READ_COMMAND_NUMBER;
    }
    
    if (*number_action < MIN_COMMAND_NUMBER || *number_action > max_command_number)
    {
        printf("\x1B[31mНомер команды должен быть >= %d и <= %d\x1B[0m\n\n",
        MIN_COMMAND_NUMBER, max_command_number);

        return WRONG_COMMAND_NUMBER;
    }
    
    return SUCCESS;
}

int read_number(int *number)
{
    int r = scanf("%d", number);
    printf("\n");

    if (r != 1)
    {
        printf("\x1B[31mНе удалось прочитать элемент\x1B[0m\n");
        return FAILED_TO_READ_NUMBER;
    }

    return SUCCESS;
}

int read_hash_table(hash_table_t *table, int *buf, int size_buf)
{
    if (!size_buf)
        return SUCCESS;

    table->size = buf[size_buf - 1];
    table->divider = buf[size_buf - 1];
    
    table->array = calloc(table->size, sizeof(hash_elem_t));

    if (!table->array)
        return MEMORY_ALIGNMENT_ERROR;

    for (int i = 0; i < size_buf; i++)
    {
        table->array[buf[i] % table->divider].number = buf[i];
        table->array[buf[i] % table->divider].bool = '1';
        table->elements++;
    }

    return SUCCESS;
}

int read_number_of_comparisons(int *number)
{
    printf("Введите максимальное кол-во сравнений в хеш-таблице: ");

    int r = scanf("%d", number);

    if (r != 1)
    {
        printf("\n\x1B[31mНе удалось прочитать кол-во сравнений\x1B[0m\n\n");
        return FAILED_TO_READ_NUMBER;
    }
    
    if (*number <= 0)
    {
        printf("\n\x1B[31mКол-во сравнений должно быть больше 0\x1B[0m\n\n");
        return NEGATIVE_NUMBER_OF_COMPARISONS;
    }

    return SUCCESS;
}

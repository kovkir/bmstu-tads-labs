#include "../inc/work_with_tree.h"

void free_tree(vertex_t *root)
{
    if (root)
    {
        free_tree(root->left);
        free_tree(root->right);
    }

    free(root);
}

int create_vertex(vertex_t **vertex, int height)
{
    vertex_t *p = malloc(sizeof(vertex_t));

    if (!p)
        return MEMORY_ALIGNMENT_ERROR;

    *vertex = p;

    (*vertex)->left = NULL;
    (*vertex)->right = NULL;
    (*vertex)->height = height;

    return SUCCESS;
}

int comparator(const void *var1, const void *var2)
{
    return *((int*) var1) - *((int*) var2);
}

int search_elem(int number, vertex_t *root, vertex_t **prev_elem, int *total_compare)
{
    *prev_elem = NULL;

    while(root)
    {
        (*total_compare)++;

        if (root->number == number)
            return YES;

        *prev_elem = root;

        if (root->number > number)
            root = root->left;
        else
            root = root->right;
    }

    return NO;
}

int insert_element_into_tree(vertex_t *prev_elem, int number, tree_t *tree)
{   
    int r;

    if (prev_elem == NULL)
    {
        r = create_vertex(&tree->root, 0);

        if (r)
            return r;

        tree->root->number = number;
        tree->size++;

        return SUCCESS;
    }

    if (prev_elem->number > number)
    {
        r = create_vertex(&prev_elem->left, prev_elem->height + 1);

        if (r)
            return r;

        prev_elem->left->number = number;
    }
    else
    {
        r = create_vertex(&prev_elem->right, prev_elem->height + 1);

        if (r)
            return r;

        prev_elem->right->number = number;
    }

    tree->size++;

    if (prev_elem->height == tree->height)
        tree->height++;

    return SUCCESS;
}

void remove_item_from_buffer(int *buf, int *size_buf, int number)
{
    for (int i = 0; i < *size_buf; i++)
    {
        if (buf[i] == number)
            buf[i] = buf[--(*size_buf)];
    }
}

int add_item_to_buffer(int *buf, int *size_buf, int number)
{
    if (*size_buf >= MAX_NUMBER_OF_ELEM_IN_FILE)
    {
        printf("\n\x1B[31mБуфер переполнен\x1B[0m\n\n");
        return BUFFER_OVERFLOW;
    }

    buf[*size_buf] = number;
    (*size_buf)++;

    return SUCCESS;
}

void remove_item_from_tree(vertex_t *prev_elem, int number, tree_t *tree)
{
    vertex_t *elem, *next_elem = NULL;

    if (prev_elem == NULL)
    {
        elem = tree->root;
    }
    else if (prev_elem->left != NULL && prev_elem->left->number == number)
    {
        elem = prev_elem->left;
    }
    else
    {
        elem = prev_elem->right;
    }
    
    if (elem->left == NULL && elem->right == NULL)
    {
        next_elem = NULL;
    }
    else if (elem->left == NULL && elem->right != NULL)
    {
        next_elem = elem->right;
    }
    else if (elem->left != NULL && elem->right == NULL)
    {
        next_elem = elem->left;
    }

    if (elem->left != NULL && elem->right != NULL)
    {
        prev_elem = elem;
        elem->number = search_min_elem(elem->right, &prev_elem);
        remove_item_from_tree(prev_elem, elem->number, tree);
    }
    else
    {
        if (prev_elem == NULL)
        {
            free(elem);
            tree->root = next_elem;
        }
        else if (prev_elem->left != NULL && prev_elem->left->number == number)
        {
            free(elem);
            prev_elem->left = next_elem;
        }
        else
        {
            free(elem);
            prev_elem->right = next_elem;
        }

        reduce_levels(next_elem);
        tree->size--;
    }
}

void reduce_levels(vertex_t *next_elem)
{
    if (next_elem)
    {
        next_elem->height--;

        reduce_levels(next_elem->left);
        reduce_levels(next_elem->right);
    }
}

int search_min_elem(vertex_t *root, vertex_t **prev_elem)
{
    while(root->left)
    {
        *prev_elem = root;
        root = root->left;
    }

    return root->number;
}

void tree_balance_check(vertex_t *root, int *fill_in_again, int max_height)
{
    if (root)
    {
        tree_balance_check(root->left, fill_in_again, max_height);
        tree_balance_check(root->right, fill_in_again, max_height);

        if ((root->left == NULL || root->right == NULL) && root->height < max_height - 1)
            *fill_in_again = 1;
    }
} 

void calculate_number_of_comparisons_in_tree(int *buf, int size_buf, tree_t *tree)
{   
    vertex_t *prev_elem;

    tree->total_compare = 0;

    for (int i = 0; i < size_buf; i++)
    {
        search_elem(buf[i], tree->root, &prev_elem, &tree->total_compare);
    }
}

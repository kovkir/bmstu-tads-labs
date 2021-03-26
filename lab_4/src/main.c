#include "../inc/main.h"

int main(void)
{
    int r;
    int stack_type;

    setbuf(stdout, NULL);
    system("clear");

    r = read_stack_type(&stack_type);

    if (r)
        return r;

    if (stack_type == 1)
        r = work_with_stack_array();
    else if (stack_type == 2)
        r = work_with_stack_list();
    else
        r = compare_stacks();
    
    if (r)
        return r;

    return SUCCESS;
}
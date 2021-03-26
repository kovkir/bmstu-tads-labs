#include "../inc/main.h"

int main(void)
{
    int r;
    int st_num_act;
    
    setbuf(stdout, NULL);
    system("clear");

    r = read_start_number_action(&st_num_act);

    if (r)
        return r;

    if (st_num_act == 1)
    {
        r = compare_turns();
    }
    else if (st_num_act == 2)
    {
        r = solution_of_problem();
    }
    
    if (r)
        return r;

    return SUCCESS;
}

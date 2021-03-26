#include "../inc/main.h"

int main(void)
{   
    system("clear");

    FILE *f = fopen("data.txt", "r");

    if (!f)
        return FILE_OPENING_ERROR;

    int buf[MAX_NUMBER_OF_ELEM_IN_FILE];
    int size_buf, action = 0, r;

    while (TRUE)
    {
        if (fseek(f, 0 , SEEK_SET))
            return POINT_OFFSET_ERROR;

        size_buf = 0;

        r = fill_buffer(buf, &size_buf, f);

        if (r)
            return r;

        if (action != 3 && action != 4)
            system("clear");

        print_start_menu();

        r = read_number_action(&action, 4);

        if (r)
            return r;

        // system("clear");

        if (action == 1)
        {
            r = work_with_trees(buf, size_buf);

            if (r)
                return r;
        }
        else if (action == 2)
        {
            r = work_with_hash_table(buf, size_buf);

            if (r)
                return r;
        }
        else if (action == 3)
        {
            if (fclose(f))
                return FILE_CLOSING_ERROR;

            f = fopen("data.txt", "w");

            if (!f)
                return FILE_OPENING_ERROR;
 
            r = add_item_to_file(buf, size_buf, f);

            if (r)
                return r;

            if (fclose(f))
                return FILE_CLOSING_ERROR;

            f = fopen("data.txt", "r");

            if (!f)
                return FILE_OPENING_ERROR;
        }
        else if (action == 4)
        {
            r = measurements(10);

            if (r)
                return r;
            
            r = measurements(25);

            if (r)
                return r;
            
            r = measurements(50);

            if (r)
                return r;

            r = measurements(100);

            if (r)
                return r;
        }
        else
        {
            break;
        }
    }
    
    if (fclose(f))
        return FILE_CLOSING_ERROR;

    return SUCCESS;
}

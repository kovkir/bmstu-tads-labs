#include "../inc/solution_of_problem.h"

int solution_of_problem(void)
{
    turn_list_t list;

    list.size = 0;
    list.head = NULL;

    int64_t begin_t1, end_t1, step_t1,
            begin_t2, end_t2, step_t2,
            begin_t3, end_t3, step_t3,
            arrival_time = 0,
            start_downtime, downtime = 0,
            simul_time = 0;

    int r;

    int numb_proc_app = 0, numb_rem_elem = 0, numb_add_elem = 0,
        ind_sec_app = 1, numb_sec_app = 0;
    double sum_time_in_turn = 0, time_in_turn, aver_len_turn;
    long long int sum_len_turn = 0, numb_check = 0, k = time(NULL);
    
    srand(k);

    step_t1 = MIN_T1 + rand() % (MAX_T1 - MIN_T1 + 1);
    begin_t1 = tick();

    step_t3 = MIN_T3 + rand() % (MAX_T3 - MIN_T3 + 1);
    begin_t3 = begin_t1;

    start_downtime = begin_t1;
    
    while (TRUE)
    {
        if (ind_sec_app != 1)
            sum_len_turn++;

        sum_len_turn += list.size;
        
        if (list.size != 0)
            sum_len_turn--;

        numb_check++;

        if ((end_t1 = tick()) - begin_t1 >= step_t1)
        {
            arrival_time += end_t1 - begin_t1;
            numb_add_elem++;
            
            
            srand(k += 5);

            step_t1 = MIN_T1 + rand() % (MAX_T1 - MIN_T1 + 1);
            begin_t1 = tick();

            r = fill_turn_list_randomly(&list, 1);

            if (r)
            {
                free_turn_list(&list);
                return r;
            }

            if (list.size == 1)
            {
                srand(k);

                step_t2 = MIN_T2 + rand() % (MAX_T2 - MIN_T2 + 1);
                begin_t2 = tick();

                downtime += end_t1 - start_downtime;
            }
        }

        if (ind_sec_app == 1 && ((end_t3 = tick()) - begin_t3 >= step_t3))
        {
            numb_sec_app++;

            if (list.size < 4)
            {
                ind_sec_app = list.size + 1;

                srand(k++);

                step_t3 = MIN_T3 + rand() % (MAX_T3 - MIN_T3 + 1);
                begin_t3 = end_t3;
            }
            else
                ind_sec_app = 4;
        }

        if (ind_sec_app != 1 && list.size != 0 && ((end_t2 = tick()) - begin_t2 >= step_t2))
        {
            simul_time += end_t2 - begin_t2;

            sum_time_in_turn += 
            (end_t2 - list.head->start) / (double) UNIT_OF_TIME;
            numb_rem_elem++;

            remove_elem_from_turn_list(&list, 1);

            if (list.size == 0)
            {
                start_downtime = tick();
            }
            else
            {
                srand(k);

                step_t2 = MIN_T2 + rand() % (MAX_T2 - MIN_T2 + 1);
                begin_t2 = tick();
            }

            numb_proc_app++;

            if (numb_proc_app == 1000)
                break;

            if (numb_proc_app % 100 == 0)
            {
                time_in_turn = sum_time_in_turn / numb_rem_elem;
                aver_len_turn = sum_len_turn / (double) numb_check;

                printf("Текущая длина очереди = %d\n", list.size);
                printf("Средняя длина очереди - %lf\n", aver_len_turn);
                printf("Кол-во вошедших заявок в очередь - %d\n", numb_add_elem);
                printf("Кол-во вышедших заявок из очереди - %d\n", numb_rem_elem);
                printf("Среднее время пребывания заявок в очереди = %lf е.в.\n\n", time_in_turn);
            }

            ind_sec_app--;

            if (ind_sec_app == 1)
            {
                srand(k);

                step_t3 = MIN_T3 + rand() % (MAX_T3 - MIN_T3 + 1);
                begin_t3 = tick();
            }
        }
    }

    time_in_turn = sum_time_in_turn / numb_rem_elem;
    aver_len_turn = sum_len_turn / (double) numb_check;

    printf("\n                  Результаты\n\n");
    printf("    Время моделирования = %Lf е.в.\n", arrival_time / (long double) UNIT_OF_TIME);
    printf("    Время работы аппарата ОА = %Lf е.в.\n", simul_time / (long double) UNIT_OF_TIME);
    printf("    Время простоя = %Lf е.в.\n", downtime / (long double) UNIT_OF_TIME);
    printf("    Среднее время пребывания заявок в очереди = %lf е.в.\n", time_in_turn);
    printf("    Кол-во вошедших заявок в очередь - %d\n", numb_add_elem);
    printf("    Кол-во вышедших заявок из очереди - %d\n", numb_rem_elem);
    printf("    Средняя длина очереди - %lf\n", aver_len_turn);
    printf("    Кол-во обращений заявок второго типа - %d\n\n\n", numb_sec_app);

    return SUCCESS;
};
#include "filosofos.h"

int check_death_flag(t_instruc *instrucciones)
{

};

int check_eat_time(t_info philo)
{

};

void *check_death(void *philo)
{
    int i;
    t_info *phil;
    t_instruc *instrucciones;

    phil = (t_info *)philo;
    instrucciones = phil->instrucciones;
    i = -1;
    while (check_death_flag(instrucciones))
    {
        while (++i < instrucciones->n_filosofos)
        {
            if (check_eat_time(phil[i]))
            {
                return NULL;
            }
        }
        if (instrucciones->dead_flags == 1)
        {
            break;
        }
        i = -1;
        ft_usleep(300);
    }
    return (NULL);
}

int ft_matrix_len(char **argc)
{
    int i;
    i = 0;
    while (argc[i])
    {
        i++;
    }
    return i;
}

int get_time(void)
{
    struct timeval now;
    long milisecond;

    gettimeofday(&now, NULL);
    milisecond = now.tv_sec * 1000;
    milisecond = now.tv_usec / 1000;
    return milisecond;
}

void ft_deestroyMutex(t_info *new)
{
    int i;
    i = -1;
    pthread_mutex_destroy(&new->instrucciones->all_eat_mutex);
    pthread_mutex_destroy(&new->instrucciones->print_mutex);
    pthread_mutex_destroy(&new->instrucciones->dead_flag_mutes);
    pthread_mutex_destroy(&new->instrucciones->dead_mutex);
    while (++i < new->instrucciones->n_filosofos)
        pthread_mutex_destroy(&new->instrucciones->forks_mutex[i]);
}
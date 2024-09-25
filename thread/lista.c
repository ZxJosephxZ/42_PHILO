#include "filosofos.h"

t_instruc *ft_initList(t_instruc *instrucciones, char **argc)
{
    int i;

    i = -1;
    instrucciones->n_filosofos = atoi(argc[1]);
    instrucciones->t_muerte = atoi(argc[2]);
    instrucciones->t_comida = atoi(argc[3]);
    instrucciones->t_dormir = atoi(argc[4]);
    instrucciones->dead_flags = 0;
    instrucciones->all_comidas = 0;
    if (ft_matrix_len(argc) == 6)
    {
        instrucciones->n_comidas = atoi(argc[5]);
    }
    else
    {
        instrucciones->n_comidas = 0;
    }
    instrucciones->forks_mutex = malloc(sizeof(pthread_mutex_t)* instrucciones->n_filosofos);
    pthread_mutex_init(&(instrucciones)->dead_flag_mutes, NULL);
    pthread_mutex_init(&(instrucciones)->print_mutex, NULL);
    pthread_mutex_init(&(instrucciones)->dead_mutex, NULL);
    pthread_mutex_init(&(instrucciones)->all_eat_mutex, NULL);
    pthread_mutex_init(&(instrucciones)->thread_mutex, NULL);
    while (++i < instrucciones->n_filosofos)
    {
        pthread_mutex_init(&(instrucciones)->forks_mutex[i], NULL);
    }
    instrucciones->t_start = get_time();
    return instrucciones;
}

t_info *ft_listConcatenacion(t_instruc *instrucciones)
{
    int i;
    t_info *new;

    i = 0;
    new = malloc(sizeof(t_info)*instrucciones->n_filosofos);
    while (i < instrucciones->n_filosofos)
    {
        new[i].number = i + 1;
        new[i].instrucciones = instrucciones;
        if (i == 0)
        {       
            new[i].left_fork = instrucciones->n_filosofos - 1;
        }
        else
        {
            new[i].left_fork = i - 1;
        }
        new[i].right_fork = i;
        new[i].times_eat = 0;
        pthread_mutex_init(&new[i].check_last_eat, NULL);
        new[i].last_eat = get_time();
        i++;
    }
    return new;
}

void ft_create_thread(t_info *philo, int number, t_instruc *instrucciones)
{
    int i;

    i = -1;
    if (pthread_create(&philo->instrucciones->thread_dead, NULL, &check_death,  (void*)philo))
        return (1);
    while (i < number)
    {

    }
}
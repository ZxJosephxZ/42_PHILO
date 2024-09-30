#include "filosofos.h"

int check_death_flag(t_instruc *instrucciones)
{
    int check_flag;

    check_flag = 0;
    pthread_mutex_lock(&(instrucciones->dead_flag_mutes));
    if (instrucciones->dead_flags != 1)
        check_flag = 1;
    pthread_mutex_unlock(&(instrucciones->dead_flag_mutes));
    pthread_mutex_lock(&instrucciones->all_eat_mutex);
    if (check_flag == 1 && instrucciones->n_comidas != 0 && instrucciones->all_comidas >= instrucciones->n_filosofos)
        check_flag = 0;
    pthread_mutex_unlock(&instrucciones->all_eat_mutex);
    return (check_flag);
};

void *check_death(void *args)
{
    int i;
    t_info *philo;
    t_instruc *instrucciones;

    philo = (t_info *)args;
    instrucciones = philo->instrucciones;
    i = -1;
    while (check_death_flag(instrucciones))
    {
        while (++i < instrucciones->n_filosofos)
        {
            if (check_eat_time(philo[i]))
                return NULL;
        }
        if (instrucciones->dead_flags == 1)
            break;
        i = -1;
        ft_usleep(300);
    }
    return NULL;
}

int check_eat_time(t_info philo)
{
    long actual;

    actual = get_time();
    if (actual > philo.last_eat + philo.instrucciones->t_muerte)
    {
        pthread_mutex_lock(&(philo.instrucciones->dead_flag_mutes));
        philo.instrucciones->dead_flags = 1;
        pthread_mutex_unlock(&(philo.instrucciones->dead_flag_mutes));
        ft_usleep(1000);
        printf("%6ld %d died\n", get_time() - philo.instrucciones->t_start, philo.number);
        return 1;
    }
    return 0;
};

void print_mes(time_t t_action, enum e_message message, t_info *philo)
{
    pthread_mutex_lock(&(philo->instrucciones->print_mutex));
    if (check_death_flag(philo->instrucciones) == 0)
    {
        pthread_mutex_unlock(&(philo->instrucciones->print_mutex));
        return ;
    }
    if (message == LEFT_FORK)
    {
        printf("%6ld %3d has taken a fork\n", t_action, philo->number);
    }
    else if (message == RIGHT_FORK)
    {
        printf("%6ld %3d has taken a fork\n", t_action, philo->number);
    }
    else if (message == EAT)
    {
        printf("%6ld %3d is eating\n", t_action, philo->number);
    }
    else if (message == THINK)
    {
        printf("%6ld %3d is thinking\n", t_action, philo->number);
    }
    else if (message == SLEEP)
    {
        printf("%6ld %3d is sleeping\n", t_action, philo->number);
    }
    pthread_mutex_unlock(&(philo->instrucciones->print_mutex));
    return ;
}

void ft_usleep(int seg)
{
    int min;
    long start;

    min = seg / 1000;
    start = get_time();
    while (get_time() - start < min)
        usleep(100);
    return ;
}

void thinking_routine(t_info *philo)
{
    print_mes(get_time() - philo->instrucciones->t_start, THINK, philo);
    return ;
}

void sleep_routine(t_info *philo)
{
    t_instruc *instrucciones;

    instrucciones = philo->instrucciones;
    print_mes(get_time() - instrucciones->t_start, SLEEP, philo);
    ft_usleep(instrucciones->t_dormir * 1000);
    thinking_routine(philo);
}

void    eat_routine(t_info *philo)
{
    t_instruc *instrucciones;

    instrucciones = philo->instrucciones;
    pthread_mutex_lock(&philo->instrucciones->forks_mutex[philo->right_fork]);
    print_mes(get_time() - philo->instrucciones->t_start, RIGHT_FORK, philo);
    pthread_mutex_lock(&philo->instrucciones->forks_mutex[philo->left_fork]);
    print_mes(get_time() - philo->instrucciones->t_start, LEFT_FORK, philo);
    pthread_mutex_lock(&philo->check_last_eat);
    philo->last_eat = get_time();
    pthread_mutex_unlock(&philo->check_last_eat);
    print_mes(get_time() - instrucciones->t_start, EAT, philo);
    (ft_usleep(instrucciones->t_comida * 1000), philo->times_eat++);
    pthread_mutex_lock(&instrucciones->all_eat_mutex);
    if (instrucciones->n_comidas != 0 && instrucciones->n_comidas == philo->times_eat)
        instrucciones->all_comidas++;
    pthread_mutex_unlock(&instrucciones->all_eat_mutex);
    pthread_mutex_unlock(&philo->instrucciones->forks_mutex[philo->right_fork]);
    pthread_mutex_unlock(&philo->instrucciones->forks_mutex[philo->left_fork]);
    sleep_routine(philo);
}

void *routine(void *args)
{
    t_info *philo;
    t_instruc *instrucciones;

    philo = (t_info *)args;
    instrucciones = philo->instrucciones;
    if (philo->number % 2 == 0)
    {
        pthread_mutex_lock(&instrucciones->thread_mutex);
        ft_usleep(1000);
        pthread_mutex_unlock(&instrucciones->thread_mutex);
    }
    while (1)
    {
        eat_routine(philo);
        if (!check_death_flag(instrucciones))
            break;
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
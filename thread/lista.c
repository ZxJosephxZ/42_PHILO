#include "filosofos.h"

void *philo_init(int n_philo, t_list *philos)
{
    int i;
    t_list *start;
    t_philo *philo;

    i = -1;
    start = philos;
    while (++i < n_philo)
    {
        philo = start->content;
        if (pthread_create(&philo->philo_thread, NULL, start_thread, start))
           return (philo_exit(philos, NULL, THREAD_FAILED));
        start = start->next;
    }
    philo_monitor(start, NULL);
    i = -1;
    while (++i < n_philo)
    {
        philo = start->content;
        pthread_join(philo->philo_thread, NULL);
        start = start->next;
    }
    return (NULL);
}

void *philo_monitor(t_list *start, t_philo *philo)
{
    long n_eat;
    long last_eat;

    while (1)
    {
        philo = start->content;
        pthread_mutex_lock(&philo->instrucciones->n_eat_lock);
        n_eat = philo->instrucciones->n_comidas;
        pthread_mutex_unlock(&philo->instrucciones->n_eat_lock);
        pthread_mutex_lock(&philo->last_eat_lock);
        last_eat = philo->last_eat;
        pthread_mutex_unlock(&philo->last_eat_lock);
        if (philo_get_time() - philo->instrucciones->init_time - last_eat >= \
            philo->instrucciones->t_died || n_eat == \
            philo->instrucciones->n_filosofos * philo->instrucciones->repeat_count)
        {
            pthread_mutex_lock(&philo->instrucciones->died_lock);
            philo->instrucciones->dead = 1;
            pthread_mutex_unlock(&philo->instrucciones->died_lock);
            if (n_eat != philo->instrucciones->n_filosofos * philo->instrucciones->repeat_count)
                philo_timestamp(start, PHILO_DIE, 0);
            return (NULL);
        }
        start = start->next;
    }
}

void philo_actions(t_list *node, t_philo *philo, t_philo *next)
{
    pthread_mutex_lock(&philo->fork_lock);
    philo_timestamp(node, PHILO_TAKE_FORK, 0);
    pthread_mutex_lock(&next->fork_lock);
    philo_timestamp(node, PHILO_TAKE_FORK, 0);
    pthread_mutex_lock(&philo->last_eat_lock);
    philo->last_eat = philo_get_time() - philo->instrucciones->init_time;
    pthread_mutex_unlock(&philo->last_eat_lock);
    philo_timestamp(node, PHILO_EAT, philo->instrucciones->t_eat);
    philo_timestamp(node, PHILO_SLEEP, 0);
    pthread_mutex_unlock(&next->fork_lock);
    pthread_mutex_unlock(&philo->fork_lock);
    ft_usleep(philo->instrucciones->t_sleep);
    philo_timestamp(node, PHILO_THINK, 0);
}

void *start_thread(void *node)
{
    t_philo *philo;
    t_philo *next;
    int i;

    i = -1;
    philo = ((struct s_list *)node)->content;
    next = ((struct s_list *)node)->next->content;
    ft_usleep(!(philo->id % 2) * 2);
    pthread_mutex_lock(&philo->instrucciones->died_lock);
    while (philo->id != next->id && !philo->instrucciones->dead && \
        (philo->instrucciones->repeat_count == -2 || ++i < philo->instrucciones->repeat_count))
    {
        pthread_mutex_unlock(&philo->instrucciones->died_lock);
        philo_actions(node, philo, next);
        pthread_mutex_unlock(&philo->instrucciones->died_lock);
    }
    pthread_mutex_unlock(&philo->instrucciones->died_lock);
    return (NULL);
}
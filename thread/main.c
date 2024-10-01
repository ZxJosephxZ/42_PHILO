#include "filosofos.h"

int ft_isnum(char *arg)
{
    int prueba; //diseñar atoi que no acepte espacios

    prueba = atoi(arg);
    if (0 < prueba && prueba< INT_MAX )
    {
        return 1;
    }
    ft_error(0, arg);
    return 0;
}

static t_instruc ft_parseo(char **argc)
{
    t_instruc instruct;

    instruct.n_filosofos = ft_atoi(argc[1]);
    if (instruct.n_filosofos <= 0)
        philo_exit(NULL, argc[1], INV_PHILO_COUNT);
    if (instruct.n_filosofos > 800)
        philo_exit(NULL, argc[1], TOO_MANY_PHILO);
    instruct.t_died = ft_atoi(argc[2]);
    if (instruct.t_died == -1)
        philo_exit(NULL, argc[2], INV_DIE_TIME);
    instruct.t_eat = ft_atoi(argc[3]);
    if (instruct.t_eat == -1)
        philo_exit(NULL, argc[3], INV_EAT_TIME);
    instruct.t_sleep = ft_atoi(argc[4]);
    if (instruct.t_sleep == -1)
        philo_exit(NULL, argc[4], INV_SLEEP_TIME);
    instruct.repeat_count = -2;
    if (argc[5])
    {
        instruct.repeat_count = ft_atoi(argc[5]);
        if (instruct.repeat_count == -1 || !instruct.repeat_count)
            philo_exit(NULL, argc[5], INV_REPEAT_COUNT);
    }
    return (instruct);
}

t_info *ft_iniciar(t_info *info, t_instruc *instrucciones)
{
    info = malloc(sizeof(t_info));

}


static void ft_init(t_instruc *instrucciones, char **argc, t_info *philos)
{
    
    t_info *filo = ft_iniciar(filo, instrucciones);
    if (atoi(argc[1]) == 1)
        ft_error(1, argc[1]);
    else
    {
        instrucciones = ft_initList(instrucciones, argc);
        philos = ft_listConcatenacion(instrucciones);
        instrucciones->info = philos;
        ft_create_thread(philos, atoi(argc[1]), instrucciones);
    }
    
}

int main(int arc, char **argc) //cantidad de filosofos,tiempo de muerte,tiempo para comer,tiempo para dormir,op(numero de comidas)
{
    t_instruc instruct;
    t_list *philos;
    if (arc != 5 && arc != 6)
    {
        philo_exit(NULL, NULL, INV_ARGS);
        printf("\nargument: [number_philo] [time_die] [time_eat]");
        printf("[time_sleep] [time_repeat]\n");
        return (1);
    }
    instruct = ft_parseo(argc);
    if (instruct.n_filosofos <= 0 || instruct.n_filosofos > 800 || instruct.t_died == -1 || \
        instruct.t_eat == -1 || instruct.t_sleep == -1 || instruct.repeat_count == -1 || \
        !instruct.repeat_count)
        return (1);
    instruct.init_time = philo_get_time();
    instruct.dead = 0;
    instruct.n_comidas = 0;
    pthread_mutex_init(&instruct.died_lock, NULL);
    pthread_mutex_init(&instruct.n_eat_lock, NULL);
    philos = philo_last(&instruct);
    ft_lstlast(philos)->next = philos;
    philo_init(instruct.n_filosofos, philos);
    philo_exit(philos, NULL, END);
    return (0);
}
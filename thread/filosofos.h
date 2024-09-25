#ifndef FILOSOFOS_H
#define FILOSOFOS_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/time.h>
#include <pthread.h>
//gcc tus .c -lpthread


typedef struct t_info
{
    int number;
    int left_fork;
    int  right_fork;
    long times_eat;
    time_t last_eat;
    pthread_t philo_thread;
    pthread_mutex_t check_last_eat;
    struct t_instruc *instrucciones;
}t_info;

typedef struct t_instruc
{
    int n_filosofos;
    long t_comida;
    long t_dormir;
    long t_muerte;
    long n_fork;
    int n_comidas;
    long all_comidas;
    time_t t_start;
    pthread_t thread_dead;
    int dead_flags;
    pthread_mutex_t thread_mutex;
    pthread_mutex_t dead_mutex;
    pthread_mutex_t dead_flag_mutes;
    pthread_mutex_t all_eat_mutex;
    pthread_mutex_t print_mutex;
    pthread_mutex_t *forks_mutex;
    t_info *info;
    
}t_instruc;

enum e_message
{
    LEFT_FORK,
    RIGHT_FORK,
    EAT,
    THINK,
    SLEEP,
    DYE
};

void ft_error(int i, char *error);
t_instruc *ft_initList(t_instruc *instrucciones, char **argc);
t_info *ft_listConcatenacion(t_instruc *instrucciones);
int ft_matrix_len(char **argc);
int get_time(void);
void ft_deestroyMutex(t_info *new);
void ft_create_thread(t_info *philo, int number, t_instruc *instrucciones);
void *check_death(void *philo);
#endif
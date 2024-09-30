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

# define PHILO_EAT "\033[1;93mis eating 🍝\033[0;39m"
# define PHILO_SLEEP "\033[1;95mis sleeping 🌙\033[0;39m"
# define PHILO_THINK "\033[1;90mis thinking 💭\033[0;39m"
# define PHILO_TAKE_FORK "\033[1;94mhas taken a fork 🍴\033[0;39m"
# define PHILO_DIE "\033[1;91mdied 💀\033[0;39m"


typedef enum e_philo_error
{
    END = 1,
	INV_ARGS = -1,
	TOO_MANY_PHILO = -2,
	INV_PHILO_COUNT = -3,
	INV_DIE_TIME = -4,
	INV_EAT_TIME = -5,
	INV_SLEEP_TIME = -6,
	INV_REPEAT_COUNT = -7,
	NO_MEMORY = -8,
	THREAD_FAILED = -9
}t_philo_error;


typedef struct t_info
{
    int id;
    useconds_t last_eat;
    pthread_t philo_thread;
    pthread_mutex_t fork_lock;
    pthread_mutex_t last_eat_lock;
    struct t_instruc *instrucciones;
}t_info;

typedef struct t_instruc
{
    int n_filosofos;
    useconds_t init_time;
    long repeat_count;
    long long t_died;
    long long t_eat;
    long long t_sleep;
    int n_comidas;
    int dead;
    pthread_mutex_t n_eat_lock;
    pthread_mutex_t died_lock;
    
}t_instruc;


#endif
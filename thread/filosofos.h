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

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct t_philo
{
    int id;
    useconds_t last_eat;
    pthread_t philo_thread;
    pthread_mutex_t fork_lock;
    pthread_mutex_t last_eat_lock;
    struct t_instruc *instrucciones;
}t_philo;

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

void *philo_monitor(t_list *start, t_philo *philo);
void *philo_init(int n_philo, t_list *philos);
void *start_thread(void *node);
void philo_actions(t_list *node, t_philo *philo, t_philo *next);
int ft_usleep(useconds_t seg);
useconds_t philo_get_time(void);
void *philo_exit(t_list *philos, char *param, t_philo_error err);
void philo_timestamp(t_list *philos, char *action, useconds_t t);
int philo_perror(char *param, t_philo_error err);
t_list *philo_lst(t_instruc *d);
t_philo *philo_get_data(t_instruc *d, int i);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **lst, t_list *newnode);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
long long	ft_atoi(const char *nptr);
int	ft_nbrlen(long n, int base);
int	ft_isdigit(int c);
int	ft_isspace(char c);
size_t	ft_strlen(const char *s);
int	ft_putchar_fd(char c, int fd);
int	ft_putnbr_fd(long unsigned n, int fd);
int	ft_putstr_fd(char *s, int fd);
int	ft_putnchar_fd(char c, int fd, int n);
#endif
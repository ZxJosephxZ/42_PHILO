#include "filosofos.h"

t_philo	*philo_get_data(t_instruc*d, int i)
{
	t_philo	*node;

	node = malloc(sizeof(struct t_philo));
	if (!node)
		return (philo_exit(NULL, NULL, THREAD_FAILED));
	node->id = i + 1;
	node->philo_thread = 0;
	pthread_mutex_init(&node->fork_lock, NULL);
	pthread_mutex_init(&node->last_eat_lock, NULL);
	node->instrucciones = d;
	node->last_eat= 0;
	return (node);
}

t_list	*philo_lst(t_instruc *d)
{
	int		i;
	t_list	*philos;

	i = -1;
	philos = NULL;
	while (++i < d->n_filosofos)
		ft_lstadd_back(&philos, ft_lstnew(philo_get_data(d, i)));
	return (philos);
}

int	philo_perror(char *param, t_philo_error err_code)
{
	ft_putstr_fd("philo: ", 2);
	if (err_code == INV_ARGS)
		ft_putstr_fd("invalid number of arguments", 2);
	if (err_code == NO_MEMORY)
		ft_putstr_fd("no memory left on device", 2);
	if (err_code == THREAD_FAILED)
		ft_putstr_fd("failed to create a thread", 2);
	if (err_code == INV_PHILO_COUNT)
		ft_putstr_fd("invalid philosopher_count: ", 2);
	if (err_code == INV_DIE_TIME)
		ft_putstr_fd("invalid time_to_die: ", 2);
	if (err_code == INV_EAT_TIME)
		ft_putstr_fd("invalid time_to_eat: ", 2);
	if (err_code == INV_SLEEP_TIME)
		ft_putstr_fd("invalid time_to_sleep: ", 2);
	if (err_code == INV_REPEAT_COUNT)
		ft_putstr_fd("invalid repeat_times: ", 2);
	if (err_code == TOO_MANY_PHILO)
		ft_putstr_fd("system may not be able to handle that many threads: ", 2);
	if (param && err_code != INV_ARGS && err_code != NO_MEMORY && \
			err_code != THREAD_FAILED)
		ft_putstr_fd(param, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

void	philo_timestamp(t_list *philos, char *action, useconds_t t)
{
	useconds_t	time;
	t_philo		*philo;
	int			died;
	int			eat_count;

	philo = philos->content;
	pthread_mutex_lock(&philo->instrucciones->died_lock);
	died = philo->instrucciones->dead;
	pthread_mutex_lock(&philo->instrucciones->n_eat_lock);
	eat_count = philo->instrucciones->n_comidas;
	time = philo_get_time() - philo->instrucciones->init_time;
	if (philo->instrucciones->repeat_count * philo->instrucciones->n_filosofos != \
			eat_count && (!died || action[7] == 'd'))
	{
		printf("[\033[1;39m%06u\033[0;39m]  \033[1;96m%03d  \033[0;39m%s\n", \
			time, philo->id, action);
	}
	if (action[10] == 'e')
		philo->instrucciones->n_comidas;
	pthread_mutex_unlock(&philo->instrucciones->n_eat_lock);
	pthread_mutex_unlock(&philo->instrucciones->died_lock);
	if (philo->instrucciones->repeat_count * philo->instrucciones->n_filosofos != \
			eat_count && (!died || action[7] == 'd'))
		ft_usleep(t);
}

void	*philo_exit(t_list *philos, char *param, t_philo_error err_code)
{
	t_philo	*philo;
	t_list	*temp;

	temp = philos;
	if (err_code != END)
		philo_perror(param, err_code);
	while (philos)
	{
		philo = philos->content;
		if (philo->id == philo->instrucciones->n_filosofos)
			philos->next = NULL;
		philos = philos->next;
	}
	ft_lstclear(&temp, free);
	return (NULL);
}
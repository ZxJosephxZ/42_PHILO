#include "filosofos.h"

useconds_t philo_get_time(void)
{
    struct timeval t;

    gettimeofday(&t, NULL);
    return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

int ft_usleep(useconds_t seg)
{
    useconds_t before;
    useconds_t after;

    before = philo_get_time();
    after = before;
    while (after - before < seg)
    {
        if (usleep(seg) == -1)
            return (-1);
        after = philo_get_time();
    }
    return (0);
}
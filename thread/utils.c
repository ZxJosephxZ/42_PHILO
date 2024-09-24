#include "filosofos.h"

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
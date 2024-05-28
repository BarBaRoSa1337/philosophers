/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakour <achakour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 09:48:32 by achakour          #+#    #+#             */
/*   Updated: 2024/05/28 11:50:49 by achakour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	sign;
	int	num;
	int	i;

	i = 0;
	num = 0;
	sign = 1;
	while (str[i] == '\f' || str[i] == '\t' || str[i] == '\r'
		|| str[i] == '\n' || str[i] == ' ' || str[i] == '\v')
	{
		++i;
	}
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		++i;
	}
	while ((str[i] >= '0' && str[i] <= '9'))
	{
		num = num * 10 + str[i] - '0';
		++i;
	}
	return (num * sign);
}

int get_args(int ac, char **ar, t_init *pars)
{
    int i;

    i = 1;
    pars->n_eat = 0;
    if (ac != 5 || ac > 6)
    {
        printf("Invalid use Try:\n./philosophers [number_of_philosophers] [time_to_die] [time_to_eat] \
            [time_to_sleep] [number_of_times_each_philosopher_must_eat]\n");
        return (0);
    }
    while (i <= ac)
    {
        if (i == 2)
            pars->n_philo = ft_atoi(ar[i - 1]);
        else if (i == 3)
            pars->tt_die = ft_atoi(ar[i - 1]);
        else if (i == 4)
            pars->tt_eat = ft_atoi(ar[i - 1]);
        else if (i == 5)
            pars->tt_sleep = ft_atoi(ar[i - 1]);
        else if (i == 6)
            pars->n_eat = ft_atoi(ar[i - 1]);
        ++i;
    }
    return (1);
}

void    ft_eating(int tt_eat, int index)
{
    int current_time;

    current_time = 0;
    printf("%d %d is eating\n", current_time, index);
    usleep(tt_eat);
}

void    ft_thinking(t_philo *philas, int index)
{
    int current_time;
    (void)philas;

    current_time = 0;
    printf("%d %d is thinking\n", current_time, index);
    usleep(500000);
}

void    ft_sleeping(int tt_sleep, int index)
{
    int current_time;

    current_time = 0;
    printf("%d %d is sleeping\n", current_time, index);
    usleep(tt_sleep);
}

void    lock_the_fork(t_philo *philas, int index, int current_time)
{
    int rigth_fork;

    current_time = 0;
    if (philas->index == 1)
        rigth_fork = philas->init->n_philo - 1;
    else
        rigth_fork = index - 1;
    pthread_mutex_lock(&philas->init->forks[rigth_fork]);
    printf("%d %d has taken a fork\n", current_time, index);
    pthread_mutex_lock(&philas->init->forks[index]);
    printf("%d %d has taken a fork\n", current_time, index);
}

void    unlock_the_fork(t_philo *philas, int index)
{
    if (philas->index == 1)
            pthread_mutex_unlock(&philas->init->forks[philas->init->n_philo - 1]);
        else
            pthread_mutex_unlock(&philas->init->forks[index - 1]);
    pthread_mutex_unlock(&philas->init->forks[index]);
}

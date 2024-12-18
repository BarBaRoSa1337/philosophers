/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakour <achakour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 09:48:32 by achakour          #+#    #+#             */
/*   Updated: 2024/11/16 14:53:16 by achakour         ###   ########.fr       */
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
	while (str[i] == '\f' || str[i] == '\t' || str[i] == '\r' || str[i] == '\n'
		|| str[i] == ' ' || str[i] == '\v')
		++i;
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

short int	check_num(t_init *p)
{
	if (p->tt_sleep <= 0 || p->tt_eat <= 0 || p->tt_die <= 0 || p->n_philo <= 0)
		return (1);
	else if (p->n_eat != -1 && p->n_eat <= 0)
		return (1);
	return (0);
}

short int	check_syntax(int ac, char **ar)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (ar[i][j])
		{
			if (!ft_isnum(ar[i][j]) && ar[i][j] != '-' && ar[i][j] != '+')
				return (1);
			else if (ft_isnum(ar[i][j]) && ar[i][j + 1] && !ft_isnum(ar[i][j
						+ 1]))
				return (1);
			++j;
		}
		++i;
	}
	return (0);
}

short int	get_args(int ac, char **ar, t_init *pars)
{
	int	i;

	if (ac < 5 || ac > 6 || check_syntax(ac, ar))
	{
		printf("Invalid Use Try Valid Arguments:\n./philosophers [number_of_philosophers] [time_to_die] [time_to_eat] \
		[time_to_sleep] [number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	i = 1;
	pars->n_eat = -1;
	pars->nbr_eating = 0;
	while (++i <= ac)
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
	}
	return (0);
}

void	init_forks(t_init *pars)
{
	int	n_philo;
	int	i;

	i = 0;
	n_philo = pars->n_philo;
	pars->forks = NULL;
	pthread_mutex_init(&pars->msg, NULL);
	pthread_mutex_init(&pars->eat_check, NULL);
	pthread_mutex_init(&pars->dead_flag, NULL);
	pars->forks = malloc(sizeof(pthread_mutex_t) * n_philo);
	if (!pars->forks)
		return ;
	while (i < n_philo)
	{
		pthread_mutex_init(&pars->forks[i], NULL);
		++i;
	}
}

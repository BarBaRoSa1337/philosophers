/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakour <achakour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 09:48:32 by achakour          #+#    #+#             */
/*   Updated: 2024/09/15 15:29:43 by achakour         ###   ########.fr       */
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

    // if (ac != 5 || ac > 6)
    // {
    //     printf("Invalid use Try:\n./philosophers [number_of_philosophers] [time_to_die] [time_to_eat] \
    //         [time_to_sleep] [number_of_times_each_philosopher_must_eat]\n");
    //     return (0);
    // }

    i = 1;
    pars->n_eat = 0;
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

pthread_mutex_t *init_forks(t_init *pars)
{
    pthread_mutex_t *forchit;
    int             n_philo;
    int             i;

    i = 0;
    n_philo = pars->n_philo;
    forchit = malloc(sizeof(pthread_mutex_t) * n_philo);
    if (!forchit)
        return (NULL);
    while (i < n_philo)
    {
        pthread_mutex_init(&forchit[i], NULL);
        ++i;
    }
    return (forchit);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakour <achakour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 09:48:32 by achakour          #+#    #+#             */
/*   Updated: 2024/05/21 10:39:33 by achakour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	num;
	int	sign;
	int	i;

	num = 0;
	sign = 1;
	i = 0;
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
	while (str[i] >= '0' && str[i] <= '9' && str[i] != '\0')
	{
		num = num * 10 + str[i] - '0';
		++i;
	}
	return (num * sign);
}

int get_args(int ac, char **ar, t_init *pars)
{
    int i;

    i = -1;
    pars->n_eat = 0;
    while (++i < ac)
    {
        if (!ft_check(ar[i]) && ac != 1)
            return (0);
        else if (ac == 2 && pars->n_philo <= 200)
            pars->n_philo = ft_atoi(ar[i]);
        else if (ac == 3)
            pars->tt_die = ft_atoi(ar[i]);
        else if (ac == 4)
            pars->tt_eat = ft_atoi(ar[i]);
        else if (ac == 5)
            pars->tt_sleep = ft_atoi(ar[i]);
        else if (ac == 6)
            pars->n_eat = ft_atoi(ar[i]);
    }
    return (1);
}

void    ft_thinking(t_philo *philas, int index)
{
    int current_time;
    
    printf("%d %d is thinking\n", current_time, index);
    usleep(500000);
}

void    ft_sleeping(t_philo *philas, int index)
{   
    int current_time;

    printf("%d %d is sleeping\n", current_time, index);
    usleep(500000);
}

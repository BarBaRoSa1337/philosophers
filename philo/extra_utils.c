/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakour <achakour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 12:22:59 by achakour          #+#    #+#             */
/*   Updated: 2024/11/10 15:00:23 by achakour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_init *init)
{
	t_philo	**p;
	int		i;

	i = 0;
	p = init->philos;
	while (i < init->n_philo)
	{
		free(p[i]);
		++i;
	}
	free(init->forks);
	free(init);
	free(p);
}

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday()failed\n", 22);
	return ((time.tv_sec * 1000 + time.tv_usec / 1000));
}

int	ft_isalpha(int c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	return (0);
}

int	ft_isnum(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

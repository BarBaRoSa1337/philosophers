/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_guard.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakour <achakour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:56:59 by achakour          #+#    #+#             */
/*   Updated: 2024/10/15 15:12:32 by achakour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_init *p)
{
	pthread_mutex_lock(&p->dead_flag);
	if (p->is_dead == 1)
		return (pthread_mutex_unlock(&p->dead_flag), 1);
	return (pthread_mutex_unlock(&p->dead_flag), 0);
}

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday()failed\n", 22);
	return ((time.tv_sec * 1000 + time.tv_usec / 1000));
}

void	ft_sleep(long time, t_init *s)
{
	long	start;

	start = get_time();
	while (((long)get_time() - start < time) && !is_dead(s))
		;
}

void	life_guarde(t_init *p)
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i < p->n_philo)
		{
			pthread_mutex_lock(&p->philos[i]->l9ess);
			if (get_time()
				- (size_t)p->philos[i]->last_eated > (size_t)p->tt_die)
			{
				pthread_mutex_lock(&p->dead_flag);
				p->is_dead = 1;
				pthread_mutex_unlock(&p->dead_flag);
				printf("%zu %d is dead\n", get_time() - p->t_start, i + 1);
				pthread_mutex_unlock(&p->philos[i]->l9ess);
				break ;
			}
			pthread_mutex_lock(&p->dead_flag);
			if (p->nbr_eating == p->n_philo)
				p->is_dead = 1;
			pthread_mutex_unlock(&p->dead_flag);
			pthread_mutex_unlock(&p->philos[i]->l9ess);
		}
		if (is_dead(p))
			break ;
	}
}

void	print_msg(char *str, int index, t_init *init)
{
	t_init	*p;

	p = init;
	if (is_dead(init))
		return ;
	pthread_mutex_lock(&p->msg);
	printf("%zu %d %s\n", get_time() - p->t_start, index + 1, str);
	pthread_mutex_unlock(&p->msg);
}

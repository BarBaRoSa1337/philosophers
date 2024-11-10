/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakour <achakour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:13:03 by achakour          #+#    #+#             */
/*   Updated: 2024/11/10 12:04:04 by achakour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_eat(t_philo *p)
{
	pthread_mutex_lock(&p->l9ess);
	p->meals++;
	p->last_eated = get_time();
	pthread_mutex_unlock(&p->l9ess);
}

int	ft_eating(int index, t_init *pars)
{
	t_philo	**philo;
	t_init	*p;

	p = pars;
	philo = pars->philos;
	if (lock_the_fork(philo[index], index))
		return (1);
	set_eat(philo[index]);
	print_msg("is eating", index, pars);
	ft_sleep(pars->tt_eat, pars);
	pthread_mutex_lock(&pars->eat_check);
	if (philo[index]->meals != -1 && philo[index]->meals == p->n_eat)
		p->nbr_eating++;
	pthread_mutex_unlock(&pars->eat_check);
	unlock_the_fork(philo[index]);
	return (0);
}

int	ft_sleeping(int index, t_init *pars)
{
	if (is_dead(pars))
		return (1);
	print_msg("is sleeping", index, pars);
	ft_sleep(pars->tt_sleep, pars);
	print_msg("is thinking", index, pars);
	usleep(133);
	return (0);
}

int	lock_the_fork(t_philo *philas, int index)
{
	if (is_dead(philas->init))
		return (1);
	pthread_mutex_lock(philas->l_forchit);
	print_msg("has taken a fork", index, philas->init);
	if (philas->init->n_philo == 1)
		return (1);
	pthread_mutex_lock(philas->r_forchit);
	print_msg("has taken a fork", index, philas->init);
	return (0);
}

void	unlock_the_fork(t_philo *philas)
{
	pthread_mutex_unlock(philas->l_forchit);
	if (philas->init->n_philo > 1)
		pthread_mutex_unlock(philas->r_forchit);
}

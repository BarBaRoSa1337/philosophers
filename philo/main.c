/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakour <achakour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 09:29:50 by achakour          #+#    #+#             */
/*   Updated: 2024/11/17 09:51:06 by achakour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*vita(void *phil)
{
	t_philo	*philas;
	int		index;

	philas = phil;
	index = philas->index;
	if (philas->index % 2)
		usleep(100);
	while (1)
	{
		if (ft_eating(index, philas->init) || ft_sleeping(index, philas->init))
			break ;
		ft_sleep(1, philas->init);
	}
	return (philas);
}

void	creat_philo(t_philo **falasifa, t_init *pars, int i)
{
	int	n_philo;

	n_philo = pars->n_philo;
	pthread_mutex_init(&falasifa[i]->l9ess, NULL);
	falasifa[i]->last_eated = get_time();
	falasifa[i]->index = i;
	falasifa[i]->init = pars;
	if (i % 2)
	{
		falasifa[i]->l_forchit = &pars->forks[(i + 1) % n_philo];
		falasifa[i]->r_forchit = &pars->forks[i];
	}
	else
	{
		falasifa[i]->l_forchit = &pars->forks[i];
		falasifa[i]->r_forchit = &pars->forks[(i + 1) % n_philo];
	}
	falasifa[i]->meals = 0;
}

void	init_philos(t_init *pars)
{
	t_philo	**falasifa;
	int		n_philo;
	int		i;

	i = 0;
	n_philo = pars->n_philo;
	pars->t_start = get_time();
	falasifa = (t_philo **)malloc(sizeof(t_philo *) * n_philo);
	pars->philos = falasifa;
	while (i < n_philo)
	{
		falasifa[i] = malloc(sizeof(t_philo));
		creat_philo(falasifa, pars, i);
		++i;
	}
	i = 0;
	while (i < n_philo)
	{
		pthread_create(&falasifa[i]->tread, NULL, vita, falasifa[i]);
		++i;
	}
	life_guarde(pars);
	i = -1;
	while (++i < n_philo)
		pthread_join(falasifa[i]->tread, NULL);
}

int	main(int ac, char **ar)
{
	t_init	*pars;

	pars = malloc(sizeof(t_init));
	if (!pars)
		return (0);
	if (get_args(ac, ar, pars) || check_num(pars))
		return (free(pars), 1);
	init_forks(pars);
	init_philos(pars);
	return (free_all(pars), 0);
}

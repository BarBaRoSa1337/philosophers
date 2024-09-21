/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakour <achakour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:56:59 by achakour          #+#    #+#             */
/*   Updated: 2024/09/19 10:40:36 by achakour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t get_time(void)
{
	struct timeval	time;

	if(gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday()failed\n", 22);
	return((time.tv_sec * 1000 + time.tv_usec / 1000));
}

void ft_sleep(long time, t_init *s)
{
    long    start;

    start = get_time();
    while (((long)get_time() - start < time) && is_dead(s) != 1);
}

void    kill_philo(t_init *pars)
{
    int i;

    i = 0;
    while (i < pars->n_philo)
    {
        pthread_mutex_lock(&pars->philos[i]->dead);
        pars->philos[i]->is_dead = 1;
        pthread_mutex_unlock(&pars->philos[i]->dead);
        ++i;
    }
}

void    *philo_monitor(void *p)
{
	t_init	*pars;
    int i;
    size_t  time;

	pars = p;
    while (1)
    {
        i = 0;
        while (i < pars->n_philo)
        {
            if (get_time() - pars->philos[i]->t_start >= pars->tt_die)
            {
                time = get_time() - pars->philos[i]->t_start;
                printf("%zu %d is dead\n", time, i);
                kill_philo(pars);
                exit (0);
            }
            ++i;
        }
    }
	return (NULL);
}
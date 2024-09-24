/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakour <achakour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:56:59 by achakour          #+#    #+#             */
/*   Updated: 2024/09/24 17:39:49 by achakour         ###   ########.fr       */
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
    while (((long)get_time() - start < time) && !(s->is_dead));
}

void    life_guarde(t_init *p)
{
	t_init	*pars;
    size_t  time;
    int i;

	pars = p;
    while (1)
    {
        i = 0;
        while (i < pars->n_philo)
        {
            //lock the meal check
            if (get_time() - pars->philos[i]->last_eated >= pars->tt_die)
            {
                time = get_time() - pars->t_start;
                printf("%zu %d is dead\n", time, i);
                pars->is_dead = 1;
            }
            //unlock it
            ++i;
        }
        if (pars->is_dead)
            break ;
    }
}
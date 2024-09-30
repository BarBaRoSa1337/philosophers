/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakour <achakour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:56:59 by achakour          #+#    #+#             */
/*   Updated: 2024/09/25 15:42:46 by achakour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int is_dead(t_init *p)
{
    int tmp;

    tmp = 0;
    pthread_mutex_lock(&p->dead_flag);
    if (p->is_dead == 1)
        tmp = 1;
    pthread_mutex_lock(&p->dead_flag);
    return (tmp);
}

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
    while (((long)get_time() - start < time) && !is_dead(s));
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
            pthread_mutex_lock(&pars->philos[i]->l9ess);
            if (get_time() - pars->philos[i]->last_eated >= pars->tt_die)
            {
                pthread_mutex_lock(&pars->dead_flag);
                pars->is_dead = 1;
                printf("%zu %d is dead\n", get_time() - pars->t_start, i);
                pthread_mutex_unlock(&pars->dead_flag);
            }
            pthread_mutex_unlock(&pars->philos[i]->l9ess);
            ++i;
        }
        if (!is_dead(p))
            break ;
    }
}
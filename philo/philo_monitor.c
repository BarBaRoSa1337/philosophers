/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakour <achakour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:32:52 by achakour          #+#    #+#             */
/*   Updated: 2024/09/04 11:50:20 by achakour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int is_dead(t_init *s)
{
    pthread_mutex_lock(&s->dead);
    if (s->is_dead == 1)
        return (pthread_mutex_unlock(&s->dead), 1);
    else
        return (pthread_mutex_unlock(&s->dead), 0);
}

void    kill_all(t_philo *philo)
{
    int i;
    t_philo *p;

    p = philo;
    while (i < philo->init->n_philo)
    {
        pthread_mutex_unlock(&(p + i)->dead);
        (p + i)->is_dead = 1;
        pthread_mutex_unlock(&(p + i)->dead);
        ++i;
    }
}

void    *check_lives(t_init *init)
{
    t_philo *philo;
    int     i;

    i = 0;
    philo = init->strct_phil;
    while (1)
    {
        if (is_dead(init))
            kill_all(init->strct_phil);
        usleep(1337);
    }
}

void    Im_deaD(t_philo *philo)
{
    int current_time;
    int index;

    pthread_mutex_lock(&(philo->init->dead));
    philo->init->is_dead = 1;
    pthread_mutex_unlock(&(philo->init->dead));
    index = philo->index;
    current_time = get_time() - philo->init->t_start;
    printf("%d %d died\n", current_time, index);
}

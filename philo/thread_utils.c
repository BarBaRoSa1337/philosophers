/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakour <achakour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:56:59 by achakour          #+#    #+#             */
/*   Updated: 2024/05/31 13:27:05 by achakour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t whats_time(void)
{
	struct timeval	time;

	if(gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday()failed\n", 22);
	return(time.tv_sec * 1000 + time.tv_usec / 1000);
}

int Is_alivE(t_init *init)
{
    t_philo *philo;
    int     i;

    philo = init->philas;
    while (i < init->n_philo)
    {
        while (pthread_mutex_lock(philo + i) != 0)
            usleep(1337);
        if ((philo + i)->is_dead == 1)
        {
            pthread_mutex_unlock((philo + i)->is_dead);
            return (1);
        }
        pthread_mutex_unlock((philo + i)->is_dead);
    }
    return (0);
}

void    Im_deaD(t_philo *philo)
{
    int current_time;
    int index;

    while (pthread_mutex_lock(&(philo->init->dead)) != 0)
        usleep(1337);
    philo->init->is_dead = 1;
    pthread_mutex_unlock(&(philo->init->dead));
    index = philo->index;
    current_time = whats_time();
    printf("%d %d died\n", current_time, index);
    exit (0);
}

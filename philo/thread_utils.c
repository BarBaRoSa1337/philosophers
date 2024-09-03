/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakour <achakour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:56:59 by achakour          #+#    #+#             */
/*   Updated: 2024/09/03 18:43:43 by achakour         ###   ########.fr       */
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
    while (get_time() - start < time)
    {
        if (is_dead(s) == 1)
            break ;
    }
}

// int Is_alivE(t_init *init)
// {
//     t_philo *philo;
//     int     i;

//     philo = init->philas;
//     while (i < init->n_philo)
//     {
//         while (pthread_mutex_lock(&(philo + i)->dead) != 0)
//             usleep(1337);
//         if ((philo + i)->is_dead == 1)
//         {
//             pthread_mutex_unlock(&(philo + i)->dead);
//             return (1);
//         }
//         pthread_mutex_unlock(&(philo + i)->dead);
//     }
//     return (0);
// }

void    Im_deaD(t_philo *philo)
{
    int current_time;
    int index;

    pthread_mutex_lock(&(philo->init->dead));
    philo->init->is_dead = 1;
    pthread_mutex_unlock(&(philo->init->dead));
    index = philo->index;
    current_time = get_time();
    printf("%d %d died\n", current_time, index);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakour <achakour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:13:03 by achakour          #+#    #+#             */
/*   Updated: 2024/09/24 17:40:52 by achakour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void    ft_eating(int index, t_init *pars)
{
    size_t current_time;
    t_philo **philo;

    philo = pars->philos;
    current_time = get_time() - pars->t_start;
    printf("%zu %d is eating\n", current_time, index);
    philo[index]->last_eated = get_time();
    philo[index]->meals++;
    lock_the_fork(philo, index);
    ft_sleep(pars->tt_eat, pars);
    unlock_the_fork(philo, index);
}

void    ft_thinking(t_init *pars, int index)
{
    size_t current_time;

    if (is_dead(pars))
        return ;
    current_time = get_time() - pars->t_start;
    printf("%zu %d is thinking\n", current_time, index);
    usleep (133);
}

void    ft_sleeping(int index, t_init *pars)
{
    size_t current_time;

    if (is_dead(pars))
        return ;
    current_time = get_time() - pars->t_start;
    printf("%zu %d is sleeping\n", current_time, index);
    ft_sleep(pars->tt_sleep, pars);
}

void    lock_the_fork(t_philo *philas, int index)
{
    size_t  current_time;

    if (is_dead(philas->init))
        return ;
    current_time = get_time() - philas->init->t_start;
    pthread_mutex_lock(&philas->l_forchit);
    printf("%zu %d has taken a fork\n", current_time, index);
    if (philas->init->n_philo == 1)
        return ;
    pthread_mutex_lock(&philas->r_forchit);
    current_time = get_time() - philas->init->t_start;
    printf("%zu %d has taken a fork\n", current_time, index);
}

void    unlock_the_fork(t_philo *philas, int index)
{
    pthread_mutex_unlock(&philas->l_forchit);
    pthread_mutex_unlock(&philas->r_forchit);
}

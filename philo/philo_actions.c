/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakour <achakour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:13:03 by achakour          #+#    #+#             */
/*   Updated: 2024/09/30 10:16:47 by achakour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    set_eat(t_philo *p)
{
    pthread_mutex_lock(&p->l9ess);
    p->meals++;
    p->last_eated = get_time();
    pthread_mutex_unlock(&p->l9ess);    
}

void    ft_eating(int index, t_init *pars)
{
    size_t current_time;
    t_philo **philo;

    if (is_dead(pars))
        return ;
    philo = pars->philos;
    current_time = get_time() - pars->t_start;
    printf("%zu %d is eating\n", current_time, index);
    set_eat(philo[index]);
    lock_the_fork(philo[index], index);
    ft_sleep(pars->tt_eat, pars);
    unlock_the_fork(philo[index], index);
}

void    ft_thinking(t_init *pars, int index)
{
    if (is_dead(pars))
        return ;
    printf("%zu %d is thinking\n", get_time() - pars->t_start, index);
    usleep (133);
}

void    ft_sleeping(int index, t_init *pars)
{
    if (is_dead(pars))
        return ;
    printf("%zu %d is sleeping\n", get_time() - pars->t_start, index);
    ft_sleep(pars->tt_sleep, pars);
}

void    lock_the_fork(t_philo *philas, int index)
{
    if (is_dead(philas->init))
        return ;
    pthread_mutex_lock(&philas->l_forchit);
    printf("%zu %d has taken a fork\n", get_time() - philas->init->t_start, index);
    if (philas->init->n_philo == 1)
        return ;
    pthread_mutex_lock(&philas->r_forchit);
    printf("%zu %d has taken a fork\n", get_time() - philas->init->t_start, index);
}

void    unlock_the_fork(t_philo *philas, int index)
{
    pthread_mutex_unlock(&philas->l_forchit);
    pthread_mutex_unlock(&philas->r_forchit);
}

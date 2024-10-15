/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakour <achakour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:13:03 by achakour          #+#    #+#             */
/*   Updated: 2024/10/14 12:56:10 by achakour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    set_eat(t_philo *p)
{
    pthread_mutex_lock(&p->l9ess);
    p->meals++;
    p->last_eated = get_time();
    if (p->meals != -1 && p->meals == p->init->n_eat)
        p->init->nbr_eating++;
    pthread_mutex_unlock(&p->l9ess); 
}

void    ft_eating(int index, t_init *pars)
{
    t_philo **philo;

    if (is_dead(pars))
        return ;
    philo = pars->philos;
    lock_the_fork(philo[index], index);
    set_eat(philo[index]);
    print_msg("is eating", index, pars);
    ft_sleep(pars->tt_eat, pars);
    unlock_the_fork(philo[index]);
}

void    ft_thinking(t_init *pars, int index)
{
    if (is_dead(pars))
        return ;
    print_msg("is thinking", index, pars);
    usleep (133);
}

void    ft_sleeping(int index, t_init *pars)
{
    if (is_dead(pars))
        return ;
    print_msg("is sleeping", index, pars);
    ft_sleep(pars->tt_sleep, pars);
}

void    lock_the_fork(t_philo *philas, int index)
{
    if (is_dead(philas->init))
        return ;            
    pthread_mutex_lock(philas->l_forchit);
    print_msg("has taken a fork", index, philas->init);
    if (philas->init->n_philo == 1)
        return ;
    pthread_mutex_lock(philas->r_forchit);
    print_msg("has taken a fork", index, philas->init);
}

void    unlock_the_fork(t_philo *philas)
{
    pthread_mutex_unlock(philas->l_forchit);
    if (philas->init->n_philo > 1)
        pthread_mutex_unlock(philas->r_forchit);
    
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakour <achakour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 09:29:50 by achakour          #+#    #+#             */
/*   Updated: 2024/05/31 13:10:27 by achakour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *vita(void *phil)
{
    t_philo *philas =  (t_philo *)phil;
    int current_time;
    int index;

    index = philas->index;
    current_time = 0;
    while (Is_alivE(philas->init))
    {
        if (philas->meals >= philas->init->n_eat)
            break ;
        lock_the_fork(phil, index, current_time);
        ft_eating(philas->init->tt_eat, index);
        unlock_the_fork(phil, index);
        philas->last_eated = whats_time();
        if (current_time - philas->last_eated > philas->init->tt_die)
            Im_deaD(phil);
        philas->meals++;
        ft_sleeping(philas->init->tt_sleep, index);
        ft_thinking(philas, index);
    }
    return (philas);
}

void    philo_init(t_init *pars)
{
    t_philo     *philosofers;
    int         i;

    i = -1;
    philosofers = malloc(sizeof(t_philo) * pars->n_philo);
    pars->forks = malloc(sizeof(pthread_mutex_t) * pars->n_philo);
    pars->philo = malloc(sizeof(pthread_mutex_t) * pars->n_philo);
    pars->philas = philosofers;
    pars->is_dead = 0;
    while (i < pars->n_philo)
        pthread_mutex_init(&pars->forks[i], NULL);
    i = -1;
    while (++i < pars->n_philo)
    {
        (philosofers + i)->init = pars;
        (philosofers + i)->meals = 0;
        if (pars->n_philo % 2)
            usleep(1337);
        (philosofers + i)->index = i + 1;
        pthread_create(pars->philo + i, NULL, vita, philosofers + i);
    }
    i = -1;
    while (++i < pars->n_philo)
        pthread_join(*(pars->philo + i), NULL);
}

int main(int ac, char **ar)
{
    t_init  *pars;

    pars = malloc(sizeof(t_init));
    if (!pars)
        return (0);
    // if (ac < 5 || !get_args(ac, ar, pars))
    //     return (1);
    get_args(ac , ar, pars);
    philo_init(pars);
    return (0);
}

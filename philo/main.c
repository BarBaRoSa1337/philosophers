/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakour <achakour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 09:29:50 by achakour          #+#    #+#             */
/*   Updated: 2024/05/28 11:52:12 by achakour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    monitoring(t_init *pars)
{
    while (1)
    {
        while (pthread_mutex_lock(&(pars->dead)) != 0)
            usleep(42);
        if (pars->is_dead == 1)
            exit(1);
        pthread_mutex_unlock(&(pars->dead));
    }
}

void    *vita(void *phil)
{
    t_philo *philas =  (t_philo *)phil;
    int current_time;
    int index;

    index = philas->index;
    current_time = 0;
    // current_time = gettimeofday(NULL, NULL);
    int i = 0;
    while (i < 5)
    {
        lock_the_fork(phil, index, current_time);
        ft_eating(philas->init->tt_eat, index);
        unlock_the_fork(phil, index);
        // philas->last_eated = gettimeofday(NULL, NULL);
        philas->meals++;
        ft_sleeping(philas->init->tt_sleep, index);
        ft_thinking(philas, index);
        ++i;
    }
    return (philas);
}

void    philo_init(t_init *pars)
{
    t_philo     *philosofers;
    int         i;

    i = 0;
    philosofers = malloc(sizeof(t_philo) * pars->n_philo);
    pars->forks = malloc(sizeof(pthread_mutex_t) * pars->n_philo);
    pars->philo = malloc(sizeof(pthread_mutex_t) * pars->n_philo);
    pars->philas = philosofers;
    pars->is_dead = 0;
    while (i < pars->n_philo)
    {
        pthread_mutex_init(&pars->forks[i], NULL);
        ++i;
    }
    i = 0;
    // monitoring(pars);
    while (i < pars->n_philo)
    {
        (philosofers + i)->init = pars;
        (philosofers + i)->meals = 0;
        if (pars->n_philo % 2)
            usleep(1337);
        (philosofers + i)->index = i + 1;
        pthread_create(pars->philo + i, NULL, vita, philosofers + i);
        ++i;
    }
    i = 0;
    while (i < pars->n_philo)
    {
        pthread_join(*(pars->philo + i), NULL);
        ++i;
    }
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

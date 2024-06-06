/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakour <achakour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 09:29:50 by achakour          #+#    #+#             */
/*   Updated: 2024/06/06 09:53:36 by achakour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *vita(void *phil)
{
    int     current_time;
    t_philo *philas;
    int     index;

    philas = phil;
    index = philas->index;
    current_time = whats_time(philas->init->t_start);
    // while (Is_alivE(philas->init))
    while(1)
    {
        if (philas->meals >= philas->init->n_eat && philas->init->n_eat != 0)
            break ;
        lock_the_fork(phil, index);
        if (philas->init->n_philo != 1)
        {
            ft_eating(index, philas->init);
            philas->meals++;
            unlock_the_fork(phil, index);
        }
        philas->last_eated = whats_time(philas->init->t_start);
        ft_sleeping(index, philas->init);
        ft_thinking(philas->init, index);
    }
    return (philas);
}

t_philo **init_philos(t_init *pars)
{
    t_philo     **falasifa;
    int         n_philo;
    int         i;

    i = 0;
    n_philo = pars->n_philo;
    pars->t_start = whats_time(0);
    falasifa = (t_philo **)malloc(sizeof(t_philo *) * n_philo);
    while (i < n_philo)
    {
        falasifa[i] = malloc(sizeof(t_philo) * n_philo);
        pthread_mutex_init(&falasifa[i]->dead, NULL);
        falasifa[i]->is_dead = 0;
        falasifa[i]->meals = 0;
        falasifa[i]->init = pars;
        falasifa[i]->index = i + 1;
        falasifa[i]->l_forchit = pars->forks[i];
        falasifa[i]->r_forchit = pars->forks[(i+1) % n_philo];
        ++i;
    }
    i = 0;
    while (i < n_philo)
    {
        pthread_create(&falasifa[i]->tread, NULL, vita, falasifa[i]);
        ++i;
    }
    i = 0;
    while (i < n_philo)
    {
       pthread_join(falasifa[i]->tread, NULL);
       ++i;
    }
    return (falasifa);
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
    pars->forks = init_forks(pars);
    init_philos(pars);
    return (0);
}

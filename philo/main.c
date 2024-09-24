/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakour <achakour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 09:29:50 by achakour          #+#    #+#             */
/*   Updated: 2024/09/24 17:41:59 by achakour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int fih_jo3(t_philo *faylasof)
{
    if ((size_t)faylasof->init->tt_die >= get_time() - faylasof->init->t_start)
        return (1);
    return (0);
}

void    *vita(void *phil)
{
    t_philo *philas;
    int     index;

    philas = phil;
    index = philas->index;
    if (philas->index % 2)
		usleep(15000);
    while(!(philas->init->is_dead))
    {
        ft_eating(index, philas->init);
        //lock meal
        if (philas->meals == philas->init->n_eat && philas->init->n_eat != 0)
        {
            //unlock
            break ;
        }
        //unlock
        ft_sleeping(index, philas->init);
        ft_thinking(philas->init, index);
    }
    return (philas);
}

void    init_philos(t_init *pars)
{
    t_philo     **falasifa;
    int         n_philo;
    int         i;

    i = 0;
    n_philo = pars->n_philo;
    pars->t_start = get_time();
    falasifa = (t_philo **)malloc(sizeof(t_philo *) * n_philo);
    while (i < n_philo)
    {
        falasifa[i] = malloc(sizeof(t_philo) * n_philo);
        falasifa[i]->meals = 0;
        falasifa[i]->init = pars;
        falasifa[i]->index = i + 1;
        falasifa[i]->l_forchit = pars->forks[i];
        falasifa[i]->r_forchit = pars->forks[(i + 1) % n_philo];
        ++i;
    }
    i = -1;
    while (++i < n_philo)
        pthread_create(&falasifa[i]->tread, NULL, vita, falasifa[i]);
    philo_monitor(pars);// the checker
    i = -1;
    while (++i < n_philo)
       pthread_join(falasifa[i]->tread, NULL);
}

int main(int ac, char **ar)
{
    t_init  *pars;

    // if (ac < 5 || !get_args(ac, ar, pars))
    //     return (1);
    pars = malloc(sizeof(t_init));
    if (!pars)
        return (0);
    get_args(ac , ar, pars);
    pars->forks = init_forks(pars);
    init_philos(pars);
    return (0);
}

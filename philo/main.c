/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakour <achakour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 09:29:50 by achakour          #+#    #+#             */
/*   Updated: 2024/05/21 11:00:57 by achakour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    monitoring(t_philo *philas)
{
    int i;
    int current_time;

    while (1)
    {
        i = 0;
        while (i < philas->init->n_philo)
        {
            while (pthread_mutex_lock(&((philas + i)->dead)) != 0)
                usleep(42);
            if ((philas + i)->last_eated - current_time >= (philas + i)->init->tt_die)
            {
                pthread_mutex_unlock(&((philas + i)->dead));
                printf("philo has dead\n");
                exit(0);
            }
            pthread_mutex_unlock(&((philas + i)->dead));
            ++i;
        }
    }
}

void    vita(t_philo *philas)
{
    int current_time;
    int index;

    index = philas->index;
    current_time = gettimeofday(NULL, NULL);
    while (is_alive(philas) && philas->meals < philas->init->n_eat)
    {
        lock_the_fork(philas + index, index, current_time);
        ft_eating(philas);
        unlock_the_fork(philas + index, index);
        philas->last_eated = gettimeofday(NULL, NULL);
        philas->meals++;
        ft_sleeping(philas, index);
        ft_thinking(philas, index);
    }
}

void    philo_init(t_init *pars)
{
    pthread_t   monitor;
    t_philo     *philosofers;
    int         i;

    i = 0;
    philosofers = malloc(sizeof(t_philo) * pars->n_philo);
    pars->forks = malloc(sizeof(pthread_mutex_t) * pars->n_philo);
    pars->philo = malloc(sizeof(pthread_mutex_t) * pars->n_philo);
    pars->philas = philosofers;
    while (i < pars->n_philo)
    {
        pthread_mutex_init(&pars->forks[i], NULL);
        (philosofers + i)->last_eated = 0;
        (philosofers + i)->init = pars;
        (philosofers + i)->meals = 0;
        if (pars->n_philo % 2 == 0)
            usleep(1337);
        philosofers->index = i;
        pthread_create(pars->philo + i, NULL, vita, philosofers + i);
        ++i;
    }
    pthread_create(&monitor, NULL, monitoring, philosofers);
}

int main(int ac, char **ar)
{
    t_init  *pars;

    pars = malloc(sizeof(t_init));
    if (!pars)
        return (NULL);
    if (ac < 5 || !get_args(ac, ar, pars))
        return (1);
    philo_init(pars);
    return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakour <achakour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 09:29:50 by achakour          #+#    #+#             */
/*   Updated: 2024/05/20 10:18:58 by achakour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    vita(t_philo *philas)
{
    while (is_alive(philas) && is_full(philas))
    {
        ft_eating(philas);
        ft_sleeping(philas);
        ft_thinking(philas);
    }
}

void    philo_init(t_init *pars)
{
    t_philo *philosofers;
    int     i;

    i = 0;
    philosofers = malloc(sizeof(t_philo));
    pars->forks = malloc(sizeof(pthread_mutex_t) * pars->n_philo);
    pars->philo = malloc(sizeof(pthread_mutex_t) * pars->n_philo);
    while (i < pars->n_philo)
    {
        pthread_mutex_init(&pars->forks[i], NULL);
        (philosofers + i)->init = pars;
        pthread_create(pars->philo + i, NULL, vita, philosofers);
        ++i;
    }
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

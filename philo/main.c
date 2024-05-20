/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakour <achakour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 09:29:50 by achakour          #+#    #+#             */
/*   Updated: 2024/05/20 09:17:20 by achakour         ###   ########.fr       */
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

void    philo(t_init pars)
{
    pthread_t *philas;
    pthread_mutex_t fork;
    int i;

    i = 0;
    while (i < pars.n_philo)
    {
        // pthread_mutex_init(philas[i]->forks, NULL);
        pthread_create(&philas[i], NULL, &vita, NULL);
        ++i;
    }
}

int main(int ac, char **ar)
{
    t_init  pars;

    if (ac < 5 || !get_args(ac, ar, pars))
        return (1);
    philo(pars);
    return (0);
}

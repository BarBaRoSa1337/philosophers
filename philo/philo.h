/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakour <achakour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 09:26:47 by achakour          #+#    #+#             */
/*   Updated: 2024/05/20 09:59:54 by achakour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <pthread.h>

typedef struct s_init
{
   int  tt_sleep;
   int  n_philo;
   int  tt_die;
   int  tt_eat;
   int  n_eat;
   pthread_mutex_t  *forks;
}       t_init;

typedef struct s_philo
{
    pthread_mutex_t right_fork;
    pthread_mutex_t left_fork;
    int             t_start;
    int             phil_n;
    t_init          *init;
}                   t_philo;

int     ft_atoi(const char *str);
int     get_args(int ac, char **ar, t_init *pars);
void    ft_thinking(t_philo *philas);
void    ft_sleeping(t_philo *philas);

#endif
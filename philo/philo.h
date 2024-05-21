/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakour <achakour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 09:26:47 by achakour          #+#    #+#             */
/*   Updated: 2024/05/21 11:00:52 by achakour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_philo t_philo;

typedef struct s_init
{
   int  tt_sleep;
   int  n_philo;
   int  tt_die;
   int  tt_eat;
   int  n_eat;
   int  t_start;
   pthread_mutex_t  dead;
   pthread_mutex_t  *forks;
   pthread_t        *philo;
   t_philo          *philas;
}       t_init;

typedef struct s_philo
{
    pthread_mutex_t right_fork;
    pthread_mutex_t left_fork;
    pthread_mutex_t dead;
    t_init          *init;
    int             index;
    int             last_eated;
    int             meals;
}                   t_philo;

int     ft_atoi(const char *str);
int     get_args(int ac, char **ar, t_init *pars);
void    ft_thinking(t_philo *philas, int index);
void    ft_sleeping(t_philo *philas, int index);
void    lock_the_fork(t_philo *philas, int index, int current_time);
void    unlock_the_fork(t_philo *philas, int index);

#endif
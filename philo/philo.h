/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakour <achakour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 09:26:47 by achakour          #+#    #+#             */
/*   Updated: 2024/06/05 10:07:15 by achakour         ###   ########.fr       */
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

typedef struct      s_philo t_philo;

typedef struct      s_init
{
   int              tt_sleep;
   int              n_philo;
   int              tt_die;
   int              tt_eat;
   int              n_eat;
   size_t              t_start;
   _Atomic int      is_dead;
   pthread_mutex_t  dead;
   pthread_mutex_t  *forks;
   t_philo        **philos;
   t_philo          *strct_phil;
}                   t_init;

typedef struct      s_philo
{
    pthread_mutex_t r_forchit;
    pthread_mutex_t l_forchit;
    t_init          *init;
    pthread_mutex_t dead;
    _Atomic int     is_dead;
    int             index;
    int         last_eated;
    int             meals;
    pthread_t        tread;
}                   t_philo;

void    lock_the_fork(t_philo *philas, int index);
void    unlock_the_fork(t_philo *philas, int index);
int     get_args(int ac, char **ar, t_init *pars);
void    ft_thinking(t_init *pars, int index);
void    ft_sleeping(int index, t_init *pars);
void    ft_eating(int index, t_init *pars);
int     ft_atoi(const char *str);
size_t whats_time(size_t t_start);
void    Im_deaD(t_philo *philo);
pthread_mutex_t *init_forks(t_init *pars);
// int Is_alivE(t_init *init);

#endif
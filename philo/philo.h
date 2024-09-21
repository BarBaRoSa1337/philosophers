/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakour <achakour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 09:26:47 by achakour          #+#    #+#             */
/*   Updated: 2024/09/19 10:47:08 by achakour         ###   ########.fr       */
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
   long              tt_sleep;
   long              n_philo;
   long              tt_die;
   long              tt_eat;
   long              n_eat;
   pthread_mutex_t  dead;
   pthread_mutex_t  *forks;
   t_philo        **philos;
   _Atomic int      is_dead;
   ssize_t              t_start;
}                   t_init;

typedef struct      s_philo
{
    pthread_mutex_t r_forchit;
    pthread_mutex_t l_forchit;
    t_init          *init;
    long             last_eated;
    int             index;
    int             meals;
    long             t_start;
    pthread_t        tread;
    pthread_mutex_t    dead;
    _Atomic int     is_dead;
}                   t_philo;

void    *philo_monitor(void *p);
pthread_mutex_t         *init_forks(t_init *pars);
void    lock_the_fork(t_philo *philas, int index);
void    unlock_the_fork(t_philo *philas, int index);
short int     get_args(int ac, char **ar, t_init *pars);
void    ft_thinking(t_init *pars, int index);
void    ft_sleeping(int index, t_init *pars);
void    ft_eating(int index, t_init *pars);
int     ft_atoi(const char *str);
void    Im_deaD(t_philo *philo);
short int     is_dead(t_init *s);
void    *check_lives(t_init *init);
size_t  get_time(void);
void    ft_sleep(long time, t_init *s);

#endif
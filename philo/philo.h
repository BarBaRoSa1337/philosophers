/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakour <achakour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 09:26:47 by achakour          #+#    #+#             */
/*   Updated: 2024/11/10 14:56:19 by achakour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo	t_philo;

typedef struct s_init
{
	long				tt_sleep;
	long				n_philo;
	long				tt_die;
	long				tt_eat;
	long				n_eat;
	int					nbr_eating;
	t_philo				**philos;
	pthread_mutex_t		eat_check;	
	pthread_mutex_t		*forks;
	pthread_mutex_t		dead_flag;
	pthread_mutex_t		msg;
	int					is_dead;
	ssize_t				t_start;
}						t_init;

typedef struct s_philo
{
	pthread_mutex_t		*r_forchit;
	pthread_mutex_t		*l_forchit;
	t_init				*init;
	long				last_eated;
	int					index;
	int					meals;
	pthread_mutex_t		l9ess;
	pthread_t			tread;
}						t_philo;

void					print_msg(char *str, int index, t_init *init);
short int				get_args(int ac, char **ar, t_init *pars);
int						lock_the_fork(t_philo *philas, int index);
int						ft_sleeping(int index, t_init *pars);
int						ft_eating(int index, t_init *pars);
void					unlock_the_fork(t_philo *philas);
void					ft_sleep(long time, t_init *s);
void					init_forks(t_init *pars);
void					free_all(t_init *init);
int						ft_atoi(const char *str);
void					life_guarde(t_init *p);
short int				check_num(t_init *p);
int						is_dead(t_init *p);
int						ft_isalpha(int c);
int						ft_isnum(int c);
size_t					get_time(void);

#endif
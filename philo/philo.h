/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 09:19:52 by anfouger          #+#    #+#             */
/*   Updated: 2026/01/22 08:19:28 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_data
{
	long			nb_philo;
	long			time_sleep;
	long			time_die;
	long			time_eat;
	long			must_eat;
	long			is_running;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t run_mutex;
} t_data;

typedef struct s_philo
{
	long		id;
	long		last_meal;
	long		nb_meal;
	t_data		*data;
	pthread_mutex_t *fork_l;
	pthread_mutex_t *fork_r;
	pthread_mutex_t	meal_mutex;
}				t_philo;

typedef struct s_monitor
{
	t_data		*data;
	t_philo		*philo;
}				t_monitor;


// --- Parsing --- //
int		verif_arg(int ac, char **av);

// --- Utils --- //
long	ft_atol(char *s);
int		is_run(t_data *data);
void	print_state(char *s, t_philo *philo);
void	clean_exit(t_data *data, pthread_t *threads, t_philo *philos);

// --- Time --- //
long	timestamp_ms(void);
void	precise_sleep(long ms);

// --- Init --- //
void	init_data(t_data *data, int ac, char **av);
void	init_philos(pthread_t *threads, t_philo *philo, t_data *data);

// --- Routine --- //
void	*routine_philo(void *arg);
void	*routine_even(t_philo *philo);
void	*routine_odd(t_philo *philo);

#endif
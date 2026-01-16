/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 09:19:52 by anfouger          #+#    #+#             */
/*   Updated: 2026/01/16 08:41:11 by anfouger         ###   ########.fr       */
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
	long nb_philo;
	long time_sleep;
	long time_die;
	long time_eat;
	long must_eat;
	pthread_mutex_t *fork_mutex;
} t_data;

typedef struct s_thread
{
	pthread_t	thread;
	long		last_meal;
	long		nb_meal;
} t_thread;

// --- Parsing --- //
int		verif_arg(int ac, char **av);
long	ft_atol(char *s);

// --- Init --- //
void	init_data(t_data *data, int ac, char **av);
void	init_threads(pthread_t *threads, int *ids, int n);

// --- Problem --- //
void	*routine(void *arg);

#endif
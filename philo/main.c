/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 09:19:20 by anfouger          #+#    #+#             */
/*   Updated: 2026/01/22 09:32:04 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
	t_data		*data;
	pthread_t	*threads;
	t_philo		*philo;
	t_monitor	*monitor;
	int	i;
	
	if (!verif_arg(ac, av))
		return (1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	data->fork_mutex = malloc(sizeof(pthread_mutex_t) * ft_atol(av[1]));
	if (!data->fork_mutex)
		return (1);
	init_data(data, ac, av);
	threads = malloc(sizeof(pthread_t) * (data->nb_philo + 1));
	philo = malloc(sizeof(t_philo) * data->nb_philo);
	monitor = malloc(sizeof(t_monitor));
	if (!threads || !philo || !monitor)
	{
		clean_exit(data, threads, philo, monitor);
		return (1);
	}
	init_philos(threads, philo, data);
	init_monitor(data, philo, monitor, threads);
	join_all(threads, data);
	clean_exit(data, threads, philo, monitor);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 09:19:20 by anfouger          #+#    #+#             */
/*   Updated: 2026/01/23 11:06:05 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data		*data;
	pthread_t	*threads;
	t_philo		*philo;
	t_monitor	*monitor;

	if (!verif_arg(ac, av))
		return (1);
	if (!init_memory(&data, &threads, &philo, av))
		return (1);
	monitor = malloc(sizeof(t_monitor));
	data->fork_mutex = malloc(sizeof(pthread_mutex_t) * ft_atol(av[1]));
	if (!data->fork_mutex || !monitor)
	{
		clean_exit(data, threads, philo, monitor);
		return (1);
	}
	init_data(data, ac, av);
	init_philos(threads, philo, data);
	init_monitor(data, philo, monitor, threads);
	join_all(threads, data);
	clean_exit(data, threads, philo, monitor);
	return (0);
}

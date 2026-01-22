/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 09:19:20 by anfouger          #+#    #+#             */
/*   Updated: 2026/01/22 08:42:10 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
	t_data	*data;
	pthread_t *threads;
	t_philo		*philo;
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
	threads = malloc(sizeof(pthread_t) * data->nb_philo);
	philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!threads || !philo)
	{
		clean_exit(data, threads, philo);
		return (1);
	}
	init_philos(threads, philo, data);
	clean_exit(data, threads, philo);
	return (0);
}

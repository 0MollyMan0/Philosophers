/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 09:19:20 by anfouger          #+#    #+#             */
/*   Updated: 2026/01/21 08:31:32 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Delete when project done
static void	print_data(t_data *data)
{
	printf("number of philosophers = %ld\n", data->nb_philo);
	printf("time to die = %ld\n", data->time_die);
	printf("time to eat = %ld\n", data->time_eat);
	printf("time to sleep = %ld\n", data->time_sleep);
	printf("number of times philosophers must eat = %ld\n", data->must_eat);
}

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
	print_data(data); // Delete when project done
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

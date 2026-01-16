/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 09:19:20 by anfouger          #+#    #+#             */
/*   Updated: 2026/01/16 11:56:46 by anfouger         ###   ########.fr       */
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
	init_data(data, ac, av);
	print_data(data); // Delete when project done
	threads = malloc(sizeof(pthread_t) * data->nb_philo);
	if (!threads)
		return ;
	philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!philo)
		return ;
	init_threads(&threads, &philo, data->nb_philo);
	return (0);
}

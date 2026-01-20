/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 09:37:47 by anfouger          #+#    #+#             */
/*   Updated: 2026/01/20 10:02:35 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	init_data(t_data *data, int ac, char **av)
{
	data->nb_philo = atol(av[1]);
	data->time_die = atol(av[2]);
	data->time_eat = atol(av[3]);
	data->time_sleep = atol(av[4]);
	data->is_running = 1;
	pthread_mutex_init(&data->print_mutex, NULL);
	if (ac == 6)
		data->must_eat = atol(av[5]);
	else
		data->must_eat = -1;
}

void	init_philos(pthread_t *threads, t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		philo[i].id = i;
		philo[i].data = data;
		philo[i].nb_meal = 0;
		pthread_create(&threads[i], NULL, routine, &philo[i]);
		philo[i].thread = &threads[i];
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(*philo[i].thread, NULL);
		i++;
	}
}

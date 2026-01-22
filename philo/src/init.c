/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 09:37:47 by anfouger          #+#    #+#             */
/*   Updated: 2026/01/22 08:08:30 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	init_data(t_data *data, int ac, char **av)
{
	long	i;
	
	i = 0;
	data->nb_philo = atol(av[1]);
	data->time_die = atol(av[2]);
	data->time_eat = atol(av[3]);
	data->time_sleep = atol(av[4]);
	data->is_running = 1;
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&data->fork_mutex[i], NULL);	
		i++;
	}
	pthread_mutex_init(&data->run_mutex, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
	if (ac == 6)
		data->must_eat = atol(av[5]);
	else
		data->must_eat = -1;
}

static void	join_philos(pthread_t *threads, t_data *data)
{
	long	i;
	
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

void	init_philos(pthread_t *threads, t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		philo[i].id = i;
		philo[i].data = data;
		if (data->must_eat == -1)
			philo[i].nb_meal = -2;
		philo[i].last_meal = timestamp_ms();
		pthread_mutex_init(&philo[i].meal_mutex, NULL);
		philo[i].fork_l = &data->fork_mutex[i];
		if (i+1 == data->nb_philo)
			philo[i].fork_r = &data->fork_mutex[0];
		else
			philo[i].fork_r = &data->fork_mutex[i+1];
		if (philo[i].id % 2 == 0)
			pthread_create(&threads[i], NULL, routine_philo, &philo[i]);
		else
			pthread_create(&threads[i], NULL, routine_philo, &philo[i]);
		i++;
	}
	join_philos(threads, data);
}

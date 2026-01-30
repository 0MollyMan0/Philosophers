/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 09:37:47 by anfouger          #+#    #+#             */
/*   Updated: 2026/01/30 13:55:35 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	init_data(t_data *data, int ac, char **av)
{
	long	i;

	i = 0;
	data->nb_philo = ft_atol(av[1]);
	data->time_die = ft_atol(av[2]);
	data->time_eat = ft_atol(av[3]);
	data->time_sleep = ft_atol(av[4]);
	data->is_running = 1;
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&data->fork_mutex[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->run_mutex, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
	if (ac == 6)
		data->must_eat = ft_atol(av[5]);
	else
		data->must_eat = -1;
}

void	init_philos(pthread_t *threads, t_philo *philo, t_data *data)
{
	int		i;
	long	start;

	i = 0;
	start = timestamp_ms();
	while (i < data->nb_philo)
	{
		philo[i].id = i + 1;
		philo[i].data = data;
		philo[i].nb_meal = 0;
		philo[i].last_meal = start;
		pthread_mutex_init(&philo[i].meal_mutex, NULL);
		pthread_mutex_init(&philo[i].nb_meal_mutex, NULL);
		philo[i].fork_l = &data->fork_mutex[i];
		if (i + 1 == data->nb_philo)
			philo[i].fork_r = &data->fork_mutex[0];
		else
			philo[i].fork_r = &data->fork_mutex[i + 1];	
		pthread_create(&threads[i], NULL, routine_philo, &philo[i]);
		i++;
	}
}

void	init_monitor(t_data *d, t_philo *p, t_monitor *m, pthread_t *t)
{
	m->data = d;
	m->philo = p;
	pthread_create(&t[d->nb_philo], NULL, routine_monitor, m);
}

int	init_memory(t_data **d, pthread_t **t, t_philo **p, char **av)
{
	*d = malloc(sizeof(t_data));
	*t = malloc(sizeof(pthread_t) * (ft_atol(av[1]) + 1));
	*p = malloc(sizeof(t_philo) * ft_atol(av[1]));
	if (!*t || !*p || !*d)
	{
		clean_exit(*d, *t, *p, NULL);
		return (0);
	}
	return (1);
}

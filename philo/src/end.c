/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 11:10:30 by anfouger          #+#    #+#             */
/*   Updated: 2026/01/23 12:01:07 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	is_philo_full(t_philo *philo, t_data *data)
{
	int	full;

	full = 0;
	pthread_mutex_lock(&philo->nb_meal_mutex);
	if (data->must_eat != -1 && philo->nb_meal >= data->must_eat)
		full = 1;
	pthread_mutex_unlock(&philo->nb_meal_mutex);
	return (full);
}


int	is_philos_full(t_philo *philo, t_data *data)
{
	long	i;

	if (data->must_eat == -1)
		return (0);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_lock(&philo[i].nb_meal_mutex);
		if (philo[i].nb_meal < data->must_eat)
		{
			pthread_mutex_unlock(&philo[i].nb_meal_mutex);
			return (0);
		}
		pthread_mutex_unlock(&philo[i].nb_meal_mutex);
		i++;
	}
	pthread_mutex_lock(&data->run_mutex);
	data->is_running = 0;
	pthread_mutex_unlock(&data->run_mutex);
	return (1);
}

int	is_run(t_data *data)
{
	pthread_mutex_lock(&data->run_mutex);
	if (data->is_running)
	{
		pthread_mutex_unlock(&data->run_mutex);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&data->run_mutex);
		return (0);
	}
}

void	clean_exit(t_data *d, pthread_t *t, t_philo *p, t_monitor *m)
{
	long	i;

	i = 0;
	if (d)
	{
		if (d->fork_mutex)
			free(d->fork_mutex);
		pthread_mutex_destroy(&d->print_mutex);
		free(d);
	}
	if (t)
		free(t);
	if (p)
		free(p);
	if (m)
		free(m);
}
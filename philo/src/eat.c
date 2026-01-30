/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 14:20:40 by anfouger          #+#    #+#             */
/*   Updated: 2026/01/30 16:06:26 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

long	get_last_meal(t_philo *philo)
{
	long	res;

	pthread_mutex_lock(&philo->meal_mutex);
	res = philo->last_meal;
	pthread_mutex_unlock(&philo->meal_mutex);
	return (res);
}

int	can_i_eat(t_data *data)
{
	pthread_mutex_lock(&data->nb_eat_mutex);
	if (data->nb_eat < data->nb_philo - 1)
	{
		data->nb_eat++;
		pthread_mutex_unlock(&data->nb_eat_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->nb_eat_mutex);
	return (0);
}

void	done_eating(t_data *data)
{
	pthread_mutex_lock(&data->nb_eat_mutex);
	data->nb_eat--;
	pthread_mutex_unlock(&data->nb_eat_mutex);
}

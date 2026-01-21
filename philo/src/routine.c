/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 08:39:20 by anfouger          #+#    #+#             */
/*   Updated: 2026/01/21 09:02:48 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*routine_odd(void *arg)
{
	t_philo *philo;
	
	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("Thread %ld doing is routine\n", philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
	while (philo->data->is_running && philo->nb_meal < philo->data->must_eat)
	{
			pthread_mutex_lock(philo->fork_r);
			pthread_mutex_lock(philo->fork_l);
			pthread_mutex_lock(&philo->meal_mutex);
			philo->last_meal = timestamp_ms();
			pthread_mutex_unlock(&philo->meal_mutex);
			precise_sleep(philo->data->time_eat);
			pthread_mutex_unlock(philo->fork_l);
			pthread_mutex_unlock(philo->fork_r);
			precise_sleep(philo->data->time_sleep);	
	}
	return (NULL);
}

void	*routine_even(void *arg)
{
	t_philo *philo;
	
	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("Thread %ld doing is routine\n", philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
	while (philo->data->is_running && philo->nb_meal < philo->data->must_eat)
	{
			pthread_mutex_lock(philo->fork_l);
			pthread_mutex_lock(philo->fork_r);
			pthread_mutex_lock(&philo->meal_mutex);
			philo->last_meal = timestamp_ms();
			pthread_mutex_unlock(&philo->meal_mutex);
			precise_sleep(philo->data->time_eat);
			pthread_mutex_unlock(philo->fork_r);
			pthread_mutex_unlock(philo->fork_l);
			precise_sleep(philo->data->time_sleep);
	}
	return (NULL);
}

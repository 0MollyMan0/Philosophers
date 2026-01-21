/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 08:39:20 by anfouger          #+#    #+#             */
/*   Updated: 2026/01/21 09:25:40 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*routine_odd(void *arg)
{
	t_philo *philo;
	
	philo = (t_philo *)arg;
	while (philo->data->is_running && philo->nb_meal < philo->data->must_eat)
	{
		print_state("is thinking", philo);
		pthread_mutex_lock(philo->fork_r);
		print_state("has taken a fork", philo);
		pthread_mutex_lock(philo->fork_l);
		pthread_mutex_lock(&philo->meal_mutex);
		print_state("is eating", philo);
		philo->last_meal = timestamp_ms();
		philo->nb_meal++;
		pthread_mutex_unlock(&philo->meal_mutex);
		precise_sleep(philo->data->time_eat);
		pthread_mutex_unlock(philo->fork_l);
		pthread_mutex_unlock(philo->fork_r);
		print_state("is thinking", philo);
		precise_sleep(philo->data->time_sleep);
	}
	print_state("died", philo);
	return (NULL);
}

void	*routine_even(void *arg)
{
	t_philo *philo;
	
	philo = (t_philo *)arg;
	while (philo->data->is_running && philo->nb_meal < philo->data->must_eat)
	{
		print_state("is thinking", philo);
		pthread_mutex_lock(philo->fork_l);
		print_state("has taken a fork", philo);
		pthread_mutex_lock(philo->fork_r);
		pthread_mutex_lock(&philo->meal_mutex);
		print_state("is eating", philo);
		philo->last_meal = timestamp_ms();
		philo->nb_meal++;
		pthread_mutex_unlock(&philo->meal_mutex);
		precise_sleep(philo->data->time_eat);
		pthread_mutex_unlock(philo->fork_r);
		pthread_mutex_unlock(philo->fork_l);
		print_state("is thinking", philo);
		precise_sleep(philo->data->time_sleep);
	}
	print_state("died", philo);
	return (NULL);
}

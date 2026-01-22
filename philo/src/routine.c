/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 08:39:20 by anfouger          #+#    #+#             */
/*   Updated: 2026/01/22 08:39:58 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*routine_philo(void *arg)
{
	t_philo *philo;
	
	philo = (t_philo *)arg;
	while (is_run(philo->data) 
		&& (philo->nb_meal < philo->data->must_eat 
		|| philo->data->must_eat == -1))
	{
		print_state("is thinking", philo);
		if (philo->id % 2 == 0)
			routine_even(philo);
		else
			routine_odd(philo);
		print_state("is sleeping", philo);
		precise_sleep(philo->data->time_sleep);
	}
	return (NULL);
}

void	*routine_odd(t_philo *philo)
{
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
	return (NULL);
}

void	*routine_even(t_philo *philo)
{
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
	return (NULL);
}

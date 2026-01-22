/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 08:39:20 by anfouger          #+#    #+#             */
/*   Updated: 2026/01/22 13:36:58 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*routine_monitor(void *arg)
{
	long		i;
	long		last;
	t_monitor	*moni;

	moni = (t_monitor *)arg;
	while (is_run(moni->data))
	{
		i = 0;
		while (i < moni->data->nb_philo)
		{
			last = get_last_meal(&moni->philo[i]);
			if (timestamp_ms() - last > moni->data->time_die)
			{
				pthread_mutex_lock(&moni->data->run_mutex);
				moni->data->is_running = 0;
				pthread_mutex_unlock(&moni->data->run_mutex);
				print_died(&moni->philo[i]);
				break ;
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

static void	routine_odd(t_philo *philo)
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
}

static void	routine_even(t_philo *philo)
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
}

void	*routine_philo(void *arg)
{
	t_philo	*philo;

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

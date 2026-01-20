/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 08:39:20 by anfouger          #+#    #+#             */
/*   Updated: 2026/01/20 15:09:58 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*routine(void *arg)
{
	t_philo *philo;
	
	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("Thread %ld doing is routine\n", philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
	while (&philo->data->is_running)
	{
		
	}
	sleep(1);
	return (NULL);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:05:19 by anfouger          #+#    #+#             */
/*   Updated: 2026/01/21 08:32:13 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	clean_exit(t_data *data, pthread_t *threads, t_philo *philo)
{
	long	i;

	i = 0;
	if (data)
	{
		if (data->fork_mutex)
			free(data->fork_mutex);
		pthread_mutex_destroy(&data->print_mutex);
		free(data);
	}
	if (threads)
		free(threads);
	if (philo)
		free(philo);
}

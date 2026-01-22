/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 09:06:21 by anfouger          #+#    #+#             */
/*   Updated: 2026/01/22 09:21:37 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	join_all(pthread_t *threads, t_data *data)
{
	long	i;
	
	i = 0;
	while (i < data->nb_philo + 1)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

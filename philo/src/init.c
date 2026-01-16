/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 09:37:47 by anfouger          #+#    #+#             */
/*   Updated: 2026/01/16 08:41:38 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	init_data(t_data *data, int ac, char **av)
{
	data->nb_philo = atol(av[1]);
	data->time_die = atol(av[2]);
	data->time_eat = atol(av[3]);
	data->time_sleep = atol(av[4]);
	if (ac == 6)
		data->must_eat = atol(av[5]);
	else
		data->must_eat = -1;	
}

void	init_threads(pthread_t *threads, int *ids, int n)
{
	int	i;
	
	threads = malloc(sizeof(pthread_t) * n);
	if (!threads)
		return ;
	ids = malloc(sizeof(int) * n);
	if (!ids)
	{
		free(threads);
		return ;	
	}
	i = 0;
	while (i < n)
	{
		ids[i] = i;
		pthread_create(&threads[i], NULL, routine, &ids[i]);
		i++;
	}
}
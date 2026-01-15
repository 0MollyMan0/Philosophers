/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 09:19:20 by anfouger          #+#    #+#             */
/*   Updated: 2026/01/15 09:48:35 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
	t_data	*data;
	int		*error;
	
	if (!verif_arg(ac, av))
		return (1);
	data = malloc(sizeof(t_data));
	init_data(data, ac, av);
	printf("number of philosophers = %ld\n", data->nb_philo);
	printf("time to die = %ld\n", data->time_die);
	printf("time to eat = %ld\n", data->time_eat);
	printf("time to sleep = %ld\n", data->time_sleep);
	printf("number of times philosophers must eat = %ld\n", data->must_eat);
	return (0);
}

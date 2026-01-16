/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 08:39:20 by anfouger          #+#    #+#             */
/*   Updated: 2026/01/16 10:40:09 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	printf("Thread %d doing is routine", philo->id);
	return (NULL);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exo.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 10:47:51 by anfouger          #+#    #+#             */
/*   Updated: 2026/01/13 11:27:14 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t	m = PTHREAD_MUTEX_INITIALIZER;

void	*thread_a(void *arg)
{
	(void)arg;
	while (1)
	{
		pthread_mutex_lock(&m);
		printf(".");
		usleep(1000);
		pthread_mutex_unlock(&m);
		usleep(100);
	}
	return NULL;
}

void	*thread_b(void *arg)
{
	(void)arg;
	while (1)
	{
		pthread_mutex_lock(&m);
		printf("\nThread b got the mutex\n");
		pthread_mutex_unlock(&m);
		usleep(100000);
	}
	return NULL;
}

int	main(void)
{
	pthread_t	t_a, t_b;

	pthread_create(&t_a, NULL, thread_a, NULL);
	pthread_create(&t_b, NULL, thread_b, NULL);

	pthread_join(t_a, NULL);
	pthread_join(t_b, NULL);
	return 0;
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exo.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 10:47:51 by anfouger          #+#    #+#             */
/*   Updated: 2026/01/13 10:46:21 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t	m1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t	m2 = PTHREAD_MUTEX_INITIALIZER;

void	*thread1(void *arg)
{
	(void)arg;
	pthread_mutex_lock(&m1);
	printf("Thread 1 locked m1\n");
	pthread_mutex_lock(&m2);
	printf("Thread 1 locked m2\n");
	pthread_mutex_unlock(&m2);
	printf("Thread 1 unlocked m2\n");
	pthread_mutex_unlock(&m1);
	printf("Thread 1 unlocked m1\n");
	return NULL;
}

void	*thread2(void *arg)
{
	(void)arg;
	pthread_mutex_lock(&m1);
	printf("Thread 2 locked m1\n");
	pthread_mutex_lock(&m2);
	printf("Thread 2 locked m2\n");
	pthread_mutex_unlock(&m2);
	printf("Thread 2 unlocked m2\n");
	pthread_mutex_unlock(&m1);
	printf("Thread 2 unlocked m1\n");
	return NULL;
}

int	main(void)
{
	pthread_t	t1, t2;

	pthread_create(&t1, NULL, thread1, NULL);
	pthread_create(&t2, NULL, thread2, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	return 0;
}


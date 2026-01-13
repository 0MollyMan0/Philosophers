/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exo.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 10:47:51 by anfouger          #+#    #+#             */
/*   Updated: 2026/01/13 09:11:25 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int counter = 0;

void	*routine(void *arg)
{
	(void)arg;
	int tmp;
	
	tmp = counter;
	usleep(1);
	counter = tmp + 1;
	return (NULL);
}

int main(int ac, char **av)
{
	int n;
	int i;
	pthread_t *threads;
	
	if (ac != 2)
		return (1);
	n = atoi(av[1]);
	threads = malloc(sizeof(pthread_t) * n);
	if (!threads)
		return (1);
	i = 0;
	while (i < n)
	{
		pthread_create(&threads[i], NULL, routine, NULL);
		i++;
	}
	i = 0;
	while (i < n)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	printf("counter = %d", counter);
	return (0);
}

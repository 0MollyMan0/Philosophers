/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exo.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 10:47:51 by anfouger          #+#    #+#             */
/*   Updated: 2026/01/12 11:06:34 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void	*routine(void *arg)
{
	int id = *(int *)arg;
	printf("Hello from thread %d\n", id);
	return (NULL);
}

int main(int ac, char **av)
{
	int n;
	int i;
	pthread_t *threads;
	int *ids;
	
	if (ac != 2)
		return (1);
	n = atoi(av[1]);
	threads = malloc(sizeof(pthread_t) * n);
	if (!threads)
		return (1);
	ids = malloc(sizeof(int) * n);
	if (!ids)
	{
		free(threads);
		return (1);	
	}
	i = 0;
	while (i < n)
	{
		ids[i] = i;
		pthread_create(&threads[i], NULL, routine, &ids[i]);
		i++;
	}
	i = 0;
	while (i < n)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	return (0);
}

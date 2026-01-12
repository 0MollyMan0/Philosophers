/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exo.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 10:47:51 by anfouger          #+#    #+#             */
/*   Updated: 2026/01/12 14:18:00 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	*routine(void *arg)
{
	(void)arg;
	return ((void *)42);
}

int main(int ac, char **av)
{
	int n;
	int i;
	void *res;
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
		pthread_join(threads[i], &res);
		printf("Returned value of Thread %d: %ld\n", i, (long)res);
		i++;
	}
	return (0);
}

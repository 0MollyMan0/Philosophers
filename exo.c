/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exo.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 10:47:51 by anfouger          #+#    #+#             */
/*   Updated: 2026/01/13 10:27:20 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_data
{
	int counter;
	pthread_mutex_t mutex;
} t_data;

void	*routine(void *arg)
{
	t_data	*data = (t_data *)arg;
	pthread_mutex_lock(&data->mutex);
	usleep(1);
	data->counter++;
	pthread_mutex_unlock(&data->mutex);
	return (NULL);
}

int main(int ac, char **av)
{
	int n;
	int i;
	pthread_t *threads;
	t_data	*data;

	if (ac != 2)
		return (1);
	n = atoi(av[1]);

	threads = malloc(sizeof(pthread_t) * n);
	if (!threads)
		return (1);

	data = malloc(sizeof(t_data));
	if (!data)
	{
		free(threads);
		return (1);
	}
	data->counter = 0;
	pthread_mutex_init(&data->mutex, NULL);

	i = 0;
	while (i < n)
		pthread_create(&threads[i++], NULL, routine, data);

	i = 0;
	while (i < n)
		pthread_join(threads[i++], NULL);

	printf("counter = %d", data->counter);
	free(threads);
	pthread_mutex_destroy(&data->mutex);
	free(data);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 07:14:34 by anfouger          #+#    #+#             */
/*   Updated: 2026/01/23 11:49:10 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	print_state(char *s, t_philo *philo)
{
	if (is_run(philo->data) && !is_philo_full(philo, philo->data))
	{
		pthread_mutex_lock(&philo->data->print_mutex);
		if (is_run(philo->data))
			printf("%ld %ld %s\n", timestamp_ms(), philo->id, s);
		pthread_mutex_unlock(&philo->data->print_mutex);
	}
}

void	print_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%ld %ld died\n", timestamp_ms(), philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

long	ft_atol(char *s)
{
	long	result;
	int		i;

	result = 0;
	i = 0;
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	while (s[i] >= '0' && s[i] <= '9')
	{
		result = result * 10 + (s[i] - '0');
		i++;
	}
	return (result);
}

long	get_last_meal(t_philo *philo)
{
	long	res;

	pthread_mutex_lock(&philo->meal_mutex);
	res = philo->last_meal;
	pthread_mutex_unlock(&philo->meal_mutex);
	return (res);
}

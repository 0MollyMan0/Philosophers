/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 13:10:03 by anfouger          #+#    #+#             */
/*   Updated: 2026/01/23 10:44:37 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static long	verif_max_long(char *s)
{
	long	result;
	int		i;

	result = 0;
	i = 0;
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	while (s[i] >= '0' && s[i] <= '9')
	{
		if (result > (LONG_MAX - (s[i] - '0')) / 10)
			return (0);
		result = result * 10 + (s[i] - '0');
		i++;
	}
	if (s[i] != '\0')
		return (0);
	return (result);
}

static int	verif_number(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

int	verif_arg(int ac, char **av)
{
	int	i;

	if (!(ac >= 5 && ac <= 6))
		return (0);
	i = 1;
	while (i < ac)
	{
		if (!verif_number(av[i]) || !verif_max_long(av[i]))
			return (0);
		i++;
	}
	return (1);
}

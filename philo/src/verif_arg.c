/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 13:10:03 by anfouger          #+#    #+#             */
/*   Updated: 2026/01/14 10:09:27 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	verif_number(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (0);
}

int	verif_arg(int ac, char **av)
{
	int i;
	
	if (ac != 4 || ac != 5)
		return (1);
	i = 1;
	while (i < ac)
	{
		if (!verif_number(av[i]))
		{
			
		}
		
	}
	
	
}

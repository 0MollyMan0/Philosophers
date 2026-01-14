/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 13:10:03 by anfouger          #+#    #+#             */
/*   Updated: 2026/01/14 10:32:17 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int	verif_number(char *s)
{
	int	i;

	i = 0;
	printf("%s", "enter in function verif nb\n");
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
	
	printf("%s", "enter in function verif arg\n");
	if (ac < 3 || ac > 4)
		return (0);
	printf("%s", "pass first test\n");
	i = 1;
	while (i < ac)
	{
		if (!verif_number(av[i]))
			return (0);
		printf("Arg %d is good", i);
		i++;
	}
	return (1);
}

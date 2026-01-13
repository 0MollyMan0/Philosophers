/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exo.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 10:47:51 by anfouger          #+#    #+#             */
/*   Updated: 2026/01/13 11:49:53 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// typedef struct timeval {
// 	time_t		tv_sec;
// 	suseconds_t	tv_usec;
// }	timeval;

int	main(int ac, char **av)
{
	struct timeval	*tv;
	int			tmp_sec;
	int			tmp_usec;
	int			n;
	int			i;
	
	if (ac != 2)
		return (1);
	tv = malloc(sizeof(struct timeval));
	n = atoi(av[1]);
	i = 0;
	gettimeofday(tv, NULL);
	tmp_sec = tv->tv_sec;
	tmp_usec = tv->tv_usec;
	while (i < n)
	{
		gettimeofday(tv, NULL);
		printf("sec = %ld | milsec = %ld | dif sec = %ld | dif milsec = %ld\n", tv->tv_sec, tv->tv_usec, tv->tv_sec - tmp_sec, tv->tv_usec - tmp_usec);
		tmp_sec = tv->tv_sec;
		tmp_usec = tv->tv_usec;
		usleep(1000);
		i++;
	}
	return (0);
}


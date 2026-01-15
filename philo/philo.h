/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 09:19:52 by anfouger          #+#    #+#             */
/*   Updated: 2026/01/15 09:48:55 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <threads.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_data
{
	long nb_philo;
	long time_sleep;
	long time_die;
	long time_eat;
	long must_eat;
} t_data;

// --- Parsing --- //
int		verif_arg(int ac, char **av);
long	ft_atol(char *s);
void	init_data(t_data *data, int ac, char **av);
#endif
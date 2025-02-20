/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:17:26 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/20 15:42:13 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int long	ft_gettimeofday(void)
{
	struct timeval	cur;

	gettimeofday(&cur, NULL);
	return ((cur.tv_sec * 1000) + (cur.tv_usec / 1000));
}

char	ft_usleep(long time, t_philo *philo)
{
	int long	start;

	start = ft_gettimeofday();
	while (1)
	{
		if (check_dead(philo))
			return (1);
		if ((ft_gettimeofday() - start) >= time)
			break ;
		usleep(1);
	}
	return (0);
}

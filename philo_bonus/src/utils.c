/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 01:14:33 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/15 01:02:24 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_atoi(char *str)
{
	int long	res;
	int			i;

	if (!str[0])
		return (-1);
	i = 0;
	res = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		res = res * 10 + (str[i++] - '0');
		if (res > 2147483647 || res < -2147483648)
			return (-1);
	}
	return (res);
}

int long	ft_gettimeofday(void)
{
	struct timeval	cur;

	gettimeofday(&cur, NULL);
	return ((cur.tv_sec * 1000) + (cur.tv_usec / 1000));
}

char	ft_usleep(int time, t_philo *philo)
{
	int long	start;

	start = ft_gettimeofday();
	while (1)
	{
		if (check_stop(philo))
			return (1);
		if ((ft_gettimeofday() - start) >= time)
			return (0);
		usleep(5);
	}
	return (0);
}

char	check_stop(t_philo *philo)
{
	char	res;

	res = 0;
	sem_wait(&philo->lock);
	if (philo->stop || philo->dead)
		res++;
	sem_post(&philo->lock);
	return (res);
}

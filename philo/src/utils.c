/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:32:06 by gakarbou          #+#    #+#             */
/*   Updated: 2025/01/29 15:37:26 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long int	time_diff(struct timeval start)
{
	struct timeval	cur;
	double			a;
	double			b;

	b = start.tv_usec / 1000;
	gettimeofday(&cur, NULL);
	a = cur.tv_usec / 1000 + (1000 * (cur.tv_sec - start.tv_sec));
	return (a - b);
}

int	ft_errors(int code, char res)
{
	if (code == 0)
		return (res);
	else if (code == 1)
		write(2, "Invalid arguments number\n", 25);
	else
		write(2, "Error\n", 6);
	return (res);
}

int	ft_atoi(char *str)
{
	int	i;
	int	res;

	if (!str[0])
		return (-1);
	res = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		res = res * 10 + (str[i++] - '0');
	}
	return (res);
}

char	check_dead(t_philo *philo)
{
	char	res;

	res = 0;
	pthread_mutex_lock(&philo->misc->printf);
	if (philo->dead || philo->misc->stop)
		res = 1;
	pthread_mutex_unlock(&philo->misc->printf);
	return (res);
}

int	print_status(int code, t_philo *philo)
{
	pthread_mutex_lock(&philo->misc->printf);
	printf("%ld %d ", time_diff(philo->misc->start), philo->id);
	if (code == 1)
		printf("has taken a fork\n");
	else if (code == 2)
		printf("is eating\n");
	else if (code == 3)
		printf("is sleeping\n");
	else if (code == 4)
		printf("is thinking\n");
	else
		printf("idk\n");
	pthread_mutex_unlock(&philo->misc->printf);
	return (1);
}

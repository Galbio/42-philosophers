/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:32:06 by gakarbou          #+#    #+#             */
/*   Updated: 2025/01/29 22:57:33 by gakarbou         ###   ########.fr       */
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
	else if (code == 3)
		write(2, "Invalid number of philo\n", 24);
	else if (code == 4)
		write(2, "Invalid time to die\n", 20);
	else if (code == 5)
		write(2, "Invalid time to eat\n", 20);
	else if (code == 6)
		write(2, "Invalid sleep time\n", 19);
	else if (code == 7)
		write(2, "Invalid minimum meal count\n", 27);
	else if (code == 8)
		write(2, "Too many arguments\n", 19);
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

char	*ft_strdup(char *str)
{
	char	*dest;
	int		i;

	if (!str[0])
		ft_strdup("GoodTry");
	if (str[0] == '\\' && str[1])
		str++;
	i = -1;
	while (str[++i])
		;
	dest = malloc(sizeof(char) * (i + 1));
	if (!dest)
		return (NULL);
	i = -1;
	while (str[++i])
		dest[i] = str[i];
	dest[i] = 0;
	return (dest);
}

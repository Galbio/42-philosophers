/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:32:06 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/04 22:32:11 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long int	time_diff(struct timeval start)
{
	struct timeval	cur;
	double			a;
	double			b;

	b = start.tv_usec;
	gettimeofday(&cur, NULL);
	a = cur.tv_usec + (1000000 * (cur.tv_sec - start.tv_sec));
	return (a - b);
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
	pthread_mutex_lock(&philo->misc->lock);
	if (philo->dead || philo->misc->stop)
		res = 1;
	pthread_mutex_unlock(&philo->misc->lock);
	return (res);
}

char	*ft_strdup(char *str)
{
	char	*dest;
	int		i;

	if (!str[0])
		return (ft_strdup("GoodTry"));
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

void	free_all(t_main *op)
{
	int	i;

	i = -1;
	while (op->use_name && ++i < op->infos->nb_philo)
	{
		free(op->philos[i].name);
		pthread_mutex_destroy(&op->misc->forks[i]);
	}
	pthread_mutex_destroy(&op->misc->printf);
	pthread_mutex_destroy(&op->misc->fork);
	pthread_mutex_destroy(&op->misc->meal);
	pthread_mutex_destroy(&op->misc->lock);
	free(op->infos);
	free(op->misc->forks);
	free(op->misc);
	free(op->philos);
}

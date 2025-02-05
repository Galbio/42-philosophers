/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:32:06 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/05 00:46:34 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

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

void	print_status(t_philo *philo, char code)
{
	sem_wait(philo->misc->printf);
	if (code == 1)
		printf("%d took a fork\n", philo->id);
	else if (code == 2)
		printf("%d is eating\n", philo->id);
	sem_post(philo->misc->printf);
}

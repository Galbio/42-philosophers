/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:17:26 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/18 20:39:07 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int long	ft_gettimeofday(void)
{
	struct timeval	cur;

	gettimeofday(&cur, NULL);
	return ((cur.tv_sec * 1000) + (cur.tv_usec / 1000));
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
	else if (code == 9)
		write(2, "Not enough arguments\n", 21);
	else
		write(2, "Error\n", 6);
	return (res);
}

void	ft_putcolor(int code)
{
	if (code == 0)
		printf("%s", RESET);
	else if (code == 2)
		printf("%s", YELLOW);
	else if (code == 3)
		printf("%s", BLUE);
	else if (code == 4)
		printf("%s", CYAN);
	else if (code == 5)
		printf("%s", RED);
	else if (code == 1)
		printf("%s", GREY);
}

int	print_status(int code, t_philo *philo)
{
	pthread_mutex_lock(&philo->misc->printf);
	if (BONUS)
		ft_putcolor(code);
	if (!philo->misc->use_name)
		printf("%ld %i ", ft_gettimeofday() - philo->misc->start, philo->id);
	else
		printf("%ld %s ", ft_gettimeofday() - philo->misc->start, philo->name);
	if (code == 1)
		printf("has taken a fork\n");
	else if (code == 2)
		printf("is eating\n");
	else if (code == 3)
		printf("is sleeping\n");
	else if (code == 4)
		printf("is thinking\n");
	else if (code == 5)
		printf("died\n");
	else
		printf("idk\n");
	if (BONUS)
		printf("%s", RESET);
	pthread_mutex_unlock(&philo->misc->printf);
	return (1);
}

char	ft_usleep(long time, t_philo *philo)
{
	int long	start;

	(void)philo;
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

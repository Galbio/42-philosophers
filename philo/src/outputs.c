/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outputs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:17:26 by gakarbou          #+#    #+#             */
/*   Updated: 2025/01/30 17:18:28 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

int	print_status(int code, t_philo *philo)
{
	pthread_mutex_lock(&philo->misc->printf);
	if (!philo->misc->use_name)
		printf("%ld %i ", time_diff(philo->misc->start), philo->id);
	else
		printf("%ld %s ", time_diff(philo->misc->start), philo->name);
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
	pthread_mutex_unlock(&philo->misc->printf);
	return (1);
}

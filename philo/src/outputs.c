/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outputs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:35:04 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/20 16:00:59 by gakarbou         ###   ########.fr       */
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

void	print_status_head(t_philo *philo, int long time, int code)
{
	if (BONUS)
		ft_putcolor(code);
	if (philo->misc->use_name)
		printf("%ld %s ", time, philo->name);
	else
		printf("%ld %d ", time, philo->id);
}

int	print_status(int code, t_philo *philo, int long time)
{
	pthread_mutex_lock(&philo->misc->printf);
	time -= philo->misc->start;
	print_status_head(philo, time, code);
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

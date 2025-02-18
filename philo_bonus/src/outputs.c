/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outputs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:29:53 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/17 17:54:27 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

char	ft_errors(int code)
{
	if (code == 1)
		write(2, "Invalid philo number\n", 21);
	else if (code == 2)
		write(2, "Invalid time to die\n", 20);
	else if (code == 3)
		write(2, "Invalid time to eat\n", 20);
	else if (code == 4)
		write(2, "Invalid time to sleep\n", 22);
	else if (code == 5)
		write(2, "Invalid nb of meals\n", 20);
	else if (code == 7)
		write(2, "Errors while creating forks\n", 29);
	else if (code == 8)
		write(2, "Semaphore error\n", 16);
	else if (code == 9)
		write(2, "Memory error\n", 13);
	else if (code == 10)
		write(2, "Invalid argc\n", 13);
	return (1);
}

void	ft_putcolor(char code)
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

void	print_status(t_philo *philo, char code)
{
	int long	date;

	date = ft_gettimeofday() - philo->misc->start_time;
	if (BONUS)
		ft_putcolor(code);
	sem_wait(philo->misc->printf);
	if (check_stop(philo))
	{
		sem_post(philo->misc->printf);
		return ;
	}
	printf("%ld %d ", date, philo->id);
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
	sem_post(philo->misc->printf);
}

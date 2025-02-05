/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:32:39 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/05 00:14:09 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	wait_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->misc->forks[philo->forks[0]]);
	philo->fork_hold++;
	pthread_mutex_lock(&philo->misc->lock);
	if (philo->dead || philo->misc->stop)
		return (pthread_mutex_unlock(&philo->misc->lock));
	else if (philo->forks[0] == philo->forks[1])
	{
		pthread_mutex_unlock(&philo->misc->lock);
		return (print_status(1, philo));
	}
	pthread_mutex_unlock(&philo->misc->lock);
	print_status(1, philo);
	pthread_mutex_lock(&philo->misc->forks[philo->forks[1]]);
	philo->fork_hold++;
	if (check_dead(philo))
		return (0);
	return (print_status(1, philo));
}

char	unlock_forks(t_philo *philo)
{
	if (!philo->fork_hold)
		return (1);
	pthread_mutex_unlock(&philo->misc->forks[philo->forks[0]]);
	philo->fork_hold--;
	if (!philo->fork_hold)
		return (1);
	pthread_mutex_unlock(&philo->misc->forks[philo->forks[1]]);
	philo->fork_hold--;
	return (1);
}

char	routine_loop(t_philo *philo)
{
	wait_forks(philo);
	if (check_dead(philo) || philo->fork_hold != 2)
		return (unlock_forks(philo));
	print_status(2, philo);
	pthread_mutex_lock(&philo->misc->meal);
	gettimeofday(&philo->last_meal, NULL);
	pthread_mutex_unlock(&philo->misc->meal);
	ft_usleep(philo->misc->infos->time_eat * 1000);
	pthread_mutex_lock(&philo->misc->meal);
	philo->nb_meal++;
	pthread_mutex_unlock(&philo->misc->meal);
	unlock_forks(philo);
	if (check_dead(philo))
		return (1);
	print_status(3, philo);
	ft_usleep(philo->misc->infos->time_sleep * 1000);
	if (check_dead(philo))
		return (1);
	print_status(4, philo);
	return (0);
}

void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id == philo->misc->infos->nb_philo)
		usleep(500);
	while (!check_dead(philo))
		if (routine_loop(philo))
			break ;
	return (NULL);
}

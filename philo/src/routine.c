/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:32:39 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/20 16:00:42 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	wait_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->forks[0]);
	philo->fork_hold++;
	pthread_mutex_lock(&philo->misc->lock);
	if (philo->dead || philo->misc->stop)
		return (pthread_mutex_unlock(&philo->misc->lock));
	else if (philo->misc->infos->nb_philo == 1)
	{
		pthread_mutex_unlock(&philo->misc->lock);
		return (print_status(1, philo, ft_gettimeofday()));
	}
	pthread_mutex_unlock(&philo->misc->lock);
	print_status(1, philo, ft_gettimeofday());
	pthread_mutex_lock(philo->forks[1]);
	philo->fork_hold++;
	if (check_dead(philo))
		return (0);
	return (print_status(1, philo, ft_gettimeofday()));
}

char	unlock_forks(t_philo *philo)
{
	if (!philo->fork_hold)
		return (1);
	pthread_mutex_unlock(philo->forks[0]);
	philo->fork_hold--;
	if (!philo->fork_hold)
		return (1);
	pthread_mutex_unlock(philo->forks[1]);
	philo->fork_hold--;
	return (1);
}

char	routine_loop(t_philo *philo)
{
	char	res;

	print_status(4, philo, ft_gettimeofday());
	wait_forks(philo);
	if (check_dead(philo) || philo->fork_hold != 2)
		return (unlock_forks(philo));
	print_status(2, philo, ft_gettimeofday());
	pthread_mutex_lock(&philo->meal);
	philo->last_meal = ft_gettimeofday();
	pthread_mutex_unlock(&philo->meal);
	res = ft_usleep(philo->misc->infos->time_eat, philo);
	if (res)
		return (unlock_forks(philo), 1);
	unlock_forks(philo);
	pthread_mutex_lock(&philo->meal);
	philo->nb_meal++;
	pthread_mutex_unlock(&philo->meal);
	if (check_dead(philo))
		return (1);
	print_status(3, philo, ft_gettimeofday());
	res = ft_usleep(philo->misc->infos->time_sleep, philo);
	if (res)
		return (1);
	return (0);
}

void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	pthread_mutex_lock(&philo->meal);
	philo->last_meal = ft_gettimeofday();
	pthread_mutex_unlock(&philo->meal);
	while (!check_dead(philo))
		if (routine_loop(philo))
			break ;
	pthread_mutex_destroy(&philo->meal);
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:15:14 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/15 00:02:04 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	post_forks(t_philo *philo)
{
	if (!philo->fork_hold)
		return ;
	sem_post(philo->misc->forks);
	philo->fork_hold--;
	if (!philo->fork_hold)
		return ;
	sem_post(philo->misc->forks);
	philo->fork_hold--;
}

char	take_forks(t_philo *philo)
{
	sem_wait(philo->misc->forks);
	philo->fork_hold++;
	if (check_stop(philo))
		return (1);
	print_status(philo, 1);
	if (philo->infos.nb_philo == 1)
		return (1);
	sem_wait(philo->misc->forks);
	philo->fork_hold++;
	if (check_stop(philo))
		return (1);
	print_status(philo, 1);
	return (0);
}

char	routine_loop(t_philo *philo)
{
	print_status(philo, 4);
	if (take_forks(philo))
		return (post_forks(philo), 1);
	print_status(philo, 2);
	sem_wait(&philo->meal);
	philo->last_meal = ft_gettimeofday();
	sem_post(&philo->meal);
	if (ft_usleep(philo->infos.time_eat, philo))
		return (post_forks(philo), 1);
	post_forks(philo);
	sem_wait(&philo->meal);
	philo->nb_meal++;
	sem_post(&philo->meal);
	print_status(philo, 3);
	if (ft_usleep(philo->infos.time_sleep, philo))
		return (1);
	return (0);
}

void	*routine_init(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2)
		usleep(300);
	while (1)
		if (routine_loop(philo))
			break ;
	return (NULL);
}

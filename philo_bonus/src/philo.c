/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 02:45:42 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/15 01:03:38 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	check_end(t_philo *philo)
{
	sem_wait(philo->misc->stop);
	sem_post(philo->misc->stop);
	sem_wait(&philo->lock);
	philo->stop = 1;
	sem_post(&philo->lock);
}

void	check_meals(t_philo *philo)
{
	static char	posted = 0;

	if (philo->infos.nb_meal <= 0)
		return ;
	if (philo->nb_meal == philo->infos.nb_meal && !posted)
	{
		posted++;
		sem_post(philo->misc->meals);
	}
}

void	give_dead_meal(t_philo *philo)
{
	if (philo->infos.nb_meal <= 0)
		return ;
	sem_wait(&philo->meal);
	if (philo->nb_meal <= philo->infos.nb_meal)
		sem_post(philo->misc->meals);
	sem_post(&philo->meal);
}

void	*check_death(void *ptr)
{
	t_philo		*philo;
	int long	diff;

	philo = (t_philo *)ptr;
	while (1)
	{
		if (check_stop(philo))
			return (give_dead_meal(philo), NULL);
		sem_wait(&philo->meal);
		diff = ft_gettimeofday() - philo->last_meal;
		check_meals(philo);
		sem_post(&philo->meal);
		if (!philo->dead && diff > philo->infos.time_die)
		{
			print_status(philo, 5);
			sem_post(philo->misc->stop);
			sem_wait(&philo->lock);
			philo->dead++;
			sem_post(&philo->lock);
		}
		usleep(10);
	}
	return (NULL);
}

void	init_process(t_philo *philo)
{
	pthread_t	routine;
	pthread_t	checker;

	philo->dead = 0;
	sem_init(&philo->meal, 0, 1);
	sem_init(&philo->lock, 0, 1);
	sem_wait(philo->misc->start);
	sem_post(philo->misc->start);
	philo->misc->start_time = ft_gettimeofday();
	philo->last_meal = ft_gettimeofday();
	pthread_create(&routine, NULL, routine_init, philo);
	pthread_create(&checker, NULL, check_death, philo);
	check_end(philo);
	pthread_join(checker, NULL);
	pthread_join(routine, NULL);
	if (philo->infos.nb_meal > 0)
		sem_close(philo->misc->meals);
	(sem_close(philo->misc->start), sem_close(philo->misc->stop));
	(sem_close(philo->misc->printf), sem_close(philo->misc->forks));
	return ;
}

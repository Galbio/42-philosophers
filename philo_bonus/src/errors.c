/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 02:39:55 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/21 13:57:24 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	destroy_forks(t_main *op, int nb)
{
	int		i;

	i = -1;
	while (++i < nb)
		kill(op->pids[i], SIGKILL);
}

void	valgrind_friendly_sem(t_philo *philo)
{
	int		i;

	i = -1;
	while ((philo->infos.nb_meal > 0) && (++i < philo->infos.nb_philo))
		sem_wait(philo->misc->meals);
	sem_wait(philo->misc->start);
	sem_wait(philo->misc->stop);
}

void	destroy_sem(t_main *op)
{
	sem_close(op->misc->forks);
	sem_close(op->misc->printf);
	sem_close(op->misc->start);
	sem_close(op->misc->stop);
	sem_close(op->misc->meals);
	sem_unlink("/forks");
	sem_unlink("/printf");
	sem_unlink("/start");
	sem_unlink("/stop");
	sem_unlink("/meals");
}

void	free_all(t_main *op)
{
	int		i;

	i = -1;
	while (++i < op->infos.nb_philo && op->use_name)
		free(op->philos[i].name);
	if (op->infos.nb_meal > 0)
		sem_close(op->misc->meals);
	(sem_close(op->misc->start), sem_close(op->misc->stop));
	(sem_close(op->misc->printf), sem_close(op->misc->forks));
	free(op->misc);
	free(op->pids);
	free(op->philos);
}

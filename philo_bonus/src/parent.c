/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 02:43:24 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/21 20:59:22 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*collect_meals(void *ptr)
{
	t_main	*op;
	int		i;

	op = (t_main *)ptr;
	if (op->infos.nb_meal <= 0)
		return (NULL);
	i = -1;
	while (++i < op->infos.nb_philo)
		sem_wait(op->misc->meals);
	sem_post(op->misc->stop);
	return (NULL);
}

void	parent_process(t_main *op)
{
	int			i;
	pthread_t	meals;

	i = -1;
	usleep(500);
	pthread_create(&meals, NULL, collect_meals, op);
	sem_post(op->misc->start);
	while (++i < op->infos.nb_philo)
		waitpid(-1, NULL, 0);
	pthread_join(meals, NULL);
	if (op->infos.nb_meal > 0)
		(sem_close(op->misc->meals), sem_unlink("/meals"));
	i = -1;
	while (++i < op->infos.nb_philo && op->use_name)
		free(op->philos[i].name);
	(sem_close(op->misc->printf), sem_close(op->misc->start));
	(sem_close(op->misc->forks), sem_close(op->misc->stop));
	(sem_unlink("/start"), sem_unlink("/stop"), sem_unlink("/forks"));
	(sem_unlink("/printf"), free(op->pids), free(op->misc), free(op->philos));
}

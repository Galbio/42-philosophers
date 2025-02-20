/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 02:08:35 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/19 18:21:58 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

char	init_sem(t_main *op)
{
	op->misc->forks = sem_open("/forks", O_CREAT, 0600, op->infos.nb_philo);
	if (op->misc->forks == SEM_FAILED)
		return (ft_errors(8));
	op->misc->printf = sem_open("/printf", O_CREAT, 0600, 1);
	if (op->misc->printf == SEM_FAILED)
		return (destroy_sem(op), ft_errors(8));
	op->misc->start = sem_open("/start", O_CREAT, 0600, 1);
	if (op->misc->start == SEM_FAILED)
		return (destroy_sem(op), ft_errors(8));
	op->misc->stop = sem_open("/stop", O_CREAT, 0600, 1);
	if (op->misc->stop == SEM_FAILED)
		return (destroy_sem(op), ft_errors(8));
	if (op->infos.nb_meal < 0)
		return (0);
	op->misc->meals = sem_open("/meals", O_CREAT, 0600, op->infos.nb_philo);
	if (op->misc->meals == SEM_FAILED)
		return (destroy_sem(op), ft_errors(8));
	return (0);
}

char	init_philos(t_main *op, char **argv)
{
	int		i;

	i = -1;
	while (++i < op->infos.nb_philo)
	{
		if (op->use_name)
			op->philos[i].name = ft_strdup(argv[i]);
		op->philos[i].stop = 0;
		op->philos[i].id = i + 1;
		op->philos[i].nb_meal = 0;
		op->philos[i].fork_hold = 0;
		op->philos[i].infos = op->infos;
		op->philos[i].misc = op->misc;
	}
	return (0);
}

void	close_sem(void)
{
	sem_unlink("/forks");
	sem_unlink("/stop");
	sem_unlink("/start");
	sem_unlink("/printf");
	sem_unlink("/meals");
}

char	init_op(t_main *op, char **argv)
{
	t_philo	*philos;
	pid_t	*pids;
	t_misc	*misc;

	philos = malloc(sizeof(t_philo) * op->infos.nb_philo);
	if (!philos)
		return (ft_errors(9));
	pids = malloc(sizeof(pid_t) * op->infos.nb_philo);
	if (!pids)
		return (free(philos), ft_errors(9));
	misc = malloc(sizeof(t_misc));
	if (!misc)
		return (free(philos), free(pids), ft_errors(9));
	misc->use_name = op->use_name;
	op->misc = misc;
	close_sem();
	if (init_sem(op))
		return (free(philos), free(pids), 1);
	op->philos = philos;
	op->pids = pids;
	return (init_philos(op, argv));
}

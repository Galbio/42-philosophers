/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 02:39:55 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/12 17:41:11 by gakarbou         ###   ########.fr       */
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

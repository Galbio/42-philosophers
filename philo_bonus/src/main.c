/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 00:34:45 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/14 23:34:06 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

char	create_forks(t_main *op)
{
	pid_t	pid;
	int		i;

	i = -1;
	while ((op->infos.nb_meal > 0) && (++i < op->infos.nb_philo))
		sem_wait(op->misc->meals);
	i = -1;
	sem_wait(op->misc->start);
	sem_wait(op->misc->stop);
	while (++i < op->infos.nb_philo)
	{
		pid = fork();
		if (pid < 0)
			return (destroy_forks(op, i), ft_errors(7));
		else if (!pid)
		{
			init_process(&op->philos[i]);
			(free(op->misc), free(op->pids), free(op->philos));
			exit(0);
		}
		else
			op->pids[i] = pid;
	}
	parent_process(op);
	return (0);
}

int	main(int argc, char **argv)
{
	t_main	op;

	if (argc < 5 || argc > 6)
		return (ft_errors(10));
	if (init_infos(&op, argv + 1, argc == 6))
		return (1);
	create_forks(&op);
}

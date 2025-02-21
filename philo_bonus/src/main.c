/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 00:34:45 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/21 18:02:48 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

char	create_forks(t_main *op)
{
	pid_t	pid;
	int		i;

	i = -1;
	while (++i < op->infos.nb_philo)
	{
		pid = fork();
		if (pid < 0)
			return (destroy_forks(op, i), ft_errors(7));
		else if (!pid)
			(init_process(&op->philos[i], i), free_all(op), exit(0));
		else
			op->pids[i] = pid;
	}
	parent_process(op);
	return (0);
}

char	init_infos(t_main *op, char **argv, int argc)
{
	t_infos	infos;
	char	error;

	error = 0;
	infos.nb_philo = ft_atoi(argv[0]);
	if (infos.nb_philo <= 0)
		error += ft_errors(1);
	infos.time_die = ft_atoi(argv[1]);
	if (infos.time_die <= 0)
		error += ft_errors(2);
	infos.time_eat = ft_atoi(argv[2]);
	if (infos.time_eat <= 0)
		error += ft_errors(3);
	infos.time_sleep = ft_atoi(argv[3]);
	if (infos.time_sleep <= 0)
		error += ft_errors(4);
	infos.nb_meal = -1;
	if (argc == 6)
		infos.nb_meal = ft_atoi(argv[4]);
	if ((argc == 6) && (infos.nb_meal <= 0))
		error += ft_errors(5);
	if (error)
		return (1);
	return (op->infos = infos, init_op(op, argv));
}

int	main(int argc, char **argv)
{
	t_main	op;

	if (argc < 5 || argc > 6)
		return (ft_errors(10));
	op.use_name = 0;
	if (init_infos(&op, argv + 1, argc))
		return (1);
	op.misc->end_loop = 1;
	create_forks(&op);
	return (0);
}

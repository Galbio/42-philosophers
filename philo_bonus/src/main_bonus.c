/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 00:34:45 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/18 21:39:50 by gakarbou         ###   ########.fr       */
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

void	check_endloop(char *loop, int *argc, char **argv)
{
	const char	*flag = "--no-stop";
	int			i;

	i = -1;
	while (flag[++i] && argv[*argc - 1][i])
		if (flag[i] != argv[*argc - 1][i])
			return ;
	(*argc)--;
	*loop = 0;
}

void	handle_names(t_main *op, char ***argv, int *argc, t_infos *infos)
{
	infos.nb_philo = ft_atoi(argv[0][0]);
	if (infos.nb_philo <= 0)
		return (ft_errors(1));
	return (0);
}

char	init_infos(t_main *op, char **argv, int argc)
{
	t_infos	infos;
	char	error;

	error = handle_names(op, &argv, &argc, &infos);
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
	return (op->infos = infos, init_op(op));
}

int	main(int argc, char **argv)
{
	t_main	op;
	char	end_loop;

	if (argc < 5)
		return (ft_errors(10));
	end_loop = 1;
	check_endloop(&end_loop, &argc, argv);
	if (init_infos(&op, argv + 1, argc - 1))
		return (1);
	op.misc->end_loop = end_loop;
	create_forks(&op);
	return (0);
}

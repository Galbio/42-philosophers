/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:30:45 by gakarbou          #+#    #+#             */
/*   Updated: 2025/01/29 22:53:46 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	get_nb_philo(int argc, char **argv, t_main *op)
{
	int	res;
	int	i;

	res = 0;
	i = -1;
	while (++i < argc)
	{
		if (argv[i][0] >= '0' && argv[i][0] <= '9')
		{
			if (!i)
				return (ft_atoi(argv[0]));
			op->use_name = 1;
			break ;
		}
		res++;
	}
	op->use_name = 1;
	return (res);
}

int	init_infos_bonus(t_main *op, int argc, char **argv)
{
	char	stop;

	stop = 0;
	op->use_name = 0;
	op->infos->nb_philo = get_nb_philo(argc, argv, op);
	if (op->infos->nb_philo <= 0)
		stop = ft_errors(3, 1);
	argv += (op->infos->nb_philo * op->use_name) + !op->use_name;
	argc -= (op->infos->nb_philo * op->use_name) + !op->use_name - 1;
	printf("NB = %i CUR = %s\n", op->infos->nb_philo, *argv);
	op->infos->time_die = ft_atoi(*argv++);
	if (op->infos->time_die <= 0)
		stop = ft_errors(4, 1);
	op->infos->time_eat = ft_atoi(*argv++);
	if (op->infos->time_eat <= 0)
		stop = ft_errors(5, 1);
	op->infos->time_sleep = ft_atoi(*argv++);
	if (op->infos->time_sleep <= 0)
		stop = ft_errors(6, 1);
	op->infos->nb_meal = -2;
	if (argc == 5)
		op->infos->nb_meal = ft_atoi(*argv);
	if (argc == 5 && op->infos->nb_meal <= 0)
		stop = ft_errors(7, 1);
	if (argc > 5)
		stop = ft_errors(8, 1);
	return (stop);
}

int	init_misc(t_main *op)
{
	t_misc			*misc;
	pthread_mutex_t	*forks;
	int				i;

	misc = malloc(sizeof(t_misc));
	if (!misc)
		return (1);
	forks = malloc(sizeof(pthread_mutex_t) * op->infos->nb_philo);
	if (!misc)
		return (free(misc), 1);
	i = -1;
	misc->forks = forks;
	misc->infos = op->infos;
	misc->stop = 0;
	misc->use_name = op->use_name;
	pthread_mutex_init(&misc->printf, NULL);
	op->misc = misc;
	return (0);
}

int	init_philosophers(int argc, char **argv, t_main *op)
{
	t_infos	*infos;

	infos = malloc(sizeof(t_infos));
	if (!infos)
		return (ft_errors(-1, 1));
	op->infos = infos;
	if (init_infos_bonus(op, argc, argv))
		return (free(infos), ft_errors(0, 1));
	if (init_philo(op, argc, argv))
		return (free(infos), ft_errors(0, 1));
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:30:45 by gakarbou          #+#    #+#             */
/*   Updated: 2025/01/29 21:34:40 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_infos(t_infos *infos, int argc, char **argv)
{
	char	stop;

	stop = 0;
	infos->nb_philo = ft_atoi(*argv++);
	if (infos->nb_philo <= 0)
		stop = ft_errors(3, 1);
	infos->time_die = ft_atoi(*argv++);
	if (infos->time_die <= 0)
		stop = ft_errors(4, 1);
	infos->time_eat = ft_atoi(*argv++);
	if (infos->time_eat <= 0)
		stop = ft_errors(5, 1);
	infos->time_sleep = ft_atoi(*argv++);
	if (infos->time_sleep <= 0)
		stop = ft_errors(6, 1);
	infos->nb_meal = -2;
	if (argc == 5)
		infos->nb_meal = ft_atoi(*argv++);
	if (argc == 5 && infos->nb_meal <= 0)
		stop = ft_errors(7, 1);
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
	if (init_infos(infos, argc, argv))
		return (free(infos), ft_errors(0, 1));
	op->infos = infos;
	if (init_philo(op, argc, argv))
		return (free(infos), ft_errors(0, 1));
	return (0);
}

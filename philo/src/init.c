/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:30:45 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/06 14:07:03 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_philo_infos(t_philo *philos, t_main *op, int i, char *name)
{
	philos[i].id = i + 1;
	if (op->use_name)
		philos[i].name = ft_strdup(name);
	philos[i].misc = op->misc;
	philos[i].forks[0] = &op->misc->forks[i];
	philos[i].forks[1] = &op->misc->forks[(i + 1) % op->infos->nb_philo];
	philos[i].dead = 0;
	philos[i].fork_hold = 0;
	philos[i].nb_meal = 0;
}

int	init_philo(t_main *op, int argc, char **argv)
{
	t_philo	*philos;
	int		i;

	(void)argc;
	philos = malloc(sizeof(t_philo) * op->infos->nb_philo);
	if (!philos)
		return (1);
	if (init_misc(op))
		return (free(philos), 1);
	i = -1;
	while (++i < op->infos->nb_philo)
		pthread_mutex_init(&op->misc->forks[i], NULL);
	i = -1;
	while (++i < op->infos->nb_philo)
		init_philo_infos(philos, op, i, argv[i]);
	op->philos = philos;
	return (0);
}

int	init_misc(t_main *op)
{
	t_misc			*misc;
	pthread_mutex_t	*forks;

	misc = malloc(sizeof(t_misc));
	if (!misc)
		return (1);
	forks = malloc(sizeof(pthread_mutex_t) * op->infos->nb_philo);
	if (!misc)
		return (free(misc), 1);
	misc->forks = forks;
	misc->infos = op->infos;
	misc->stop = 0;
	misc->use_name = op->use_name;
	pthread_mutex_init(&misc->printf, NULL);
	pthread_mutex_init(&misc->meal, NULL);
	pthread_mutex_init(&misc->fork, NULL);
	pthread_mutex_init(&misc->lock, NULL);
	op->misc = misc;
	return (0);
}

int	init_philosophers(int argc, char **argv, t_main *op)
{
	t_infos	*infos;

	infos = malloc(sizeof(t_infos));
	if (!infos)
		return (ft_errors(-1, 1));
	op->use_name = 0;
	op->infos = infos;
	if (init_infos(op, argc, argv))
		return (free(infos), ft_errors(0, 1));
	if (init_philo(op, argc, argv))
		return (free(infos), ft_errors(0, 1));
	return (0);
}

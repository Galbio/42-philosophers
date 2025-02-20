/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:08:16 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/20 15:26:29 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_infos(t_main *op, int argc, char **argv)
{
	char	stop;

	stop = 0;
	op->use_name = 0;
	op->infos->nb_philo = ft_atoi(*argv++);
	if (op->infos->nb_philo <= 0)
		stop = ft_errors(3, 1);
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
	return (stop);
}

int	main(int argc, char **argv)
{
	int		i;
	t_main	op;

	if (argc < 5 || argc > 6)
		return (ft_errors(1, 1));
	op.end_loop = 1;
	if (init_philosophers(argc - 1, argv + 1, &op))
		return (ft_errors(0, 1));
	i = -1;
	while (++i < op.infos->nb_philo)
	{
		op.philos[i].last_meal = ft_gettimeofday();
		pthread_mutex_init(&op.philos[i].meal, NULL);
		pthread_mutex_lock(&op.misc->printf);
		op.misc->start = ft_gettimeofday();
		pthread_mutex_unlock(&op.misc->printf);
		pthread_create(&op.philos[i].thread, NULL, &routine, &op.philos[i]);
	}
	pthread_mutex_lock(&op.misc->printf);
	op.misc->start = ft_gettimeofday();
	(pthread_mutex_unlock(&op.misc->printf), godmode(&op));
	i = -1;
	while (++i < op.infos->nb_philo)
		pthread_join(op.philos[i].thread, NULL);
	return (free_all(&op), 0);
}

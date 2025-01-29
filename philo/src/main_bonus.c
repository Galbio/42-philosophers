/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:08:16 by gakarbou          #+#    #+#             */
/*   Updated: 2025/01/29 22:52:15 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
	{
		if (op->use_name)
			philos[i].name = ft_strdup(argv[i]);
		philos[i].id = i + 1;
		philos[i].misc = op->misc;
		philos[i].forks[0] = i;
		philos[i].forks[1] = (i + 1) % op->infos->nb_philo;
		philos[i].dead = 0;
		philos[i].fork_hold = 0;
		philos[i].nb_meal = 0;
		pthread_mutex_init(&op->misc->forks[i], NULL);
	}
	op->philos = philos;
	return (0);
}

int	print_status(int code, t_philo *philo)
{
	pthread_mutex_lock(&philo->misc->printf);
	if (!philo->misc->use_name)
		printf("%ld %i ", time_diff(philo->misc->start), philo->id);
	else
		printf("%ld %s ", time_diff(philo->misc->start), philo->name);
	if (code == 1)
		printf("has taken a fork\n");
	else if (code == 2)
		printf("is eating\n");
	else if (code == 3)
		printf("is sleeping\n");
	else if (code == 4)
		printf("is thinking\n");
	else
		printf("idk\n");
	pthread_mutex_unlock(&philo->misc->printf);
	return (1);
}

void	free_all(t_main *op)
{
	int	i;

	i = -1;
	while (++i < op->infos->nb_philo)
		free(op->philos[i].name);
	free(op->infos);
	free(op->misc->forks);
	free(op->misc);
	free(op->philos);
}

int	main(int argc, char **argv)
{
	int		i;
	t_main	op;

	if (argc < 5)
		return (ft_errors(1, 1));
	i = init_philosophers(argc - 1, argv + 1, &op);
	if (i)
		return (ft_errors(0, 1));
	i = -1;
	gettimeofday(&op.misc->start, NULL);
	while (++i < op.infos->nb_philo)
	{
		gettimeofday(&op.philos[i].last_meal, NULL);
		pthread_create(&op.philos[i].thread, NULL, &routine, &op.philos[i]);
	}
	godmode(&op);
	i = -1;
	while (++i < op.infos->nb_philo)
		pthread_join(op.philos[i].thread, NULL);
	free_all(&op);
	return (0);
}

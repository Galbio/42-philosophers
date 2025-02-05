/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 01:51:15 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/05 01:25:04 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	init_infos(t_main *op, int argc, char **argv)
{
	char	stop;

	stop = 0;
	op->infos.nb_philo = ft_atoi(*argv++);
	if (op->infos.nb_philo <= 0)
		stop = ft_errors(3, 1);
	op->infos.time_die = ft_atoi(*argv++);
	if (op->infos.time_die <= 0)
		stop = ft_errors(4, 1);
	op->infos.time_eat = ft_atoi(*argv++);
	if (op->infos.time_eat <= 0)
		stop = ft_errors(5, 1);
	op->infos.time_sleep = ft_atoi(*argv++);
	if (op->infos.time_sleep <= 0)
		stop = ft_errors(6, 1);
	op->infos.nb_meal = -2;
	if (argc == 5)
		op->infos.nb_meal = ft_atoi(*argv);
	if (argc == 5 && op->infos.nb_meal <= 0)
		stop = ft_errors(7, 1);
	return (stop);
}

int	init_misc(t_main *op)
{
	t_misc			*misc;

	misc = malloc(sizeof(t_misc));
	if (!misc)
		return (1);
	misc->forks = sem_open("/forks", O_CREAT, 0600, 1);
	misc->printf = sem_open("/philo", O_CREAT, 0600, 1);
	sem_init(misc->forks, 1, op->infos.nb_philo);
	sem_init(misc->printf, 1, 1);
	misc->infos = op->infos;
	op->misc = misc;
	return (0);
}

char	init_philo(t_main *op)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * op->infos.nb_philo);
	if (!philos)
		return (1);
	if (init_misc(op))
		return (free(philos), 1);
	i = -1;
	while (++i < op->infos.nb_philo)
	{
		philos[i].id = i + 1;
		philos[i].misc = op->misc;
		philos[i].dead = 0;
		philos[i].fork_hold = 0;
		philos[i].nb_meal = 0;
	}
	op->philos = philos;
	return (0);
}

int	init_philos(t_main *op, int argc, char **argv)
{
	if (init_infos(op, argc, argv))
		return (ft_errors(0, 1));
	if (init_philo(op))
		return (ft_errors(0, 1));
	return (0);
}

void	free_forks(t_philo *philo)
{
	if (philo->fork_hold)
		sem_post(philo->misc->forks);
	if (--philo->fork_hold)
		sem_post(philo->misc->forks);
}

char	wait_forks(t_philo *philo)
{
	sem_wait(philo->misc->forks);
	philo->fork_hold++;
	if (philo->dead)
		return (1);
	print_status(philo, 1);
	if (philo->misc->infos.nb_philo == 1)
		return (1);
	sem_wait(philo->misc->forks);
	philo->fork_hold++;
	if (philo->dead)
		return (1);
	print_status(philo, 1);
	print_status(philo, 2);
	return (0);
}

char	routine_loop(t_philo *philo)
{
	if (wait_forks(philo))
		return (free_forks(philo), 1);
	ft_usleep(philo->misc->infos.time_eat * 1000);
	sem_post(philo->misc->forks);
	sem_post(philo->misc->forks);
	if (philo->dead)
		return (1);
	printf("%d is sleeping\n", philo->id);
	ft_usleep(philo->misc->infos.time_sleep * 1000);
	if (philo->dead)
		return (1);
	return (0);
}

char	routine_start(t_philo *philo)
{
	int	i;

	if (philo->id % 2)
		usleep(50);
	i = -1;
	while (++i < 10)
		if (routine_loop(philo))
			break ;
	return (0);
}

void	free_all(t_main *op)
{
	sleep(1);
	op->misc->stop = 1;
	sem_close(op->misc->printf);
	sem_unlink("/philo");
	sem_close(op->misc->forks);
	sem_unlink("/forks");
	free(op->misc);
	free(op->philos);
}

char	create_forks(t_main *op)
{
	int		i;
	pid_t	pid;

	i = -1;
	op->misc->stop = 0;
	while (++i < op->infos.nb_philo)
	{
		pid = fork();
		if (pid != 0)
			op->philos[i].pid = pid;
		else
		{
			routine_start(&op->philos[i]);
			(sem_close(op->misc->printf), sem_close(op->misc->forks));
			(free(op->philos), free(op->misc));
			return (0);
		}
	}
	free_all(op);
	return (0);
}

int	main(int argc, char **argv)
{
	t_main	op;

	if (argc < 5 || argc > 6)
		return (1);
	if (init_philos(&op, argc - 1, argv + 1))
		return (1);
	create_forks(&op);
	return (0);
}

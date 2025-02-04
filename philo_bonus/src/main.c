/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 01:51:15 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/04 02:10:06 by gakarbou         ###   ########.fr       */
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
	sem_t		*forks;
	int				i;

	misc = malloc(sizeof(t_misc));
	if (!misc)
		return (1);
	forks = sem_open("/forks", O_CREAT, 0600, 1);
	sem_init(forks, 1, op->infos.nb_philo);
	i = -1;
	misc->forks = forks;
	misc->infos = op->infos;
	misc->stop = 1;
	misc->printf = sem_open("/philo", O_CREAT, 0600, 1);
	sem_init(misc->printf, 1, 1);
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
		philos[i].forks[0] = i;
		philos[i].forks[1]-= (i + 1) % op->infos.nb_philo;
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

char	routine_start(t_philo *philo)
{
	sem_wait(philo->misc->printf);
	printf("miam from %d\n", philo->id);
	usleep(50000);
	printf("dodo from %d\n", philo->id);
	sem_post(philo->misc->printf);
	return (0);
}

void	supervisor(t_main *op)
{
	int	i;

	printf("I'll take a nap\n");
	sleep(1);
	i = -1;
	sem_close(op->misc->printf);
	sem_unlink("/philo");
	sem_close(op->misc->forks);
	sem_unlink("/forks");
	free(op->misc);
	free(op->philos);
	printf("They're dead lol\n");
	sleep(3);
	//while (++i < op->infos.nb_philo)
		//kill(op->philos[i].pid, SIGINT);
}

char	create_forks(t_main *op)
{
	int		i;
	pid_t	pid;

	i = -1;
	while (++i < op->infos.nb_philo)
	{
		pid = fork();
		if (pid != 0)
			op->philos[i].pid = pid;
		else
			return (routine_start(&op->philos[i]));
	}
	supervisor(op);
	return (0);
}

int main(int argc, char **argv)
{
	t_main	op;

	if (argc < 5 || argc > 6)
		return (1);
	if (init_philos(&op, argc - 1, argv + 1))
		return (1);
	create_forks(&op);
    return (0);
}

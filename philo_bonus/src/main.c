/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 01:51:15 by gakarbou          #+#    #+#             */
/*   Updated: 2025/01/31 14:51:20 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

/*
void* thread(void* arg)
{
    //wait
    sem_wait(&mutex);
    printf("\nEntered..\n");

    //critical section
    sleep(4);
    
    //signal
    printf("\nJust Exiting...\n");
    sem_post(&mutex);
}*/

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
	forks = malloc(sizeof(sem_t) * op->infos.nb_philo);
	if (!misc)
		return (free(misc), 1);
	i = -1;
	misc->forks = forks;
	misc->infos = op->infos;
	misc->stop = 1;
	sem_init(&misc->printf, 1, 0);
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
		sem_init(&op->misc->forks[i], 1, 0);
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

void	routine_start(t_philo *philo)
{
	while (philo->misc->stop)
		printf("stop = %d, addr = %p\n", philo->misc->stop, &philo->misc->stop);
	printf("%d miam\n", philo->id);
	while (1)
		;
}

void	create_forks(t_main *op)
{
	int		i;
	pid_t	pid;

	i = -1;
	while (++i < op->infos.nb_philo)
	{
		pid = fork();
		if (pid != 0)
		{
			printf("My son's pid is %d\n", pid);
			op->philos[i].pid = pid;
		}
		else
			routine_start(&op->philos[i]);
	}
	op->misc->stop = 0;
}

int main(int argc, char **argv)
{
	t_main	op;
	int		i;

	if (argc < 5 || argc > 6)
		return (1);
	if (init_philos(&op, argc - 1, argv + 1))
		return (1);
	create_forks(&op);
	printf("stop = %d, addr = %p\n", op.philos[0]->misc->stop, &op.philos[0]->misc->stop);
	printf("I'll take a nap\n");
	sleep(2);
	i = -1;
	while (++i < op.infos.nb_philo)
		kill(op.philos[i].pid, SIGINT);
	printf("They're dead lol\n");
	free(op.misc->forks);
	free(op.misc);
	free(op.philos);
    return 0;
}

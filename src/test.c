/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 20:53:26 by gakarbou          #+#    #+#             */
/*   Updated: 2025/01/27 15:21:14 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>

void	ft_errors(int code, t_main *op)
{
	(void)code;
	op->exit = 1;
	printf("Error\n");
}

int	ft_atoi(char *str)
{
	int	i;
	int	res;

	if (!str[0])
		return (-1);
	i = -1;
	res = 0;
	while (str[++i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		res = res * 10 + (str[i] - '0');
	}
	return (res);
}

long int	time_diff(struct timeval start)
{
	struct timeval	cur;
	double			a;
	double			b;

	b = start.tv_usec / 1000;
	gettimeofday(&cur, NULL);
	a = cur.tv_usec / 1000 + (1000 * (cur.tv_sec - start.tv_sec));
	return (a - b);
}

void	wait_forks(t_philo *philo)
{
	if (philo->index % 2)
		pthread_mutex_lock(&philo->misc.forks[philo->forks[0]]);
	else
		pthread_mutex_lock(&philo->misc.forks[philo->forks[1]]);
	philo->fork_hold = 1;
	if (!philo->is_dead && time_diff(philo->time_since_meal) \
			<= philo->infos.time_die)
		;
	else
		return ;
	if (philo->infos.nb_philo == 1)
		return ;
	if (philo->index % 2)
		pthread_mutex_lock(&philo->misc.forks[philo->forks[1]]);
	else
		pthread_mutex_lock(&philo->misc.forks[philo->forks[0]]);
	philo->fork_hold = 2;
	if (!philo->is_dead && time_diff(philo->time_since_meal) \
			<= philo->infos.time_die)
		;
}

char	free_philo_forks(t_philo *philo)
{
	if (philo->index % 2 && philo->fork_hold >= 1)
		pthread_mutex_unlock(&philo->misc.forks[philo->forks[0]]);
	else if (philo->fork_hold >= 1)
		pthread_mutex_unlock(&philo->misc.forks[philo->forks[1]]);
	philo->fork_hold--;
	if ((philo->index % 2) && philo->fork_hold == 1)
		pthread_mutex_unlock(&philo->misc.forks[philo->forks[1]]);
	else if (philo->fork_hold == 1)
		pthread_mutex_unlock(&philo->misc.forks[philo->forks[0]]);
	philo->fork_hold--;
	return (1);
}

char	routine_loop(t_philo *philo)
{
	wait_forks(philo);
	if (philo->is_dead || philo->infos.nb_philo == 1)
		return (free_philo_forks(philo));
	if (gettimeofday(&philo->time_since_meal, NULL))
		return (1);
	usleep(philo->infos.time_eat * 999);
	free_philo_forks(philo);
	philo->meal_count++;
	if (!philo->is_dead && time_diff(philo->time_since_meal) \
			<= philo->infos.time_die)
		;
	else
		return (1);
	usleep(philo->infos.time_sleep * 999);
	if (!philo->is_dead && time_diff(philo->time_since_meal) \
			<= philo->infos.time_die)
		;
	return (philo->is_dead);
}

void	*routine(void *ptr_start)
{
	t_philo			*philo;

	philo = (t_philo *)ptr_start;
	if (philo->index % 2)
		usleep(10);
	while (!philo->is_dead)
		if (routine_loop(philo))
			break ;
	return (NULL);
}

void	init_philo(t_main *op, int i)
{
	op->philosophers[i].index = i;
	op->philosophers[i].is_dead = 0;
	op->philosophers[i].fork_hold = 0;
	op->philosophers[i].meal_count = 0;
	op->philosophers[i].infos = op->infos;
	op->philosophers[i].misc.forks = op->forks;
	op->philosophers[i].misc.started = &op->go;
	op->philosophers[i].misc.start = &op->start;
	op->philosophers[i].forks[0] = i;
	op->philosophers[i].forks[1] = (i + 1) % op->infos.nb_philo;
	pthread_mutex_init(&op->philosophers[i].lock, NULL);
}

void	init_mallocs(t_main *op)
{
	int	i;

	op->forks = malloc(sizeof(pthread_mutex_t) * op->infos.nb_philo);
	if (!op->forks)
		ft_errors(0, op);
	op->philosophers = malloc(sizeof(t_philo) * op->infos.nb_philo);
	if (!op->philosophers)
	{
		free(op->forks);
		ft_errors(0, op);
	}
	i = -1;
	while (++i < op->infos.nb_philo)
		init_philo(op, i);
}

char	init_infos(int argc, char **argv, t_main *op)
{
	op->exit = 0;
	op->infos.nb_philo = ft_atoi(argv[0]);
	if (op->infos.nb_philo < 1)
		ft_errors(1, op);
	op->infos.time_die = ft_atoi(argv[1]);
	if (op->infos.time_die < 1)
		ft_errors(2, op);
	op->infos.time_eat = ft_atoi(argv[2]);
	if (op->infos.time_eat < 1)
		ft_errors(3, op);
	op->infos.time_sleep = ft_atoi(argv[3]);
	if (op->infos.time_sleep < 1)
		ft_errors(4, op);
	op->infos.nb_meal = -1;
	if (argc == 5)
		op->infos.nb_meal = ft_atoi(argv[4]);
	if (argc == 5 && op->infos.nb_meal < 1)
		ft_errors(5, op);
	if (!op->exit)
		init_mallocs(op);
	return (op->exit);
}

char	everyone_alive(t_main *op)
{
	int	i;

	i = -1;
	while (++i < op->infos.nb_philo)
		if (op->philosophers[i].is_dead == 0)
			return (1);
	return (0);
}

char	everyone_ate(t_main *op)
{
	int	i;

	if (op->infos.nb_meal == -1)
		return (0);
	i = -1;
	while (++i < op->infos.nb_philo)
	{
		if (op->philosophers[i].is_dead)
			continue ;
		if (op->philosophers[i].meal_count < op->infos.nb_meal)
			return (0);
	}
	return (1);
}

void	godmode(t_main *op)
{
	int			i;
	int long	time_d;

	while (everyone_alive(op))
	{
		i = -1;
		if (everyone_ate(op))
		{
			while (++i < op->infos.nb_philo)
				op->philosophers[i].is_dead = 1;
			break ;
		}
		while (++i < op->infos.nb_philo)
		{
			time_d = 1000;
			if (time_d > op->infos.time_die && !op->philosophers[i].is_dead)
			{
				pthread_join(op->philosophers[i].philo, NULL);
				op->philosophers[i].is_dead = 1;
				printf("[%ld] %i died\n", time_diff(op->start) - 1, i + 1);
			}
		}
	}
}

int	main(int argc, char **argv)
{
	int			i;
	t_main		op;

	if (argc < 5 || argc > 6 || init_infos(argc - 1, argv + 1, &op))
		return (1);
	i = -1;
	op.go = 0;
	gettimeofday(&op.start, NULL);
	while (++i < op.infos.nb_philo)
	{
		gettimeofday(&op.philosophers[i].time_since_meal, NULL);
		pthread_create(&op.philosophers[i].philo, NULL, &routine, \
				&op.philosophers[i]);
	}
	i = -1;
	op.go = 1;
	godmode(&op);
	i = -1;
	while (++i < op.infos.nb_philo)
		pthread_mutex_destroy(&op.forks[i]);
	free(op.forks);
	free(op.philosophers);
	return (0);
}

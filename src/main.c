/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:08:16 by gakarbou          #+#    #+#             */
/*   Updated: 2025/01/28 17:09:53 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

int	ft_errors(int code, char res)
{
	if (code == 0)
		return (res);
	else if (code == 1)
		write(2, "Invalid arguments number\n", 25);
	else
		write(2, "Error\n", 6);
	return (res);
}

int	ft_atoi(char *str)
{
	int	i;
	int	res;

	if (!str[0])
		return (-1);
	res = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		res = res * 10 + (str[i++] - '0');
	}
	return (res);
}

int	init_infos(t_infos *infos, int argc, char **argv)
{
	char	stop;

	stop = 0;
	infos->nb_philo = ft_atoi(argv[0]);
	if (infos->nb_philo <= 0)
		stop = ft_errors(3, 1);
	infos->time_die = ft_atoi(argv[1]);
	if (infos->time_die <= 0)
		stop = ft_errors(4, 1);
	infos->time_eat = ft_atoi(argv[2]);
	if (infos->time_eat <= 0)
		stop = ft_errors(5, 1);
	infos->time_sleep = ft_atoi(argv[3]);
	if (infos->time_sleep <= 0)
		stop = ft_errors(6, 1);
	infos->nb_meal = -2;
	if (argc == 5)
		infos->nb_meal = ft_atoi(argv[4]);
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
	pthread_mutex_init(&misc->printf, NULL);
	op->misc = misc;
	return (0);
}

int	init_philo(t_main *op)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * op->infos->nb_philo);
	if (!philos)
		return (1);
	if (init_misc(op))
		return (free(philos), 1);
	i = -1;
	while (++i < op->infos->nb_philo)
	{
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

int	init_philosophers(int argc, char **argv, t_main *op)
{
	t_infos	*infos;

	infos = malloc(sizeof(t_infos));
	if (!infos)
		return (ft_errors(-1, 1));
	if (init_infos(infos, argc, argv))
		return (free(infos), ft_errors(0, 1));
	op->infos = infos;
	if (init_philo(op))
		return (free(infos), ft_errors(0, 1));
	return (0);
}

char	check_dead(t_philo *philo)
{
	char	res;

	res = 0;
	pthread_mutex_lock(&philo->misc->printf);
	if (philo->dead || philo->misc->stop)
		res = 1;
	pthread_mutex_unlock(&philo->misc->printf);
	return (res);
}

int	print_status(int code, t_philo *philo)
{
	pthread_mutex_lock(&philo->misc->printf);
	if (code == 1)
		printf("[%ld] %d has taken a fork\n", time_diff(philo->misc->start), \
				philo->id);
	else if (code == 2)
		printf("[%ld] %d is eating\n", time_diff(philo->misc->start), \
				philo->id);
	else if (code == 3)
		printf("[%ld] %d is sleeping\n", time_diff(philo->misc->start), \
				philo->id);
	else if (code == 4)
		printf("[%ld] %d is thinking\n", time_diff(philo->misc->start), \
				philo->id);
	else
		printf("idk\n");
	pthread_mutex_unlock(&philo->misc->printf);
	return (1);
}

int	wait_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->misc->forks[philo->forks[philo->id % 2]]);
	philo->fork_hold++;
	pthread_mutex_lock(&philo->misc->printf);
	if (philo->dead || philo->misc->stop)
		return (pthread_mutex_unlock(&philo->misc->printf));
	else if (philo->forks[0] == philo->forks[1])
	{
		pthread_mutex_unlock(&philo->misc->printf);
		return (print_status(1, philo));
	}
	pthread_mutex_unlock(&philo->misc->printf);
	print_status(1, philo);
	pthread_mutex_lock(&philo->misc->forks[philo->forks[(philo->id + 1) % 2]]);
	philo->fork_hold++;
	if (check_dead(philo))
			return (0);
	return (print_status(1, philo));
}

char	unlock_forks(t_philo *philo)
{
	if (!philo->fork_hold)
		return (1);
	pthread_mutex_unlock(&philo->misc->forks[philo->forks[philo->id % 2]]);
	philo->fork_hold--;
	if (!philo->fork_hold)
		return (1);
	pthread_mutex_unlock(&philo->misc->forks[philo->forks[(philo->id \
				+ 1) % 2]]);
	philo->fork_hold--;
	return (1);
}

char	routine_loop(t_philo *philo)
{
	wait_forks(philo);
	if (check_dead(philo) || philo->fork_hold != 2)
		return (unlock_forks(philo));
	print_status(2, philo);
	pthread_mutex_lock(&philo->misc->printf);
	gettimeofday(&philo->last_meal, NULL);
	philo->nb_meal++;
	pthread_mutex_unlock(&philo->misc->printf);
	usleep(999 * philo->misc->infos->time_eat);
	unlock_forks(philo);
	if (check_dead(philo))
		return (1);
	print_status(3, philo);
	usleep(999 * philo->misc->infos->time_sleep);
	if (check_dead(philo))
		return (1);
	print_status(4, philo);
	return (0);
}

void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (!check_dead(philo))
		if (routine_loop(philo))
			break ;
	return (NULL);
}

char	supervise(t_main *op, int *nb_alive)
{
	int	i;
	int	time_temp;

	i = -1;
	while (++i < op->infos->nb_philo)
	{
		pthread_mutex_lock(&op->misc->printf);
		time_temp = time_diff(op->philos[i].last_meal);
		pthread_mutex_unlock(&op->misc->printf);
		if (time_temp > op->infos->time_die && !op->philos[i].dead)
		{
			pthread_mutex_lock(&op->misc->printf);
			op->misc->stop = 1;
			op->philos[i].dead = 1;
			printf("[%ld] %d died\n", time_diff(op->misc->start), \
					op->philos[i].id);
			*nb_alive += 1;
			pthread_mutex_unlock(&op->misc->printf);
			return (1);
		}
	}
	return (0);
}

char	everyone_ate(t_main *op)
{
	int	i;

	if (op->infos->nb_meal <= 0)
		return (0);
	i = -1;
	while (++i < op->infos->nb_philo)
	{
		pthread_mutex_lock(&op->misc->printf);
		if (op->philos[i].nb_meal < op->infos->nb_meal)
		{
			pthread_mutex_unlock(&op->misc->printf);
			return (0);
		}
		pthread_mutex_unlock(&op->misc->printf);
	}
	return (1);
}

char	godmode(t_main *op)
{
	int			nb_alive;

	nb_alive = op->infos->nb_philo;
	while (nb_alive)
	{
		if (everyone_ate(op))
		{
			pthread_mutex_lock(&op->misc->printf);
			op->misc->stop = 1;
			pthread_mutex_unlock(&op->misc->printf);
			return (1);
		}
		if (supervise(op, &nb_alive))
			break ;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int		i;
	t_main	op;

	if (argc < 5 || argc > 6)
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
	free(op.infos);
	free(op.misc->forks);
	free(op.misc);
	free(op.philos);
	return (0);
}

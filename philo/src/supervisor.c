/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 21:30:09 by gakarbou          #+#    #+#             */
/*   Updated: 2025/01/30 17:43:04 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
			if (op->end_loop)
				op->misc->stop = 1;
			op->philos[i].dead = 1;
			pthread_mutex_unlock(&op->misc->printf);
			print_status(5, &op->philos[i]);
			pthread_mutex_lock(&op->misc->printf);
			(*nb_alive)--;
			pthread_mutex_unlock(&op->misc->printf);
			return (op->misc->stop);
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

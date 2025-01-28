/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:08:36 by gakarbou          #+#    #+#             */
/*   Updated: 2025/01/28 16:28:34 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_infos
{
	int	nb_philo;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	nb_meal;
}	t_infos;

typedef struct s_misc
{
	struct timeval	start;
	t_infos			*infos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	printf;
	char			stop;
}	t_misc;

typedef struct s_philo
{
	struct timeval	last_meal;
	pthread_t		thread;
	t_misc			*misc;
	char			dead;
	char			fork_hold;
	int				forks[2];
	int				id;
	int				nb_meal;
}	t_philo;

typedef struct s_main
{
	t_philo	*philos;
	t_infos	*infos;
	t_misc	*misc;
}	t_main;

#endif

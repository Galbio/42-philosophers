/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:32:58 by gakarbou          #+#    #+#             */
/*   Updated: 2025/01/24 16:21:13 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_philo_info
{
	int				nb_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nb_meal;
}	t_philo_info;

typedef struct s_misc
{
	char			*started;
	struct timeval	*start;
	pthread_mutex_t	*forks;
}	t_misc;

typedef struct s_philo
{
	pthread_t		philo;
	pthread_mutex_t	lock;
	t_philo_info	infos;
	t_misc			misc;
	int				index;
	int				forks[2];
	struct timeval	time_since_meal;
	int long		action_start;
	int				meal_count;
	char			fork_hold;
	char			is_dead;
}	t_philo;

typedef struct s_main
{
	char			go;
	char			exit;
	struct timeval	start;
	pthread_mutex_t	*forks;
	t_philo_info	infos;
	t_philo			*philosophers;
}	t_main;

#endif

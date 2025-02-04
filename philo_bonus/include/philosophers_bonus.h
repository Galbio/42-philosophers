/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 02:36:23 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/04 01:16:19 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <stdio.h>

typedef struct s_info
{
	int		nb_philo;
	int		time_die;
	int		time_eat;
	int		time_sleep;
	int		nb_meal;
}	t_info;

typedef struct s_misc
{
	struct timeval	start;
	char			stop;
	t_info			infos;
	sem_t			*forks;
	sem_t			*printf;
}	t_misc;

typedef struct s_philo
{
	struct timeval	last_meal;
	t_misc			*misc;
	pid_t			pid;
	char			dead;
	char			fork_hold;
	int				nb_meal;
	int				forks[2];
	int				id;
}	t_philo;

typedef struct s_main
{
	t_philo	*philos;
	t_info	infos;
	t_misc	*misc;
}	t_main;

int			ft_atoi(char *str);
long int	time_diff(struct timeval start);
int			ft_errors(int code, char res);

#endif

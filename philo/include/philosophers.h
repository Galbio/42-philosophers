/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:08:36 by gakarbou          #+#    #+#             */
/*   Updated: 2025/01/28 22:19:40 by gakarbou         ###   ########.fr       */
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

/*    main.c   */
char		godmode(t_main *op);
char		everyone_ate(t_main *op);
char		supervise(t_main *op, int *nb_alive);

/*    init.c   */
int			init_misc(t_main *op);
int			init_philo(t_main *op);
int			init_infos(t_infos *infos, int argc, char **argv);
int			init_philosophers(int argc, char **argv, t_main *op);

/*   routine.c  */
void		*routine(void *ptr);
char		routine_loop(t_philo *philo);
char		unlock_forks(t_philo *philo);
int			wait_forks(t_philo *philo);

/*   utils.c   */
int			print_status(int code, t_philo *philo);
char		check_dead(t_philo *philo);
int			ft_atoi(char *str);
int			ft_errors(int code, char res);
long int	time_diff(struct timeval start);

#endif

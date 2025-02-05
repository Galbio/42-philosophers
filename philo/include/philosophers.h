/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:08:36 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/04 22:31:23 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

# define RESET		"\033[0m"
# define RED		"\033[31m"
# define GREEN       "\033[32m"
# define YELLOW      "\033[93m"
# define BLUE        "\033[34m"
# define MAGENTA     "\033[35m"
# define CYAN        "\033[36m"
# define GREY		"\033[90m"
# define BOLD		"\033[1m"
# define UNDERLINE	"\033[4m"

# ifndef BONUS
#  define BONUS 0
# endif

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
	char			stop;
	char			use_name;
	t_infos			*infos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	printf;
	pthread_mutex_t	fork;
	pthread_mutex_t	meal;
	pthread_mutex_t	lock;
}	t_misc;

typedef struct s_philo
{
	struct timeval	last_meal;
	pthread_t		thread;
	t_misc			*misc;
	char			*name;
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
	char	use_name;
	char	end_loop;
}	t_main;

/*    main.c   */
char		godmode(t_main *op);
char		everyone_ate(t_main *op);
char		supervise(t_main *op, int *nb_alive);
char		*ft_strdup(char *str);

/*    init.c   */
int			init_misc(t_main *op);
int			init_philo(t_main *op, int argc, char **argv);
int			init_infos(t_main *op, int argc, char **argv);
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
void		free_all(t_main *op);
char		*ft_strdup(char *str);
void		ft_usleep(long time);

#endif

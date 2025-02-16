/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 02:12:38 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/14 23:47:51 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <pthread.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <signal.h>
# include <semaphore.h>
# include <string.h>

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
	int			nb_philo;
	int			time_die;
	int			time_eat;
	int			time_sleep;
	int			nb_meal;
}	t_infos;

typedef struct s_misc
{
	int long	start_time;
	sem_t		*forks;
	sem_t		*printf;
	sem_t		*start;
	sem_t		*stop;
	sem_t		*meals;
}	t_misc;

typedef struct s_philo
{
	sem_t		meal;
	sem_t		lock;
	t_infos		infos;
	t_misc		*misc;
	int			id;
	int			nb_meal;
	int long	last_meal;
	char		dead;
	char		stop;
	char		fork_hold;
}	t_philo;

typedef struct s_main
{
	t_infos		infos;
	t_misc		*misc;
	t_philo		*philos;
	pid_t		*pids;
}	t_main;

/*		Main.c		*/
char			create_forks(t_main *op);

/*		Init.c		*/
char			init_infos(t_main *op, char **argv, char nb_meal);
char			init_philos(t_main *op);
char			init_op(t_main *op);
char			init_sem(t_main *op);
void			close_sem(void);

/*		Philo.c		*/
void			init_process(t_philo *philo);
void			check_end(t_philo *philo);
void			*check_death(void *ptr);
void			check_meals(t_philo *philo);
void			give_dead_meal(t_philo *philo);

/*		Routine.c	*/
char			routine_loop(t_philo *philo);
void			*routine_init(void *ptr);
char			take_forks(t_philo *philo);
void			post_forks(t_philo *philo);

/*		Parent.c	*/
void			parent_process(t_main *op);
void			*collect_meals(void *ptr);

/*		Errors.c	*/
void			destroy_forks(t_main *op, int nb);
void			destroy_sem(t_main *op);

/*		Outputs.c	*/
void			print_status(t_philo *philo, char code);
char			ft_errors(int code);

/*		Utils.c		*/
char			ft_usleep(int time, t_philo *philo);
char			check_stop(t_philo *philo);
int long		ft_gettimeofday(void);
int				ft_atoi(char *str);

#endif

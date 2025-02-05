/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 02:36:23 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/05 01:27:46 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <stdio.h>

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
	pthread_t		routine;
	pthread_t		checker;
	t_misc			*misc;
	pid_t			pid;
	char			dead;
	char			fork_hold;
	int				nb_meal;
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
void		ft_usleep(long time);
void		print_status(t_philo *philo, char code);

#endif

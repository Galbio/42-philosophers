/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 20:53:26 by gakarbou          #+#    #+#             */
/*   Updated: 2025/01/22 16:39:10 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_haha
{
	struct timeval	start;
	char			aled;
}	t_haha;

long long	ft_round(double nb)
{
	if (((nb / nb) - 1) >= 0.5)
		return ((nb / 1) + 1);
	return (nb / 1);
}

long long	time_diff(struct timeval start, struct timeval cur)
{
	double	a;
	double	b;

	b = (double)start.tv_usec / 1000;
	a = (double)cur.tv_usec / 1000 + (1000 * (cur.tv_sec - start.tv_sec));
	printf("A = %lf, B = %lf\n", a, b);
	return (a - b);
}

void	*routine(void *ptr_start)
{
	static pthread_mutex_t	lck;
	struct timeval cur;
	static int	a = 0;
	t_haha			*haha;

	haha = (t_haha *)ptr_start;
	while (!haha->aled)
		;
	pthread_mutex_lock(&lck);
	usleep(1000000);
	gettimeofday(&cur, NULL);
	pthread_mutex_unlock(&lck);
	printf("%d finished at %lld\n", a++, time_diff(haha->start, cur));
}

int	main(void)
{
	int			i;
	pthread_t	id[5];
	t_haha		haha;

	i = -1;
	haha.aled = 0;
	while (++i < 5)
		pthread_create(&(id[i]), NULL, &routine, &haha);
	usleep(500);
	gettimeofday(&haha.start, NULL);
	haha.aled = 1;
	i = -1;
	while (++i < 5)
		pthread_join(id[i], NULL);
	printf("Done\n");
	return (0);
}

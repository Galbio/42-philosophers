/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_fork_mem.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:31:11 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/05 19:44:56 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void	print_status(char *start)
{
	write(1, "aled\n", 5);
	free(start);
	while (1)
		;
	exit(0);
}

int	main(void)
{
	char	*truc;
	pid_t	pid;
	pthread_t	change;

	truc = malloc(sizeof(char));
	*truc = 42;
	pid = fork();
	if (!pid)
		print_status(truc);
	sleep(1);
	kill(pid, SIGTERM);
	free(truc);
	return (0);
}

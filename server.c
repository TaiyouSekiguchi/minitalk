/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 09:21:13 by tsekiguc          #+#    #+#             */
/*   Updated: 2021/09/13 11:37:37 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

volatile sig_atomic_t	sigint_count = 3;

void	sigusr1_handler(int signum)
{
	static unsigned char	tmp;
	static size_t			cnt;

	tmp = tmp | 0;
	if (cnt == 8)
	{
		printf("%c", tmp);
		tmp = 0;
		cnt = 0;
	}
	tmp <<= 1;
	cnt++;
}

void	sigusr2_handler(int signum)
{
	static unsigned char	tmp;
	static size_t			cnt;

	tmp = tmp | 1;
	if (cnt == 8)
	{
		printf("%c", tmp);
		tmp = 0;
		cnt = 0;
	}
	tmp <<= 1;
	cnt++;
}

int	main(void)
{
	struct sigaction sa_sigint;

	memset(&sa_sigint, 0, sizeof(sa_sigint));
	sa_sigint.sa_handler = sigint_handler;
	sa_sigint.sa_flags = SA_RESTART;

	printf("PID is [%ld]\n", (long)getpid());

	if (sigaction(SIGUSR1, &sa_sigint, NULL) < 0)
	{
		perror("sigaction");
		exit(1);
	}

	for(;;)
	{
		printf("\nMAIN : sigint_count(%d), calling pause...\n", sigint_count);

		pause();

		printf("\nMAIN : returned from pause.sigint_count(%d)\n", sigint_count);
	}
	return (0);
}

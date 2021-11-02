/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 09:21:13 by tsekiguc          #+#    #+#             */
/*   Updated: 2021/11/01 16:51:40 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

volatile sig_atomic_t	g_recieve_signal;

static void	handle_signal(int signal)
{
	g_recieve_signal = signal;
	printf("signal get\n");
}

static void	recieve_bit(char *str, int g_recieve_signal)
{
	static unsigned char	uc;
	static int				count;
	static int				i;

	printf("in recieve_bit\n");
	if (g_recieve_signal == SIGUSR1)
	{
		uc |= 0;
	}
	else if (g_recieve_signal == SIGUSR2)
	{
		uc |= 1;
	}
	printf("%d\n", uc);
	uc <<= 1;
	count++;
	if (count == 8)
	{
		uc >>= 1;
		str[i] = (char)uc;
		printf("%c\n", str[i]);
		if (str[i] == 0x04)
		{
			printf("%s\n", str);
			exit(0);
		}
		i++;
		uc = 0;
		count = 0;
	}
}

static void	exit_server(char *str)
{
	free(str);
	exit(0);
}

int	main(void)
{
	struct sigaction	sa;
	sigset_t			block;
	int					ret;
	char				*str;

	ret = sigemptyset(&block);
	if (ret < 0)
		return (1);
	ret = sigaddset(&block, SIGUSR1);
	if (ret < 0)
		return (1);
	ret = sigaddset(&block, SIGUSR2);
	if (ret < 0)
		return (1);

	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &handle_signal;
	sa.sa_mask = block;
	sa.sa_flags = SA_RESTART;

	if (sigaction(SIGUSR1, &sa, NULL) < 0)
	{
		perror("sigaction");
		exit(1);
	}

	if (sigaction(SIGUSR2, &sa, NULL) < 0)
	{
		perror("sigaction");
		exit(1);
	}

	printf("PID is [%ld]\n", (long)getpid());

	str = (char *)malloc(sizeof(char) * 10);
	if (str == NULL)
		return (1);
	memset(str, 0, 10);

	while (1)
	{
		printf("in while loop\n");
		if (g_recieve_signal == SIGUSR1 || g_recieve_signal == SIGUSR2)
			recieve_bit(str, g_recieve_signal);
		if (g_recieve_signal == SIGQUIT || g_recieve_signal == SIGINT)
			exit_server(str);
		pause();
	}

	return (0);
}

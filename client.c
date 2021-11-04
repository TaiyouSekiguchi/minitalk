/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 10:47:56 by tsekiguc          #+#    #+#             */
/*   Updated: 2021/11/04 14:22:35 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static void	sent_bit(unsigned char send_char, pid_t pid)
{
	unsigned char	answer;
	unsigned char	bit;

	bit = 1 << 7;
	while (bit != 0)
	{
		answer = send_char & bit;
		if (answer == 0)
		{
			if (kill(pid, SIGUSR1) < 0)
				exit(1);
		}
		else
		{
			if (kill(pid, SIGUSR2) < 0)
				exit(1);
		}
		bit >>= 1;
		usleep(100);
	}
}

static void	handle_signal(int signal)
{
	if (signal == SIGUSR1)
		ft_putendl_fd("ACK recieved ;)", STDOUT_FILENO);
	exit(0);
}

int	main(int argc, char *argv[])
{
	struct sigaction	sa;
	pid_t				pid;
	int					i;

	if (argc != 3)
	{
		ft_putstr_fd("\"./client [server PID] [message]\"", STDOUT_FILENO);
		return (0);
	}

	ft_memset(&sa, '\0', sizeof(sa));
	sa.sa_handler = &handle_signal;
	sa.sa_flags = SA_RESTART;

	if (sigaction(SIGUSR1, &sa, NULL) < 0)
	{
		ft_putstr_fd("sigaction error\n", STDERR_FILENO);
		exit(1);
	}

	pid = ft_atoi(argv[1]);

	i = 0;
	while (argv[2][i] != '\0')
	{
		sent_bit((unsigned char)argv[2][i], pid);
		i++;
	}
	sent_bit('\0', pid);
	pause();
	return (0);
}

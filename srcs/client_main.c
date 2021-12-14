/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 14:31:49 by tsekiguc          #+#    #+#             */
/*   Updated: 2021/11/11 16:03:37 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static void	error_exit(char *msg)
{
	ft_putendl_fd(msg, STDERR_FILENO);
	exit(1);
}

static void	handle_signal(int signal)
{
	if (signal == SIGUSR1)
		ft_putendl_fd("ACK recieved ;)", STDOUT_FILENO);
	exit(0);
}

static void	sigaction_set(struct sigaction *sa, sigset_t *block)
{
	if ((sigemptyset(block) != 0)
		|| (sigaddset(block, SIGUSR1) != 0))
		error_exit("sigset error in sigaction_set");
	sa->sa_handler = &handle_signal;
	sa->sa_mask = *block;
	sa->sa_flags = SA_RESTART;
	if (sigaction(SIGUSR1, sa, NULL) < 0)
		error_exit("sigaction error in sigaction_set");
}

static void	send_bit(unsigned char sent_char, long pid)
{
	unsigned char	answer;
	unsigned char	bit;

	bit = 1 << 7;
	while (bit != 0)
	{
		answer = sent_char & bit;
		if (answer == 0)
		{
			if (kill(pid, SIGUSR1) < 0)
				error_exit("kill error in send_bit");
		}
		else
		{
			if (kill(pid, SIGUSR2) < 0)
				error_exit("kill error in send_bit");
		}
		if (usleep(100) < 0)
			error_exit("usleep error in send_bit");
		bit >>= 1;
	}
}

int	main(int argc, char *argv[])
{
	struct sigaction	sa;
	sigset_t			block;
	long				pid;
	size_t				i;

	if (argc != 3)
		error_exit("\"./client [server PID] [message]\"");
	ft_memset(&sa, '\0', sizeof(sa));
	sigaction_set(&sa, &block);
	pid = ft_atol(argv[1]);
	if (pid <= 0)
		error_exit("Please input server PID");
	i = 0;
	while (argv[2][i] != '\0')
	{
		send_bit((unsigned char)argv[2][i], pid);
		i++;
	}
	send_bit('\0', pid);
	pause();
	return (0);
}

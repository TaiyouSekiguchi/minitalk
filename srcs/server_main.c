/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 09:21:13 by tsekiguc          #+#    #+#             */
/*   Updated: 2021/11/11 15:35:40 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

volatile t_signal	g_signal;

static void	handle_signal(int no, siginfo_t *info, void *ctx)
{
	(void)*ctx;
	g_signal.sig = no;
	g_signal.pid = info->si_pid;
}

static void	sigaction_set(struct sigaction *sa, sigset_t *block)
{
	if ((sigemptyset(block) != 0)
		|| (sigaddset(block, SIGUSR1) != 0)
		|| (sigaddset(block, SIGUSR2) != 0))
		error_exit("sigset error in sigaction_set");
	sa->sa_sigaction = &handle_signal;
	sa->sa_mask = *block;
	sa->sa_flags = SA_SIGINFO | SA_RESTART;
	if ((sigaction(SIGUSR1, sa, NULL) < 0)
		|| (sigaction(SIGUSR2, sa, NULL) < 0)
		|| (sigaction(SIGQUIT, sa, NULL) < 0)
		|| (sigaction(SIGINT, sa, NULL) < 0))
		error_exit("sigaction error in sigaction_set");
}

static void	put_pid(void)
{
	ft_putstr_fd("PID is [", STDOUT_FILENO);
	ft_putnbr_long_fd(getpid(), STDOUT_FILENO);
	ft_putstr_fd("]\n", STDOUT_FILENO);
}

static void	main_loop(char **buf, size_t *buf_size)
{
	while (1)
	{
		if (g_signal.sig == SIGUSR1 || g_signal.sig == SIGUSR2)
			recieve_signal(buf, buf_size, g_signal.sig, g_signal.pid);
		if (g_signal.sig == SIGQUIT || g_signal.sig == SIGINT)
			break ;
		pause();
	}
}

int	main(void)
{
	struct sigaction	sa;
	sigset_t			block;
	char				*buf;
	size_t				buf_size;

	ft_memset(&sa, '\0', sizeof(sa));
	sigaction_set(&sa, &block);
	put_pid();
	if (!buf_init(&buf, &buf_size))
		error_exit("buf_init error in main");
	main_loop(&buf, &buf_size);
	free(buf);
	return (0);
}

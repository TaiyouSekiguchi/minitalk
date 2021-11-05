/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 09:21:13 by tsekiguc          #+#    #+#             */
/*   Updated: 2021/11/05 11:10:03 by tsekiguc         ###   ########.fr       */
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

char	*buf_resize(char *buf, size_t buf_size)
{
	char	*ret;
	size_t	resize;
	size_t	i;

	if (buf == NULL)
		return (NULL);

	if (SIZE_MAX - buf_size <= buf_size)
	{
		free(buf);
		return (NULL);
	}
	resize = buf_size * 2;
	ret = (char *)malloc(sizeof(char) * resize);
	if (ret == NULL)
	{
		free(buf);
		return (NULL);
	}
	ft_memset(ret, '\0', resize);
	i = 0;
	while (i < buf_size)
	{
		ret[i] = buf[i];
		i++;
	}
	ret[i] = '\0';
	free(buf);
	return (ret);
}

static void	recieve_bit(char **buf, size_t *buf_size, int g_recieve_signal)
{
	static unsigned char	uc;
	static size_t			count;
	static size_t			i;

	if (g_recieve_signal == SIGUSR1)
	{
		uc |= 0;
	}
	else if (g_recieve_signal == SIGUSR2)
	{
		uc |= 1;
	}

	if (count == 7)
	{
		(*buf)[i] = (char)uc;
		if ((*buf)[i] == '\0')
		{
			write(1, *buf, strlen(*buf));
			write(1, "\n", 1);

			if (kill(g_signal.pid, SIGUSR1) < 0)
				exit(1);

			memset(*buf, '\0', *buf_size);
			uc = 0;
			count = 0;
			i = 0;
			return ;
		}
		if (i == *buf_size - 1)
		{
			*buf = buf_resize(*buf, *buf_size);
			if (*buf == NULL)
				exit(1);
			*buf_size *= 2;
		}
		uc = 0;
		count = 0;
		i++;
		return ;
	}

	uc <<= 1;
	count++;
}

static void	exit_server(char **buf)
{
	free(*buf);
	system("leaks server");
	exit(0);
}

static int	buf_init(char **buf, size_t *buf_size)
{
	*buf_size = BUF_SIZE;
	*buf = (char *)malloc(sizeof(char) * (*buf_size));
	if (*buf == NULL)
		return (0);
	ft_memset(*buf, '\0', *buf_size);
	return (1);
}

static void error_exit(char *msg)
{
	ft_putendl_fd(msg, STDERR_FILENO);
	exit(1);
}

static void	main_loop(char **buf, size_t *buf_size)
{
	while (1)
	{
		if (g_signal.sig == SIGUSR1 || g_signal.sig == SIGUSR2)
			recieve_bit(buf, buf_size, g_signal.sig);
		if (g_signal.sig == SIGQUIT || g_signal.sig == SIGINT)
			exit_server(buf);
		pause();
	}
}

static void sig_block_set(struct sigaction *sa, sigset_t *block)
{
	if ((sigemptyset(block) != 0)
		|| (sigaddset(block, SIGUSR1) != 0)
		|| (sigaddset(block, SIGUSR2) != 0))
		error_exit("sigset error in main");

	sa->sa_sigaction = &handle_signal;
	sa->sa_mask = *block;
	sa->sa_flags = SA_SIGINFO | SA_RESTART;

	if ((sigaction(SIGUSR1, sa, NULL) < 0)
		|| (sigaction(SIGUSR2, sa, NULL) < 0)
		|| (sigaction(SIGQUIT, sa, NULL) < 0)
		|| (sigaction(SIGINT, sa, NULL) < 0))
		error_exit("sigaction error in main");
}

int	main(void)
{
	struct sigaction	sa;
	sigset_t			block;
	char				*buf;
	size_t				buf_size;

	ft_memset(&sa, '\0', sizeof(sa));
	sig_block_set(&sa, &block);

	printf("PID is [%d]\n", getpid());
	if (!buf_init(&buf, &buf_size))
		error_exit("buf_init error in main");
	main_loop(&buf, &buf_size);
	return (0);
}

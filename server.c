/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 09:21:13 by tsekiguc          #+#    #+#             */
/*   Updated: 2021/11/03 11:01:28 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

volatile sig_atomic_t	g_recieve_signal;

static void	handle_signal(int signal)
{
	g_recieve_signal = signal;
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
	i = 0;
	while (i < buf_size)
	{
		ret[i] = buf[i];
		i++;
	}
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
		if ((*buf)[i] == 0x04)
		{
			(*buf)[i] = '\0';
			printf("%s\n", *buf);
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

static void	exit_server(char *buf)
{
	free(buf);
	system("leaks server");
	exit(0);
}

int	main(void)
{
	struct sigaction	sa;
	sigset_t			block;
	int					ret;
	char				*buf;
	size_t				buf_size;

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
	if (sigaction(SIGQUIT, &sa, NULL) < 0)
	{
		perror("sigaction");
		exit(1);
	}
	if (sigaction(SIGINT, &sa, NULL) < 0)
	{
		perror("sigaction");
		exit(1);
	}

	printf("PID is [%ld]\n", (long)getpid());

	buf_size = 1000;
	buf = (char *)malloc(sizeof(char) * buf_size);
	if (buf == NULL)
		return (1);
	memset(buf, '\0', buf_size);

	while (1)
	{
		if (g_recieve_signal == SIGUSR1 || g_recieve_signal == SIGUSR2)
			recieve_bit(&buf, &buf_size, g_recieve_signal);
		if (g_recieve_signal == SIGQUIT || g_recieve_signal == SIGINT)
			exit_server(buf);
		pause();
	}

	system("leaks server");
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 09:21:13 by tsekiguc          #+#    #+#             */
/*   Updated: 2021/11/03 10:09:10 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

volatile sig_atomic_t	g_recieve_signal;

static void	handle_signal(int signal)
{
	g_recieve_signal = signal;
}

char	*str_resize(char *str, size_t size)
{
	char	*ret;
	size_t	resize;
	size_t	i;

	if (str == NULL)
		return (NULL);

	if (SIZE_MAX - size < size)
	{
		free(str);
		return (NULL);
	}
	resize = size * 2;
	ret = (char *)malloc(sizeof(char) * resize);
	if (ret == NULL)
	{
		free(str);
		return (NULL);
	}
	memset(ret, '\0', resize);
	i = 0;
	while (i < size)
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	//free(str);
	return (ret);
}

static void	recieve_bit(char *str, size_t *size, int g_recieve_signal)
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
		str[i] = (char)uc;
		if (str[i] == 0x04)
		{
			printf("%s\n", str);
			memset(str, '\0', *size);
			uc = 0;
			count = 0;
			i = 0;
			return ;
		}
		uc = 0;
		count = 0;
		i++;
		return ;
	}

	uc <<= 1;
	count++;
}

static void	exit_server(char *str)
{
	free(str);
	system("leaks server");
	exit(0);
}

int	main(void)
{
	struct sigaction	sa;
	sigset_t			block;
	int					ret;
	char				*str;
	size_t				size;

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

	size = 100;
	str = (char *)malloc(sizeof(char) * size);
	if (str == NULL)
		return (1);
	memset(str, '\0', size);

	while (1)
	{
		if (g_recieve_signal == SIGUSR1 || g_recieve_signal == SIGUSR2)
			recieve_bit(str, &size, g_recieve_signal);
		if (g_recieve_signal == SIGQUIT || g_recieve_signal == SIGINT)
			exit_server(str);
		pause();
	}

	system("leaks server");
	return (0);
}

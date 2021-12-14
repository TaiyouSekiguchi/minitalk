/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_recieve_signal.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:40:52 by tsekiguc          #+#    #+#             */
/*   Updated: 2021/11/09 16:05:58 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void	signal_to_bit(unsigned char *uc, int signal)
{
	if (signal == SIGUSR1)
	{
		*uc |= 0;
	}
	else if (signal == SIGUSR2)
	{
		*uc |= 1;
	}
}

static void	recieve_fin(char *buf, size_t buf_size, pid_t c_pid, size_t *i)
{
	ft_putendl_fd(buf, STDOUT_FILENO);
	if (usleep(100) < 0)
		error_free_exit("usleep error in recieve_fin", buf);
	if (kill(c_pid, SIGUSR1) < 0)
		error_free_exit("kill error in recieve_fin", buf);
	ft_memset(buf, '\0', buf_size);
	*i = 0;
}

static void	do_buf_resize(char **buf, size_t *buf_size)
{
	*buf = buf_resize(*buf, *buf_size);
	if (*buf == NULL)
		error_exit("buf_resize error in do_buf_resize");
	*buf_size *= 2;
}

void	recieve_signal(char **buf, size_t *buf_size, int signal, pid_t c_pid)
{
	static unsigned char	uc;
	static size_t			count;
	static size_t			i;

	signal_to_bit(&uc, signal);
	if (count == 7)
	{
		(*buf)[i] = (char)uc;
		if ((*buf)[i] == '\0')
			recieve_fin(*buf, *buf_size, c_pid, &i);
		else
		{
			if (i == *buf_size - 1)
				do_buf_resize(buf, buf_size);
			i++;
		}
		uc = 0;
		count = 0;
		return ;
	}
	uc <<= 1;
	count++;
}

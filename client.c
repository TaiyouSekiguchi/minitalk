/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 10:47:56 by tsekiguc          #+#    #+#             */
/*   Updated: 2021/11/02 16:19:38 by tsekiguc         ###   ########.fr       */
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

int	main(int argc, char *argv[])
{
	pid_t			pid;
	char			*str;
	int				i;

	if (argc != 3)
	{
		printf("How to use client  \"./client  [server PID]  [send message]\"");
		return (0);
	}

	pid = atoi(argv[1]);
	str = argv[2];

	i = 0;
	while (str[i] != '\0')
	{
		sent_bit((unsigned char)str[i], pid);
		i++;
	}

	sent_bit(0x04, pid);

	return (0);
}

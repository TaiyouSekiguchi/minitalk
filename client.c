/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 10:47:56 by tsekiguc          #+#    #+#             */
/*   Updated: 2021/11/02 10:55:14 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

int	main(int argc, char *argv[])
{
	pid_t			pid;
	char			*str;
	int				i;
	unsigned char	uc;
	unsigned char	ans;
	unsigned char	bit;

	pid = atoi(argv[1]);
	str = argv[2];

	i = argc;
	i = 0;
	while (str[i] != '\0')
	{
		printf("str[%d] is %c (%d)\n", i, str[i], (int)str[i]);
		printf("%d is ", (int)str[i]);
		uc = (unsigned char)str[i];
		bit = 1 << 7;
		while (bit != 0)
		{
			ans = uc & bit;
			if (ans == 0)
			{
				printf("0");
				if (kill(pid, SIGUSR1) < 0)
					return (1);
			}
			else
			{
				printf("1");
				if (kill(pid, SIGUSR2) < 0)
					return (1);
			}
			bit >>= 1;
			usleep(100000);
		}
		printf("\n");
		i++;
	}

	uc = 0x04;
	bit = 1 << 7;
	while (bit != 0)
	{
		ans = uc & bit;
		if (ans == 0)
		{
			if (kill(pid, SIGUSR1) < 0)
				return (1);
		}
		else
		{
			if (kill(pid, SIGUSR2) < 0)
				return (1);
		}
		bit >>= 1;
		usleep(100000);
	}

	return (0);
}

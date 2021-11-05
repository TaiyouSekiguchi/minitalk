/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:45:36 by tsekiguc          #+#    #+#             */
/*   Updated: 2021/11/05 11:09:08 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <stdio.h>
# include <string.h>

# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include "libft.h"

# define BUF_SIZE 10

typedef struct	s_signal
{
	volatile int	sig;
	volatile pid_t	pid;
}				t_signal;

#endif

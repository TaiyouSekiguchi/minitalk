/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:45:36 by tsekiguc          #+#    #+#             */
/*   Updated: 2021/11/10 15:45:01 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <signal.h>
# include "libft.h"

# define BUF_SIZE 10

typedef struct s_signal
{
	volatile int	sig;
	volatile pid_t	pid;
}				t_signal;

int		buf_init(char **buf, size_t *buf_size);
char	*buf_resize(char *buf, size_t buf_size);
void	error_exit(char *msg);
void	error_free_exit(char *msg, char *buf);
void	recieve_signal(char **buf, size_t *buf_size, int signal, pid_t c_pid);

#endif

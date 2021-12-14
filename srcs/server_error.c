/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 09:21:13 by tsekiguc          #+#    #+#             */
/*   Updated: 2021/11/09 16:04:18 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	error_exit(char *msg)
{
	ft_putendl_fd(msg, STDERR_FILENO);
	exit(1);
}

void	error_free_exit(char *msg, char *buf)
{
	ft_putendl_fd(msg, STDERR_FILENO);
	free(buf);
	exit(1);
}

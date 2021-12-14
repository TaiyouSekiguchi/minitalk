/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_buf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:23:01 by tsekiguc          #+#    #+#             */
/*   Updated: 2021/11/09 15:23:04 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int	buf_init(char **buf, size_t *buf_size)
{
	*buf_size = BUF_SIZE;
	*buf = (char *)malloc(sizeof(char) * (*buf_size));
	if (*buf == NULL)
		return (0);
	ft_memset(*buf, '\0', *buf_size);
	return (1);
}

char	*buf_resize(char *buf, size_t buf_size)
{
	char	*ret;
	size_t	resize;

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
	ft_memcpy(ret, buf, buf_size);
	free(buf);
	return (ret);
}

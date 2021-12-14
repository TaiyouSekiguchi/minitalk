/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 19:23:30 by tsekiguc          #+#    #+#             */
/*   Updated: 2021/07/14 19:24:44 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ucs;
	unsigned char	ucc;
	size_t			i;

	ucs = (unsigned char *)s;
	ucc = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (ucs[i] == ucc)
			return (&ucs[i]);
		i++;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 19:04:32 by tsekiguc          #+#    #+#             */
/*   Updated: 2021/07/14 19:14:32 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*ucdst;
	unsigned char	*ucsrc;
	size_t			i;

	if (len == 0 || dst == src)
		return (dst);
	ucdst = (unsigned char *)dst;
	ucsrc = (unsigned char *)src;
	i = 0;
	if (ucdst > ucsrc)
	{
		while (len--)
			ucdst[len] = ucsrc[len];
	}
	else
	{
		while (len--)
			*ucdst++ = *ucsrc++;
	}
	return (dst);
}

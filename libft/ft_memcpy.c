/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 18:57:59 by tsekiguc          #+#    #+#             */
/*   Updated: 2021/07/14 19:01:05 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*ucdst;
	unsigned char	*ucsrc;
	size_t			i;

	if (n == 0 || dst == src)
		return (dst);
	ucdst = (unsigned char *)dst;
	ucsrc = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		ucdst[i] = ucsrc[i];
		i++;
	}
	return (dst);
}

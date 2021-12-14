/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 19:03:46 by tsekiguc          #+#    #+#             */
/*   Updated: 2021/07/16 11:47:07 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*ucdst;
	unsigned char	*ucsrc;
	unsigned char	ucc;
	size_t			i;

	ucdst = (unsigned char *)dst;
	ucsrc = (unsigned char *)src;
	ucc = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		ucdst[i] = ucsrc[i];
		if (ucdst[i] == ucc)
			return (&ucdst[i + 1]);
		i++;
	}
	return (NULL);
}

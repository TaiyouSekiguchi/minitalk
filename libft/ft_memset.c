/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 18:50:13 by tsekiguc          #+#    #+#             */
/*   Updated: 2021/07/14 18:56:51 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ub;
	unsigned char	uc;
	size_t			i;

	ub = (unsigned char *)b;
	uc = (unsigned char)c;
	i = 0;
	while (i < len)
	{
		ub[i] = uc;
		i++;
	}
	return (b);
}

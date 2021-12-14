/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 19:36:55 by tsekiguc          #+#    #+#             */
/*   Updated: 2021/07/15 12:00:15 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*ret;
	char	cc;
	size_t	len;
	size_t	i;

	ret = (char *)s;
	cc = (char)c;
	len = ft_strlen(s);
	i = 0;
	while (i <= len)
	{
		if (ret[i] == cc)
			return (&ret[i]);
		i++;
	}
	return (NULL);
}

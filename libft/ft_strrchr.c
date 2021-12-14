/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 19:40:16 by tsekiguc          #+#    #+#             */
/*   Updated: 2021/08/18 11:48:57 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ret;
	char	cc;
	size_t	len;
	size_t	i;

	ret = NULL;
	cc = (char)c;
	len = ft_strlen(s);
	i = 0;
	while (i <= len)
	{
		if (s[i] == cc)
			ret = (char *)&s[i];
		i++;
	}
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 14:14:21 by tsekiguc          #+#    #+#             */
/*   Updated: 2021/07/15 14:34:27 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*empty_string(void)
{
	char	*ret;

	ret = (char *)malloc(sizeof(char));
	if (ret == NULL)
		return (NULL);
	*ret = '\0';
	return (ret);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	count;
	size_t	i;

	if (s == NULL)
		return (NULL);
	if (ft_strlen(s) <= start || len <= 0)
		return (empty_string());
	count = ft_strlen(s + start);
	if (count < len)
		len = count;
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ret[i] = s[start + i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

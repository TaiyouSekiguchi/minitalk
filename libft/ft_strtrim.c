/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 20:34:09 by tsekiguc          #+#    #+#             */
/*   Updated: 2021/07/15 20:48:30 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ret;
	size_t	start;
	int		i;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = 0;
	i = 0;
	while (s1[i] != '\0')
	{
		if (ft_strchr(set, (int)s1[i]) == NULL)
			break ;
		start++;
		i++;
	}
	i = ft_strlen(s1) - 1;
	while (i >= 0)
	{
		if (ft_strchr(set, (int)s1[i]) == NULL)
			break ;
		i--;
	}
	ret = ft_substr(s1, start, i + 1 - start);
	return (ret);
}

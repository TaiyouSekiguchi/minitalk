/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 15:01:15 by tsekiguc          #+#    #+#             */
/*   Updated: 2021/07/16 11:43:48 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	char	*tmp;
	char	*cp1;
	char	*cp2;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	cp1 = (char *)s1;
	cp2 = (char *)s2;
	ret = (char *)malloc(sizeof(char) * (ft_strlen(cp1) + ft_strlen(cp2) + 1));
	if (ret == NULL)
		return (NULL);
	tmp = ret;
	while (*cp1 != '\0')
		*tmp++ = *cp1++;
	while (*cp2 != '\0')
		*tmp++ = *cp2++;
	*tmp = '\0';
	return (ret);
}

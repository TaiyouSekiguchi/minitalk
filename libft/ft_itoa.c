/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 12:23:34 by tsekiguc          #+#    #+#             */
/*   Updated: 2021/08/02 23:26:34 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	get_ret(int n, int order, char *ret)
{
	unsigned int	copy;
	int				num;
	int				i;

	i = 0;
	if (n < 0)
	{
		ret[i++] = '-';
		copy = n * -1;
	}
	else
		copy = n;
	while (order != 0)
	{
		num = copy / order;
		ret[i++] = num + '0';
		copy %= order;
		order /= 10;
	}
	ret[i] = '\0';
}

char	*ft_itoa(int n)
{
	char	*ret;
	int		copy;
	int		digit;
	int		order;

	copy = n;
	if (copy < 0)
		digit = 2;
	else
		digit = 1;
	order = 1;
	while (copy / 10 != 0)
	{
		copy /= 10;
		digit++;
		order *= 10;
	}
	ret = (char *)malloc(sizeof(char) * (digit + 1));
	if (ret == NULL)
		return (NULL);
	get_ret(n, order, ret);
	return (ret);
}

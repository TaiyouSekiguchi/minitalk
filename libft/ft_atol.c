/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 16:00:17 by tsekiguc          #+#    #+#             */
/*   Updated: 2021/11/10 16:00:20 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(const char *str)
{
	unsigned long	num;
	int				minus;
	size_t			i;

	minus = 0;
	num = 0;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			minus = 1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (!ft_long_check(num, str[i] - '0', minus))
			return (0);
		num = num * 10 + (str[i++] - '0');
	}
	if (minus == 0)
		return ((long)num);
	else
		return ((long)(num * -1));
}

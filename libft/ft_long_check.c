/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_long_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 11:43:05 by tsekiguc          #+#    #+#             */
/*   Updated: 2021/11/04 14:52:45 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_long_check(unsigned long num, unsigned long add, int minus)
{
	unsigned long	num_limit;
	unsigned long	add_limit;
	unsigned long	max;

	max = LONG_MAX;
	if (minus == 1)
		max++;
	num_limit = max / 10;
	add_limit = max % 10;
	if (num > num_limit
		|| (num == num_limit && add > add_limit))
		return (0);
	return (1);
}

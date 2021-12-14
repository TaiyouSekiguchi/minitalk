/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_long_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 10:28:43 by tsekiguc          #+#    #+#             */
/*   Updated: 2021/11/11 10:39:43 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_long_fd(long n, int fd)
{
	unsigned long	copy;
	int				div;
	int				mod;

	if (n < 0)
	{
		write(fd, "-", 1);
		copy = n * -1;
	}
	else
		copy = n;
	mod = copy % 10 + '0';
	div = copy / 10;
	if (div > 0)
		ft_putnbr_long_fd(div, fd);
	write(fd, &mod, 1);
}

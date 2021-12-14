/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 11:17:00 by tsekiguc          #+#    #+#             */
/*   Updated: 2021/08/02 22:27:12 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	copy;
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
		ft_putnbr_fd(div, fd);
	write(fd, &mod, 1);
}

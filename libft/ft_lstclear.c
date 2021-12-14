/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 11:33:55 by tsekiguc          #+#    #+#             */
/*   Updated: 2021/07/16 11:35:05 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*tmp;

	if (lst == NULL || *lst == NULL)
		return ;
	current = *lst;
	while (current != NULL)
	{
		tmp = current -> next;
		(*del)(current -> content);
		free(current);
		current = tmp;
	}
	*lst = NULL;
}

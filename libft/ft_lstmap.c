/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsekiguc <tsekiguc@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 11:35:19 by tsekiguc          #+#    #+#             */
/*   Updated: 2021/07/16 11:37:09 by tsekiguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*current;
	t_list	*ret;
	t_list	*new;

	if (lst == NULL)
		return (NULL);
	ret = NULL;
	current = lst;
	while (current != NULL)
	{
		new = ft_lstnew((*f)(current->content));
		if (new == NULL)
		{
			ft_lstclear(&ret, (*del));
			return (NULL);
		}
		ft_lstadd_back(&ret, new);
		current = current->next;
	}
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 01:53:35 by minjungk          #+#    #+#             */
/*   Updated: 2022/07/15 22:02:34 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*new;
	void	*tmp;

	if (lst == 0 || f == 0)
		return (0);
	head = 0;
	while (lst)
	{
		tmp = f(lst->content);
		new = ft_lstnew(tmp);
		if (new == 0)
		{
			if (tmp)
				free(tmp);
			ft_lstclear(&head, del);
			return (0);
		}
		ft_lstadd_back(&head, new);
		lst = lst->next;
	}
	new = 0;
	return (head);
}

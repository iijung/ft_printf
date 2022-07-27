/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 01:53:35 by minjungk          #+#    #+#             */
/*   Updated: 2022/07/26 23:48:48 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*tail;
	t_list	*new;
	void	*tmp;

	head = 0;
	tail = 0;
	while (lst && f)
	{
		tmp = f(lst->content);
		new = ft_lstnew(tmp);
		if (new == 0)
		{
			free(tmp);
			ft_lstclear(&head, del);
			return (0);
		}
		if (head == 0)
			head = new;
		ft_lstadd_back(&tail, new);
		tail = new;
		lst = lst->next;
	}
	return (head);
}

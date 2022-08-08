/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 04:45:14 by minjungk          #+#    #+#             */
/*   Updated: 2022/08/09 01:41:12 by iijung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	parse_tokens(t_list *lst, va_list ap)
{
	int		len;
	int		total;
	t_token	*token;

	total = 0;
	while (lst && lst->content)
	{
		token = lst->content;
		if (ft_parse_token(token, ap) < 0 || token->out == 0)
			return (total);
		if (token->width == 0)
			token->width = ft_strlen(token->out);
		len = write(1, token->out, token->width);
		if (len < 0)
			return (total);
		total += len;
		lst = lst->next;
	}
	return (total);
}

int	ft_printf(const char *format, ...)
{
	t_list	*head;
	int		total;
	va_list	ap;

	total = -1;
	va_start(ap, format);
	head = ft_make_tokens(format);
	if (head)
	{
		total = parse_tokens(head, ap);
		ft_lstclear(&head, ft_free_token);
	}
	va_end(ap);
	return (total);
}

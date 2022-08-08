/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 04:45:14 by minjungk          #+#    #+#             */
/*   Updated: 2022/08/08 08:48:48 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_list	*make_tokens(const char *format)
{
	t_list		*head;
	t_list		*tmp;
	t_token		*token;
	size_t		len;

	head = 0;
	len = 0;
	while (format && format[len])
	{
		token = ft_make_token((char *)format + len);
		if (token == 0)
			break ;
		tmp = ft_lstnew(token);
		if (tmp == 0 || token->in == 0)
		{
			ft_free_token(token);
			break ;
		}
		ft_lstadd_back(&head, tmp);
		len += ft_strlen(token->in);
	}
	return (head);
}

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
		if (token->opt.width == 0)
			token->opt.width = ft_strlen(token->out);
		len = write(1, token->out, token->opt.width);
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
	head = make_tokens(format);
	if (head)
	{
		total = parse_tokens(head, ap);
		ft_lstclear(&head, ft_free_token);
	}
	va_end(ap);
	return (total);
}

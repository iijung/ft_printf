/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 02:55:52 by minjungk          #+#    #+#             */
/*   Updated: 2022/07/27 04:51:15 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_show_tokens(t_list	*token, t_list	*option, va_list ap)
{
	char	*tmp;
	size_t	total;
	size_t	len;

	total = 0;
	while (token && option)
	{
		if (option->content == 0)
		{
			len = ft_strlen(token->content);
			ft_putendl_fd(token->content, 1);
		}
		else
		{
			tmp = ft_parse(option->content, ap);
			len = ft_strlen(tmp);
			ft_putendl_fd(tmp, 1);
			free(tmp);
		}
		total += len;
		token = token->next;
		option = option->next;
	}
	return (total);
}

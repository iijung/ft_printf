/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 04:45:14 by minjungk          #+#    #+#             */
/*   Updated: 2022/07/27 08:52:12 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	t_list	*token_list;
	t_list	*option_list;
	size_t	total;
	va_list	ap;

	total = 0;
	va_start(ap, format);
	token_list = ft_make_tokens(format);
	option_list = ft_lstmap(token_list, ft_get_option, free);
	total = ft_show_tokens(token_list, option_list, ap);
	va_end(ap);
	ft_lstclear(&token_list, free);
	ft_lstclear(&option_list, free);
	return (total);
}

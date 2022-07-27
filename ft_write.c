/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 02:55:52 by minjungk          #+#    #+#             */
/*   Updated: 2022/07/27 12:12:21 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	show_token(char *token, t_option *opt, va_list ap)
{
	size_t	len;
	char	*new;

	len = 0;
	if (opt->text == 1)
		new = ft_strdup(token);
	else
		new = ft_parse(opt, ap);
	if (new == 0)
		return (0);
	len = ft_strlen(new);
	if (opt->type == 'c' && new[0] == 0)
		len = 1;
	ft_putstr_fd(new, 1);
	free(new);
	return (len);
}

size_t	ft_show_tokens(t_list *token, t_list *opt, va_list ap)
{
	size_t	total;
	size_t	len;

	total = 0;
	while (token && opt)
	{
		if (opt->content == 0)
			return (total);
		else
			len = show_token(token->content, opt->content, ap);
		total += len;
		token = token->next;
		opt = opt->next;
	}
	return (total);
}

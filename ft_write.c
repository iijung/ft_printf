/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 02:55:52 by minjungk          #+#    #+#             */
/*   Updated: 2022/07/27 13:13:18 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	show_token(char *token, t_option *opt, va_list ap)
{
	size_t	len;
	char	*tmp;

	if (opt->text == 1)
		tmp = ft_strdup(token);
	else
		tmp = ft_parse(opt, ap);
	if (tmp == 0)
		return (0);
	len = ft_strlen(tmp);
	if (opt->type == 'c')
		len = 1;
	write(1, tmp, len);
	free(tmp);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 02:45:22 by minjungk          #+#    #+#             */
/*   Updated: 2022/08/08 06:31:45 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_flags(char *f, t_token *token)
{
	int	len;

	len = 1;
	while (f[len] == '#' || f[len] == ' ' || f[len] == '0'
		|| f[len] == '+' || f[len] == '-')
	{
		if (f[len] == '#')
			token->opt.found = 1;
		else if (f[len] == ' ')
			token->opt.blank = 1;
		else if (f[len] == '0')
			token->opt.zero = 1;
		else if (f[len] == '+')
			token->opt.plus = 1;
		else if (f[len] == '-')
			token->opt.minus = 1;
		++len;
	}
	return (len);
}

static int	get_option(char *f, t_token *token)
{
	int	len;

	if (f[0] != '%')
		return (ft_strchr(f, '%') - f);
	len = get_flags(f, token);
	token->opt.width = ft_atoi(f + len);
	while (ft_isdigit(f[len]))
		++len;
	if (f[len] == '.')
	{
		token->opt.precision = 1;
		++len;
		token->opt.length = ft_atoi(f + len);
		while (ft_isdigit(f[len]))
			++len;
	}
	token->opt.type = f[len];
	if (token->opt.type == 'p')
		token->opt.found = 1;
	++len;
	return (len);
}

t_token	*ft_make_token(void *content)
{
	int		len;
	char	*fmt;
	t_token	*token;

	if (content == 0)
		return (0);
	token = ft_calloc(1, sizeof(t_token));
	if (token == 0)
		return (0);
	fmt = content;
	len = get_option(content, token);
	if (len < 0)
		token->in = ft_strdup(fmt);
	else
		token->in = ft_substr(fmt, 0, len);
	return (token);
}

void	ft_free_token(void *content)
{
	t_token	*token;

	if (content == 0)
		return ;
	token = content;
	free(token->in);
	free(token->out);
	token->in = 0;
	token->out = 0;
	free(content);
}

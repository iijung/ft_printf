/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 02:45:22 by minjungk          #+#    #+#             */
/*   Updated: 2022/08/08 15:32:21 by iijung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_flags(char *f, t_token *t)
{
	int	len;

	len = 1;
	while (f[len] == '#' || f[len] == ' ' || f[len] == '0'
		|| f[len] == '+' || f[len] == '-')
	{
		if (f[len] == '#')
			t->opt |= FOUND;
		else if (f[len] == ' ')
			t->opt |= BLANK;
		else if (f[len] == '0')
			t->opt |= ZERO;
		else if (f[len] == '+')
			t->opt |= PLUS;
		else if (f[len] == '-')
			t->opt |= MINUS;
		++len;
	}
	return (len);
}

static int	get_option(char *f, t_token *t)
{
	int	len;

	if (f[0] != '%')
		return (ft_strchr(f, '%') - f);
	len = get_flags(f, t);
	t->width = ft_atoi(f + len);
	while (ft_isdigit(f[len]))
		++len;
	if (f[len] == '.')
	{
		t->opt |= PREC;
		++len;
		t->length = ft_atoi(f + len);
		while (ft_isdigit(f[len]))
			++len;
	}
	t->type = f[len];
	if (t->type == 'p')
		t->opt |= FOUND;
	++len;
	return (len);
}

t_token	*ft_make_token(void *content)
{
	int		len;
	char	*fmt;
	t_token	*t;

	if (content == 0)
		return (0);
	t = ft_calloc(1, sizeof(t_token));
	if (t == 0)
		return (0);
	fmt = content;
	len = get_option(content, t);
	if (len < 0)
		t->in = ft_strdup(fmt);
	else
		t->in = ft_substr(fmt, 0, len);
	if ((t->opt & BLANK) && (t->opt & PLUS))
		t->opt &= ~BLANK;
	if ((t->opt & ZERO) && (t->opt & MINUS))
		t->opt &= ~ZERO;
	if (t->type != 'd' && t->type != 'i')
		t->opt &= ~(PLUS | BLANK);
	return (t);
}

void	ft_free_token(void *content)
{
	t_token	*t;

	if (content == 0)
		return ;
	t = content;
	free(t->in);
	free(t->out);
	t->in = 0;
	t->out = 0;
	free(content);
}

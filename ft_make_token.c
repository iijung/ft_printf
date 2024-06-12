/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 02:45:22 by minjungk          #+#    #+#             */
/*   Updated: 2024/06/13 03:37:31 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_free_token(void *content)
{
	t_token *const	t = content;

	if (content == NULL)
		return ;
	free(t->in);
	free(t->out);
	t->in = NULL;
	t->out = NULL;
	free(content);
}

static int	get_option(char *f, t_token *t, int len)
{
	while (ft_strchr("# 0+-", f[len]) != NULL)
	{
		t->opt |= FOUND * (f[len] == '#');
		t->opt |= BLANK * (f[len] == ' ');
		t->opt |= ZERO * (f[len] == '0');
		t->opt |= PLUS * (f[len] == '+');
		t->opt |= MINUS * (f[len] == '-');
		++len;
	}
	t->width = ft_atoi(f + len);
	while (ft_isdigit(f[len]))
		++len;
	t->type = f[len++];
	t->opt |= PREC * (t->type == '.');
	t->opt |= FOUND * (t->type == 'p');
	if (t->type == '.')
	{
		t->precision = ft_atoi(f + len);
		while (ft_isdigit(f[len]))
			++len;
		t->type = f[len++];
	}
	return (len);
}

static t_token	*ft_make_token(void *content)
{
	int				len;
	char			*fmt;
	t_token *const	t = ft_calloc(1, sizeof(t_token));

	if (t == NULL)
		return (NULL);
	fmt = content;
	if (fmt[0] != '%')
		len = ft_strchr(fmt, '%') - fmt;
	else
		len = get_option(content, t, 1);
	if (len < 0)
		t->in = ft_strdup(fmt);
	else
		t->in = ft_substr(fmt, 0, len);
	if (t->opt & PLUS)
		t->opt &= ~BLANK;
	if (t->opt & MINUS)
		t->opt &= ~ZERO;
	if (t->type != 'd' && t->type != 'i')
		t->opt &= ~(PLUS | BLANK);
	return (t);
}

int	ft_make_tokens(t_list **head, const char *format)
{
	t_list		*tmp;
	t_token		*token;
	size_t		len;

	len = 0;
	while (format && format[len])
	{
		token = ft_make_token((char *)format + len);
		if (token == NULL)
			return (-1);
		tmp = ft_lstnew(token);
		if (tmp == NULL || token->in == NULL)
		{
			free(tmp);
			ft_free_token(token);
			return (-1);
		}
		ft_lstadd_back(head, tmp);
		len += ft_strlen(token->in);
	}
	return (0);
}

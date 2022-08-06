/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 04:50:52 by minjungk          #+#    #+#             */
/*   Updated: 2022/08/07 02:37:37 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
#include <stdio.h>

void	ft_debug(t_token *token)
{
	if (token == 0)
		return ;
	printf("=== debug ===\n");
	printf("in [%3ld] : %.*s\n", \
		token->in ? ft_strlen(token->in) : 0, \
		token->in ? (int)ft_strlen(token->in) : 0, token->in);
	printf("out[%3ld] : %.*s\n", \
		token->out ? ft_strlen(token->out) : 0, \
		token->out ? (int)ft_strlen(token->out) : 0, token->out);
	printf("-------------\n");
	printf("found: %d\n", token->opt.found);
	printf("blank: %d\n", token->opt.blank);
	printf("plus : %d\n", token->opt.plus);
	printf("minus: %d\n", token->opt.minus);
	printf("zero : %d\n", token->opt.zero);
	printf(".    : %d\n", token->opt.precision);
	printf("width: %u\n", token->opt.width);
	printf("len  : %u\n", token->opt.length);
	printf("type : %c\n", token->opt.type);
	printf("=============\n");
}
*/

static int	parse_char(t_token *token, char c)
{
	if (token->opt.width == 0)
		token->opt.width = 1;
	token->out = ft_calloc(token->opt.width + 1, sizeof(char));
	if (token->out == 0)
		return (-1);
	if (token->opt.minus == 0 && token->opt.zero)
		ft_memset(token->out, '0', token->opt.width);
	else
		ft_memset(token->out, ' ', token->opt.width);
	if (token->opt.minus)
		token->out[0] = c;
	else
		token->out[token->opt.width - 1] = c;
	return (0);
}

static int	parse_string(t_token *token, char *s)
{
	if (s == 0)
		s = "(null)";
	if (token->opt.precision == 0 || token->opt.length >= (int)ft_strlen(s))
		token->opt.length = ft_strlen(s);
	if (token->opt.width < token->opt.length)
		token->opt.width = token->opt.length;
	token->out = ft_calloc(token->opt.width + 1, sizeof(char));
	if (token->out == 0)
		return (-1);
	if (token->opt.minus == 0 && token->opt.zero)
		ft_memset(token->out, '0', token->opt.width);
	else
		ft_memset(token->out, ' ', token->opt.width);
	if (token->opt.minus)
		ft_memcpy(token->out, s, token->opt.length);
	else
		ft_memcpy(token->out + token->opt.width - token->opt.length, \
				s, token->opt.length);
	return (0);
}

int	ft_parse_token(t_token *token, va_list ap)
{
	if (token == 0)
		return (-1);
	if (token->opt.type == 'c')
		return (parse_char(token, va_arg(ap, int)));
	else if (token->opt.type == 's')
		return (parse_string(token, va_arg(ap, char *)));
	else if (token->opt.type == '%')
		token->out = ft_strdup("%");
	else if (token->opt.type == 'd' || token->opt.type == 'i')
		token->out = ft_itoa(va_arg(ap, int));
	else if (token->opt.type == 'u')
		token->out = ft_utoa(va_arg(ap, unsigned int));
	else if (token->opt.type == 'x')
		token->out = ft_utoa(va_arg(ap, unsigned int));
	else if (token->opt.type == 'X')
		token->out = ft_utoa(va_arg(ap, unsigned int));
	else if (token->opt.type == 'p')
		token->out = ft_utoh(va_arg(ap, unsigned long), 0, 1);
	else
		token->out = ft_strdup(token->in);
	if (token->out == 0)
		return (-1);
	return (0);
}

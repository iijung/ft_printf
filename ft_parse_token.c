/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 04:50:52 by minjungk          #+#    #+#             */
/*   Updated: 2022/08/08 11:21:16 by iijung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

static int	parse_c(t_token *token, char c)
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

static int	parse_s(t_token *token, char *s)
{
	if (s == 0 && token->opt.precision && token->opt.length < (int)ft_strlen("(null)"))
		s = "";
	else if (s == 0)
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

/* ************************************************************************** */
static int	parse_puxX(t_token *token, unsigned long ul)
{
	char	*tmp;

	if (token->opt.type == 'p' && ul == 0)
	{
		token->out = ft_strdup("(nil)");
		return (0);
	}
	if (token->opt.type == 'u')
		tmp = ft_utoa(ul, "0123456789");
	else
		tmp = ft_utoa(ul, "0123456789abcdef");
	token->opt.length = ft_strlen(tmp);
	if (token->opt.width < (int)ft_strlen(tmp) + 2 * token->opt.found)
		token->opt.width = ft_strlen(tmp) + 2 * token->opt.found;
	token->out = ft_calloc(token->opt.width + 1, sizeof(char));
	if (token->out == 0)
	{
		free(tmp);
		return (-1);
	}
	if (token->opt.minus == 0 && token->opt.zero)
		ft_memset(token->out, '0', token->opt.width);
	else
		ft_memset(token->out, ' ', token->opt.width);
	if (token->opt.minus)
		ft_memcpy(token->out + 2 * token->opt.found, tmp, token->opt.length);
	else
		ft_memcpy(token->out + token->opt.width - token->opt.length, \
				tmp, token->opt.length);
	if (token->opt.found && token->opt.minus && ul)
		ft_memcpy(token->out, "0x", 2);
	if (token->opt.found && token->opt.minus == 0 && ul)
		ft_memcpy(token->out + token->opt.width - token->opt.length - 2, \
				"0x", 2);
	free(tmp);
	return (0);
}

static int	parse_di(t_token *token, int num)
{
	int	flag;
	char	*tmp;

	tmp = ft_itoa(num);
	flag = num >= 0 && (token->opt.blank || token->opt.plus);
	if (token->opt.width < (int)ft_strlen(tmp) + flag)
		token->opt.width = ft_strlen(tmp) + flag;
	token->out = ft_calloc(token->opt.width + 1, sizeof(char));
	if (token->out == 0)
	{
		free(tmp);
		return (-1);
	}
	if (token->opt.minus == 0 && token->opt.zero)
		ft_memset(token->out, '0', token->opt.width);
	else
		ft_memset(token->out, ' ', token->opt.width);
	if (token->opt.minus)
		ft_memcpy(token->out + flag, tmp, token->opt.length);
	else
		ft_memcpy(token->out + token->opt.width - ft_strlen(tmp), tmp, ft_strlen(tmp));
	free(tmp);
	return (0);
}

int	ft_parse_token(t_token *token, va_list ap)
{
	if (token == 0)
		return (-1);
	if (token->opt.type == 0)
		token->out = ft_strdup(token->in);
	else if (token->opt.type == '%')
		token->out = ft_strdup("%");
	else if (token->opt.type == 'c')
		return (parse_c(token, va_arg(ap, int)));
	else if (token->opt.type == 's')
		return (parse_s(token, va_arg(ap, char *)));
	else if (token->opt.type == 'd' || token->opt.type == 'i')
		return (parse_di(token, va_arg(ap, int)));
	else if (token->opt.type == 'u')
		return (parse_puxX(token, va_arg(ap, unsigned int)));
	else if (token->opt.type == 'x' || token->opt.type == 'X')
		return (parse_puxX(token, va_arg(ap, unsigned int)));
	else if (token->opt.type == 'p')
		return (parse_puxX(token, va_arg(ap, unsigned long)));
	if (token->out == 0)
		return (-1);
	return (0);
}

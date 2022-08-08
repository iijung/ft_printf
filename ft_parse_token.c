/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 04:50:52 by minjungk          #+#    #+#             */
/*   Updated: 2022/08/08 12:28:57 by iijung           ###   ########.fr       */
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
	printf("found: %d\n", token->opt & FOUND);
	printf("blank: %d\n", token->opt & BLANK);
	printf("plus : %d\n", token->opt & PLUS);
	printf("minus: %d\n", token->opt & MINUS);
	printf("zero : %d\n", token->opt & ZERO);
	printf(".    : %d\n", token->opt & PREC);
	printf("width: %u\n", token->width);
	printf("len  : %u\n", token->length);
	printf("type : %c\n", token->type);
	printf("=============\n");
}

static int	parse_c(t_token *token, char c)
{
	if (token->width == 0)
		token->width = 1;
	token->out = ft_calloc(token->width + 1, sizeof(char));
	if (token->out == 0)
		return (-1);
	if ((token->opt & MINUS) == 0 && token->opt & ZERO)
		ft_memset(token->out, '0', token->width);
	else
		ft_memset(token->out, ' ', token->width);
	if (token->opt & MINUS)
		token->out[0] = c;
	else
		token->out[token->width - 1] = c;
	return (0);
}

static int	parse_s(t_token *token, char *s)
{
	if (s == 0 && token->opt & PREC && token->length < (int)ft_strlen("(null)"))
		s = "";
	else if (s == 0)
		s = "(null)";
	if ((token->opt & PREC) == 0 || token->length >= (int)ft_strlen(s))
		token->length = ft_strlen(s);
	if (token->width < token->length)
		token->width = token->length;
	token->out = ft_calloc(token->width + 1, sizeof(char));
	if (token->out == 0)
		return (-1);
	if ((token->opt & MINUS) == 0 && (token->opt & ZERO))
		ft_memset(token->out, '0', token->width);
	else
		ft_memset(token->out, ' ', token->width);
	if (token->opt & MINUS)
		ft_memcpy(token->out, s, token->length);
	else
		ft_memcpy(token->out + token->width - token->length, \
				s, token->length);
	return (0);
}

/* ************************************************************************** */
static int	parse_puxX(t_token *token, unsigned long ul)
{
	char	*tmp;

	if (token->type == 'p' && ul == 0)
	{
		token->out = ft_strdup("(nil)");
		return (0);
	}
	if (token->type == 'u')
		tmp = ft_utoa(ul, "0123456789");
	else
		tmp = ft_utoa(ul, "0123456789abcdef");
	token->length = ft_strlen(tmp);
	if (token->width < (int)ft_strlen(tmp) + (int)(2 * (token->opt & FOUND)))
		token->width = ft_strlen(tmp) + 2 * (token->opt & FOUND);
	token->out = ft_calloc(token->width + 1, sizeof(char));
	if (token->out == 0)
	{
		free(tmp);
		return (-1);
	}
	if ((token->opt & MINUS) == 0 && (token->opt & ZERO))
		ft_memset(token->out, '0', token->width);
	else
		ft_memset(token->out, ' ', token->width);
	if (token->opt & MINUS)
		ft_memcpy(token->out + 2 * (token->opt & FOUND), tmp, token->length);
	else
		ft_memcpy(token->out + token->width - token->length, \
				tmp, token->length);
	if ((token->opt & FOUND) && (token->opt & MINUS) && ul)
		ft_memcpy(token->out, "0x", 2);
	if ((token->opt & FOUND) && (token->opt & MINUS) == 0 && ul)
		ft_memcpy(token->out + token->width - token->length - 2, "0x", 2);
	free(tmp);
	return (0);
}

static int	parse_di(t_token *token, int num)
{
	int	flag;
	char	*tmp;

	tmp = ft_itoa(num);
	flag = num >= 0 && (token->opt & (BLANK | PLUS));
	if (token->width < (int)ft_strlen(tmp) + flag)
		token->width = ft_strlen(tmp) + flag;
	token->out = ft_calloc(token->width + 1, sizeof(char));
	if (token->out == 0)
	{
		free(tmp);
		return (-1);
	}
	if ((token->opt & MINUS) == 0 && (token->opt & ZERO))
		ft_memset(token->out, '0', token->width);
	else
		ft_memset(token->out, ' ', token->width);
	if (token->opt & MINUS)
		ft_memcpy(token->out + flag, tmp, token->length);
	else
		ft_memcpy(token->out + token->width - ft_strlen(tmp), tmp, ft_strlen(tmp));
	free(tmp);
	return (0);
}

int	ft_parse_token(t_token *token, va_list ap)
{
	if (token == 0)
		return (-1);
	if (token->type == 0)
		token->out = ft_strdup(token->in);
	else if (token->type == '%')
		token->out = ft_strdup("%");
	else if (token->type == 'c')
		return (parse_c(token, va_arg(ap, int)));
	else if (token->type == 's')
		return (parse_s(token, va_arg(ap, char *)));
	else if (token->type == 'd' || token->type == 'i')
		return (parse_di(token, va_arg(ap, int)));
	else if (token->type == 'u')
		return (parse_puxX(token, va_arg(ap, unsigned int)));
	else if (token->type == 'x' || token->type == 'X')
		return (parse_puxX(token, va_arg(ap, unsigned int)));
	else if (token->type == 'p')
		return (parse_puxX(token, va_arg(ap, unsigned long)));
	if (token->out == 0)
		return (-1);
	return (0);
}

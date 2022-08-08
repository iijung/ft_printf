/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 04:50:52 by minjungk          #+#    #+#             */
/*   Updated: 2022/08/08 12:38:48 by iijung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#include <stdio.h>

void	ft_debug(t_token *t)
{
	if (t == 0)
		return ;
	printf("=== debug ===\n");
	printf("in [%3ld] : %.*s\n", \
		t->in ? ft_strlen(t->in) : 0, \
		t->in ? (int)ft_strlen(t->in) : 0, t->in);
	printf("out[%3ld] : %.*s\n", \
		t->out ? ft_strlen(t->out) : 0, \
		t->out ? (int)ft_strlen(t->out) : 0, t->out);
	printf("-------------\n");
	printf("found: %d\n", t->opt & FOUND);
	printf("blank: %d\n", t->opt & BLANK);
	printf("plus : %d\n", t->opt & PLUS);
	printf("minus: %d\n", t->opt & MINUS);
	printf("zero : %d\n", t->opt & ZERO);
	printf(".    : %d\n", t->opt & PREC);
	printf("width: %u\n", t->width);
	printf("len  : %u\n", t->length);
	printf("type : %c\n", t->type);
	printf("=============\n");
}

static int	parse_c(t_token *t, char c)
{
	if (t->width == 0)
		t->width = 1;
	t->out = ft_calloc(t->width + 1, sizeof(char));
	if (t->out == 0)
		return (-1);
	if ((t->opt & MINUS) == 0 && t->opt & ZERO)
		ft_memset(t->out, '0', t->width);
	else
		ft_memset(t->out, ' ', t->width);
	if (t->opt & MINUS)
		t->out[0] = c;
	else
		t->out[t->width - 1] = c;
	return (0);
}

static int	parse_s(t_token *t, char *s)
{
	if (s == 0 && t->opt & PREC && t->length < (int)ft_strlen("(null)"))
		s = "";
	else if (s == 0)
		s = "(null)";
	if ((t->opt & PREC) == 0 || t->length >= (int)ft_strlen(s))
		t->length = ft_strlen(s);
	if (t->width < t->length)
		t->width = t->length;
	t->out = ft_calloc(t->width + 1, sizeof(char));
	if (t->out == 0)
		return (-1);
	if ((t->opt & MINUS) == 0 && (t->opt & ZERO))
		ft_memset(t->out, '0', t->width);
	else
		ft_memset(t->out, ' ', t->width);
	if (t->opt & MINUS)
		ft_memcpy(t->out, s, t->length);
	else
		ft_memcpy(t->out + t->width - t->length, s, t->length);
	return (0);
}

/* ************************************************************************** */
static int	parse_puxX(t_token *t, unsigned long ul)
{
	char	*tmp;

	if (t->type == 'p' && ul == 0)
	{
		t->out = ft_strdup("(nil)");
		return (0);
	}
	if (t->type == 'u')
		tmp = ft_utoa(ul, "0123456789");
	else
		tmp = ft_utoa(ul, "0123456789abcdef");
	t->length = ft_strlen(tmp);
	if (t->width < (int)ft_strlen(tmp) + (int)(2 * (t->opt & FOUND)))
		t->width = ft_strlen(tmp) + 2 * (t->opt & FOUND);
	t->out = ft_calloc(t->width + 1, sizeof(char));
	if (t->out == 0)
	{
		free(tmp);
		return (-1);
	}
	if ((t->opt & MINUS) == 0 && (t->opt & ZERO))
		ft_memset(t->out, '0', t->width);
	else
		ft_memset(t->out, ' ', t->width);
	if (t->opt & MINUS)
		ft_memcpy(t->out + 2 * (t->opt & FOUND), tmp, t->length);
	else
		ft_memcpy(t->out + t->width - t->length, tmp, t->length);
	if ((t->opt & FOUND) && (t->opt & MINUS) && ul)
		ft_memcpy(t->out, "0x", 2);
	if ((t->opt & FOUND) && (t->opt & MINUS) == 0 && ul)
		ft_memcpy(t->out + t->width - t->length - 2, "0x", 2);
	free(tmp);
	return (0);
}

static int	parse_di(t_token *t, int num)
{
	int	flag;
	char	*tmp;

	tmp = ft_itoa(num);
	t->length = ft_strlen(tmp);
	flag = num >= 0 && (t->opt & (BLANK | PLUS));
	if (t->width < (int)ft_strlen(tmp) + flag)
		t->width = ft_strlen(tmp) + flag;
	t->out = ft_calloc(t->width + 1, sizeof(char));
	if (t->out == 0)
	{
		free(tmp);
		return (-1);
	}
	if ((t->opt & MINUS) == 0 && (t->opt & ZERO))
		ft_memset(t->out, '0', t->width);
	else
		ft_memset(t->out, ' ', t->width);
	if (t->opt & MINUS)
		ft_memcpy(t->out + flag, tmp, t->length);
	else
		ft_memcpy(t->out + t->width - ft_strlen(tmp), tmp, ft_strlen(tmp));
	free(tmp);
	return (0);
}

int	ft_parse_token(t_token *t, va_list ap)
{
	if (t == 0)
		return (-1);
	if (t->type == 0)
		t->out = ft_strdup(t->in);
	else if (t->type == '%')
		t->out = ft_strdup("%");
	else if (t->type == 'c')
		return (parse_c(t, va_arg(ap, int)));
	else if (t->type == 's')
		return (parse_s(t, va_arg(ap, char *)));
	else if (t->type == 'd' || t->type == 'i')
		return (parse_di(t, va_arg(ap, int)));
	else if (t->type == 'u')
		return (parse_puxX(t, va_arg(ap, unsigned int)));
	else if (t->type == 'x' || t->type == 'X')
		return (parse_puxX(t, va_arg(ap, unsigned int)));
	else if (t->type == 'p')
		return (parse_puxX(t, va_arg(ap, unsigned long)));
	if (t->out == 0)
		return (-1);
	return (0);
}

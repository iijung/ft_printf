/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 04:50:52 by minjungk          #+#    #+#             */
/*   Updated: 2022/08/09 02:09:16 by iijung           ###   ########.fr       */
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
	printf("len  : %u\n", t->precision);
	printf("type : %c\n", t->type);
	printf("=============\n");
}

static void make_out(t_token *t, char *copy)
{
	int	len;

	if (t->type != 's' && copy && t->precision < (int)ft_strlen(copy))
		t->precision = ft_strlen(copy);
	if (t->width < t->precision)
		t->width = t->precision;
	t->out = ft_calloc(t->width + 1, sizeof(char));
	if (t->out == 0)
		return ;
	ft_memset(t->out, ' ', t->width);
	if (t->opt & ZERO)
		ft_memset(t->out, '0', t->width);
	if (copy == 0)
		return ;
	len = t->precision;
	if (t->type != 's')
		len = ft_strlen(copy);
	if (t->opt & MINUS)
		ft_memcpy(t->out, copy, len);
	else
		ft_memcpy(t->out + t->width - len, copy, len);
}

static int	parse_text(t_token *t, va_list ap)
{
	char	*s;

	if (t->type == 'c')
	{
		t->precision = 1;
		make_out(t, "");
		t->out[0] = va_arg(ap, int);
	}
	else if (t->type == 's')
	{
		s = va_arg(ap, char *);
		if (s == 0 && t->opt & PREC && t->precision < (int)ft_strlen("(null)"))
			s = "";
		else if (s == 0)
			s = "(null)";
		if ((t->opt & PREC) == 0 || t->precision >= (int)ft_strlen(s))
			t->precision = ft_strlen(s);
		make_out(t, s);
	}
	return (0);
}

static int	parse_number(t_token *t, va_list ap)
{
	char	*s;

	if (t->type == 'u')
		s = ft_utoa(va_arg(ap, unsigned int), "0123456789");
	else
		s = ft_itoa(va_arg(ap, int));
	if (s == 0)
		return (-1);
	if (t->opt & PREC)
	{
		t->width = t->precision + (s[0] == '-' || (t->opt & (PLUS | BLANK)));
		t->opt |= ZERO;
		t->opt &= ~MINUS;
	}
	t->precision = ft_strlen(s);
	make_out(t, s);
	if (s[0] == '-' && (t->opt & ZERO))
	{
		t->out[t->width - t->precision] = '0';
		t->out[0] = '-';
	}

	free(s);
	return (0);
}


/* ************************************************************************** */
static int	parse_pxX(t_token *t, unsigned long ul)
{
	char	*tmp;

	if (t->type == 'p' && ul == 0)
	{
		t->width = ft_strlen("(nil)");
		t->out = ft_strdup("(nil)");
		return (0);
	}
	tmp = ft_utoa(ul, "0123456789abcdef");
	t->precision = ft_strlen(tmp);
	if (t->width < (int)ft_strlen(tmp) + (int)(2 * (t->opt & FOUND)))
		t->width = ft_strlen(tmp) + 2 * (t->opt & FOUND);
	t->out = ft_calloc(t->width + 1, sizeof(char));
	if (t->out == 0)
	{
		free(tmp);
		return (-1);
	}
	if (t->opt & ZERO)
		ft_memset(t->out, '0', t->width);
	else
		ft_memset(t->out, ' ', t->width);
	if (t->opt & MINUS)
		ft_memcpy(t->out + 2 * (t->opt & FOUND), tmp, t->precision);
	else
		ft_memcpy(t->out + t->width - t->precision, tmp, t->precision);
	if ((t->opt & FOUND) && (t->opt & MINUS) && ul)
		ft_memcpy(t->out, "0x", 2);
	if ((t->opt & FOUND) && (t->opt & MINUS) == 0 && ul)
		ft_memcpy(t->out + t->width - t->precision - 2, "0x", 2);
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
	else if (t->type == 'c' || t->type == 's')
		return (parse_text(t, ap));
	else if (t->type == 'd' || t->type == 'i' || t->type == 'u')
		return (parse_number(t, ap));
	else if (t->type == 'x' || t->type == 'X')
		return (parse_pxX(t, va_arg(ap, unsigned int)));
	else if (t->type == 'p')
		return (parse_pxX(t, va_arg(ap, unsigned long)));
	if (t->out == 0)
		return (-1);
	return (0);
}

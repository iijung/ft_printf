/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 04:50:52 by minjungk          #+#    #+#             */
/*   Updated: 2022/08/10 05:57:32 by iijung           ###   ########.fr       */
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
	printf("prec : %u\n", t->precision);
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
		t->precision = t->width;
	if (t->opt & MINUS)
		ft_memset(t->out, '0', t->precision);
	else
		ft_memset(t->out + t->width - t->precision, '0', t->precision);
	if (copy == 0)
		return ;
	len = t->precision;
	if (t->type != 's')
		len = ft_strlen(copy);
	if (t->opt & MINUS)
		ft_memcpy(t->out + t->precision - len, copy, len);
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

static int	parse_number(t_token *t, char *s)
{
	char	flag;

	if (s == 0)
		return (-1);
	if (s[0] == '-')
		flag = '-';
	else if (t->opt & PLUS)
		flag = '+';
	else if (t->opt & BLANK)
		flag = ' ';
	else
		flag = 0;
	if (t->precision < (int)ft_strlen(s))
		t->precision = (int)ft_strlen(s);
	if (flag)
		t->precision += (flag != '-' || (t->opt & PREC));
	if (s[0] == '-')
		make_out(t, s + 1);
	else
		make_out(t, s);
	if (flag && t->opt & MINUS)
		t->out[0] = flag;
	else if (flag)
		t->out[t->width - t->precision] = flag;
	free(s);
	return (0);
}

static int	parse_pxX(t_token *t, char *s)
{
	if (s == 0)
		return (-1);
	if (t->type == 'p' && s[0] == '0')
	{
		make_out(t, "(nil)");
		free(s);
		return (0);
	}
	if (!(t->opt & PREC))
		t->precision = ft_strlen(s);
	if (t->opt & FOUND)
		t->precision += 2 * (1 && s[0] != '0');
	make_out(t, s);
	if ((t->opt & FOUND) && (t->opt & MINUS))
		ft_memcpy(t->out, "0x", 2);
	if ((t->opt & FOUND) && !(t->opt & MINUS))
		ft_memcpy(t->out + t->width - t->precision, "0x", 2);
	int len = -1;
	while (s[0] != '0' && t->type == 'X' && t->out[++len])
		t->out[len] = ft_toupper(t->out[len]);
	free(s);
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
	else if (t->type == 'd' || t->type == 'i')
		return (parse_number(t, ft_itoa(va_arg(ap, int))));
	else if (t->type == 'u')
		return (parse_number(t, ft_utoa(va_arg(ap, unsigned int), "0123456789")));
	else if (t->type == 'x' || t->type == 'X')
		return (parse_pxX(t, ft_utoa(va_arg(ap, unsigned int), "0123456789abcdef")));
	else if (t->type == 'p')
		return (parse_pxX(t, ft_utoa(va_arg(ap, unsigned long), "0123456789abcdef")));
	if (t->out == 0)
		return (-1);
	return (0);
}

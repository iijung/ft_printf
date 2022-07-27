/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 04:50:52 by minjungk          #+#    #+#             */
/*   Updated: 2022/07/27 12:14:15 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

static char	*get_text(char type, va_list ap)
{
	char	*tmp;
	char	*rtn;

	rtn = 0;
	if (type == 'c')
	{
		rtn = ft_calloc(2, sizeof(char));
		if (rtn)
			rtn[0] = va_arg(ap, int);
	}
	else if (type == 's')
	{
		tmp = va_arg(ap, char *);
		if (tmp)
			rtn = ft_strdup(tmp);
	}
	if (rtn == 0)
		return (ft_strdup("(null)"));
	return (rtn);
}

char	*ft_parse(t_option *opt, va_list ap)
{
	if (opt->type == '%')
		return (ft_strdup("%"));
	if (opt->type == 'c' || opt->type == 's')
		return (get_text(opt->type, ap));
	if (opt->type == 'd' || opt->type == 'i')
		return (ft_itoa(va_arg(ap, int)));
	if (opt->type == 'u')
		return (ft_utoa(va_arg(ap, unsigned int)));
	if (opt->type == 'x' || opt->type == 'X')
		return (ft_utoh(va_arg(ap, unsigned int), \
					opt->type == 'X', opt->flag_found));
	if (opt->type == 'p')
		return (ft_utoh(va_arg(ap, unsigned long), 0, 1));
	return (ft_strdup("(null)"));
}

/*
	printf("=== debug ===\n");
	printf("text : %d\n", opt->text);
	printf("found: %d\n", opt->flag_found);
	printf("blank: %d\n", opt->flag_blank);
	printf("plus : %d\n", opt->flag_plus);
	printf("minus: %d\n", opt->flag_minus);
	printf("zero : %d\n", opt->flag_zero);
	printf("width: %u\n", opt->width);
	printf("len  : %u\n", opt->length);
	printf("type : %c\n", opt->type);
	printf("=============\n");
 */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 04:45:14 by minjungk          #+#    #+#             */
/*   Updated: 2022/07/17 15:24:09 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	size_t	total;
	size_t	read;
	va_list	ap;

	total = 0;
	va_start(ap, format);
	while (format && *format)
	{
		if (*format != '%')
		{
			ft_putchar_fd(*format, 1);
			++total;
		}
		else
		{
			read = ft_put_syntax(format);
		}
		++format;
	}
	va_end(ap);
	return (0);
}

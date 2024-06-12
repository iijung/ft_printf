/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 04:45:14 by minjungk          #+#    #+#             */
/*   Updated: 2024/06/13 04:52:38 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_printf_util.h"

int	ft_printf(const char *format, ...)
{
	int		total;
	va_list	ap;

	va_start(ap, format);
	total = ft_vprintf(format, ap);
	va_end(ap);
	return (total);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	int		total;
	va_list	ap;

	va_start(ap, format);
	total = ft_vdprintf(fd, format, ap);
	va_end(ap);
	return (total);
}

int	ft_vprintf(const char *format, va_list ap)
{
	return (ft_vdprintf(STDOUT_FILENO, format, ap));
}

int	ft_vdprintf(int fd, const char *format, va_list ap)
{
	t_token	*token;
	size_t	len;
	int		ret;
	int		total;

	len = 0;
	total = 0;
	while (format && format[len] != '\0')
	{
		ret = -1;
		token = ft_make_token(format + len);
		if (0 == ft_parse_token(token, ap) && token->out)
		{
			if (token->width == 0)
				token->width = ft_strlen(token->out);
			ret = write(fd, token->out, token->width);
			total += ret;
			len += ft_strlen(token->in);
		}
		ft_free_token(token);
		if (ret < 0)
			return (0);
	}
	return (total);
}

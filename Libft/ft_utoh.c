/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 22:05:50 by minjungk          #+#    #+#             */
/*   Updated: 2022/07/27 12:21:58 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	nlen(unsigned long n)
{
	size_t	len;

	if (n == 0)
		return (1);
	len = 0;
	while (n)
	{
		++len;
		n /= 16;
	}
	return (len);
}

static char	*null_text(int is_upper, int is_prefix)
{
	if (is_prefix == 0)
		return (ft_strdup("0"));
	if (is_upper)
		return (ft_strdup("0X0"));
	else
		return (ft_strdup("0x0"));
}

char	*ft_utoh(unsigned long n, int is_upper, int is_prefix)
{
	size_t	i;
	char	ch;
	char	*rtn;

	if (n == 0)
		return (null_text(is_upper, is_prefix));
	i = nlen(n) + (2 * is_prefix);
	rtn = (char *)ft_calloc(i + 1, sizeof(char));
	while (rtn && n)
	{
		ch = n % 16;
		if (ch < 10)
			rtn[--i] = ch + '0';
		else
			rtn[--i] = ch + 'a' - 10 - (32 * is_upper);
		n /= 16;
	}
	if (rtn && is_prefix)
	{
		rtn[0] = '0';
		rtn[1] = 'x' - (32 * is_upper);
	}
	return (rtn);
}

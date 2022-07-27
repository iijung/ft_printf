/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 22:05:50 by minjungk          #+#    #+#             */
/*   Updated: 2022/07/27 10:57:30 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	numlen(unsigned long n)
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

char	*ft_utoh(unsigned long n, int is_upper, int is_prefix)
{
	size_t	i;
	char	ch;
	char	*rtn;

	if (n == 0)
		return (ft_strdup("0"));
	i = numlen(n) + (2 * is_prefix);
	rtn = (char *)ft_calloc(i + 1, sizeof(char));
	if (rtn == 0)
		return (0);
	while (n)
	{
		ch = n % 16;
		if (ch < 10)
			rtn[--i] = ch + '0';
		else
			rtn[--i] = ch + 'a' - 10 - (32 * is_upper);
		n /= 16;
	}
	if (is_prefix)
	{
		rtn[0] = '0';
		rtn[1] = 'x' - (32 * is_upper);
	}
	return (rtn);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 20:10:10 by minjungk          #+#    #+#             */
/*   Updated: 2022/07/15 19:28:38 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

int	ft_atoi(const char *str)
{
	int				sign;
	unsigned long	rtn;

	rtn = 0;
	sign = 1;
	while ((9 <= *str && *str <= 13) || *str == ' ')
		++str;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		++str;
	}
	while ('0' <= *str && *str <= '9')
	{
		rtn = rtn * 10 + *str - '0';
		if (sign > 0 && rtn > (unsigned long)LONG_MAX)
			return ((int)LONG_MAX);
		if (sign < 0 && rtn > (unsigned long)LONG_MIN)
			return ((int)LONG_MIN);
		++str;
	}
	rtn *= sign;
	return ((int)rtn);
}

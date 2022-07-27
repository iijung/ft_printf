/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 22:05:50 by minjungk          #+#    #+#             */
/*   Updated: 2022/07/27 09:46:42 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	numlen(unsigned int n)
{
	int	len;

	if (n == 0)
		return (1);
	len = 0;
	while (n)
	{
		++len;
		n /= 10;
	}
	return (len);
}

char	*ft_utoa(unsigned int n)
{
	int		i;
	char	*rtn;

	if (n == 0)
		return (ft_strdup("0"));
	i = numlen(n);
	rtn = (char *)ft_calloc(i + 1, sizeof(char));
	if (rtn == 0)
		return (0);
	while (n)
	{
		rtn[--i] = n % 10 + '0';
		n /= 10;
	}
	return (rtn);
}

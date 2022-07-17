/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 20:34:42 by minjungk          #+#    #+#             */
/*   Updated: 2022/07/06 21:45:15 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	slen;

	i = 0;
	slen = 0;
	while (src[slen])
		++slen;
	if (dstsize == 0)
		return (slen);
	while (i + 1 < dstsize && src[i])
	{
		dst[i] = src[i];
		++i;
	}
	dst[i] = 0;
	return (slen);
}

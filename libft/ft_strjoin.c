/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 15:35:40 by minjungk          #+#    #+#             */
/*   Updated: 2022/07/10 01:20:46 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	dlen;
	char	*dst;

	if (s1 == 0 || s2 == 0)
		return (0);
	dlen = ft_strlen(s1) + ft_strlen(s2);
	dst = (char *)ft_calloc(dlen + 1, sizeof(char));
	if (dst)
	{
		ft_strlcat(dst, s1, dlen + 1);
		ft_strlcat(dst, s2, dlen + 1);
	}
	return (dst);
}

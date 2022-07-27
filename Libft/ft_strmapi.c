/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 23:53:23 by minjungk          #+#    #+#             */
/*   Updated: 2022/07/10 01:20:58 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	slen;
	char	*rtn;

	if (s == 0)
		return (0);
	i = -1;
	slen = ft_strlen(s);
	rtn = (char *)ft_calloc(slen + 1, sizeof(char));
	while (rtn && s[++i])
		rtn[i] = f(i, s[i]);
	return (rtn);
}

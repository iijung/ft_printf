/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_util.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 04:51:08 by minjungk          #+#    #+#             */
/*   Updated: 2024/06/13 04:53:40 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_UTIL_H
# define FT_PRINTF_UTIL_H
# include <stdarg.h>
# include "libft.h"

typedef enum e_option
{
	NONE	= 0,
	FOUND	= 1 << 0,
	BLANK	= 1 << 1,
	PLUS	= 1 << 2,
	MINUS	= 1 << 3,
	ZERO	= 1 << 4,
	PREC	= 1 << 5
}			t_option;

typedef struct s_token
{
	char		*in;
	char		*out;
	char		type;
	int			width;
	int			precision;
	t_option	opt;
}				t_token;

extern void		ft_free_token(void *content);
extern t_token	*ft_make_token(const char *fmt);
extern int		ft_parse_token(t_token *t, va_list ap);

#endif

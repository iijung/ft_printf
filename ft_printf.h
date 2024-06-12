/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 11:03:12 by minjungk          #+#    #+#             */
/*   Updated: 2024/06/13 03:24:12 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
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

int		ft_printf(const char *format, ...);
#endif

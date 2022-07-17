/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 11:03:12 by minjungk          #+#    #+#             */
/*   Updated: 2022/07/17 14:57:10 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include "libft.h"

typedef enum e_flag
{
	FLAG_POUND,
	FLAG_BLANK,
	FLAG_PLUS,
	FLAG_MINUS,
	FLAG_ZERO
}			t_flag;

typedef enum e_type
{
	TYPE_CHAR,
	TYPE_STRING,
	TYPE_POINTER,
	TYPE_DECIMAL,
	TYPE_INTEGER,
	TYPE_UNSIGNED,
	TYPE_HEXADECIAML_SMALL,
	TYPE_HEXADECIAML_BIG,
	TYPE_PERCENTAGE
}			t_type;

typedef struct s_option
{
	t_flag			flag;
	t_type			type;
	int				width;
	int				length;
}				t_option;

int	ft_printf(const char *format, ...);
#endif

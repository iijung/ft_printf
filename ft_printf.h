/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 11:03:12 by minjungk          #+#    #+#             */
/*   Updated: 2022/08/07 01:16:01 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include "libft.h"

typedef struct s_option
{
	int			found;
	int			blank;
	int			plus;
	int			minus;
	int			zero;
	int			precision;
	int			width;
	int			length;
	char		type;
}				t_option;

typedef struct s_token
{
	char		*in;
	char		*out;
	t_option	opt;
}				t_token;

void	ft_free_token(void *content);
t_token	*ft_make_token(void *content);
int		ft_parse_token(t_token *token, va_list ap);

int		ft_printf(const char *format, ...);
#endif

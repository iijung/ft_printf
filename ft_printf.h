/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 11:03:12 by minjungk          #+#    #+#             */
/*   Updated: 2022/07/27 04:53:28 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include "libft.h"

typedef struct s_option
{
	int				text;
	int				flag_found;
	int				flag_blank;
	int				flag_plus;
	int				flag_minus;
	int				flag_zero;
	unsigned int	width;
	unsigned int	length;
	char			type;
}				t_option;

t_list	*ft_make_tokens(const char *format);
void	*ft_get_option(void	*content);
char	*ft_parse(t_option	*option, va_list ap);
size_t	ft_show_tokens(t_list	*token, t_list	*option, va_list ap);

int	ft_printf(const char *format, ...);
#endif

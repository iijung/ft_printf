/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 02:45:22 by minjungk          #+#    #+#             */
/*   Updated: 2022/07/27 11:16:56 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	get_token_len(char *str)
{
	size_t	len;

	if (str == 0)
		return (0);
	len = 1;
	while (str[len] == '#' || str[len] == ' ' || str[len] == '0'
		|| str[len] == '+' || str[len] == '-')
		++len;
	while (ft_isdigit(str[len]))
		++len;
	if (str[len] == '.')
	{
		++len;
		while (ft_isdigit(str[len]))
			++len;
	}
	++len;
	return (len);
}

t_list	*ft_make_tokens(const char *format)
{
	t_list	*rtn;
	t_list	*token;
	char	*curr;
	char	*next;
	size_t	len;

	rtn = 0;
	curr = (char *)format;
	while (curr && *curr)
	{
		next = ft_strchr(curr, '%');
		token = ft_lstnew(ft_substr(curr, 0, next - curr));
		ft_lstadd_back(&rtn, token);
		if (next)
		{
			len = get_token_len(next);
			token = ft_lstnew(ft_substr(next, 0, len));
			ft_lstadd_back(&rtn, token);
			next += len;
		}
		curr = next;
	}
	return (rtn);
}

static char	*get_flags(char *str, t_option *option)
{
	size_t	len;

	len = 1;
	while (str[len] == '#' || str[len] == ' ' || str[len] == '0'
		|| str[len] == '+' || str[len] == '-')
	{
		if (str[len] == '#')
			option->flag_found = 1;
		else if (str[len] == ' ')
			option->flag_blank = 1;
		else if (str[len] == '0')
			option->flag_zero = 1;
		else if (str[len] == '+')
			option->flag_plus = 1;
		else if (str[len] == '-')
			option->flag_minus = 1;
		++len;
	}
	return (str + len);
}

static char	*get_remain(char *str, t_option *option)
{
	size_t	len;

	len = 0;
	option->width = ft_atoi(str);
	while (ft_isdigit(str[len]))
		++len;
	if (str[len] == '.')
	{
		++len;
		option->length = ft_atoi(str + len);
		while (ft_isdigit(str[len]))
			++len;
	}
	option->type = str[len];
	++len;
	return (str + len);
}

void	*ft_get_option(void	*content)
{
	char		*curr;
	t_option	*option;

	curr = content;
	option = ft_calloc(1, sizeof(t_option));
	if (option == 0)
		return (0);
	if (*curr != '%')
		option->text = 1;
	else
	{
		curr = get_flags(curr, option);
		curr = get_remain(curr, option);
	}
	return (option);
}

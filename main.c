/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 11:43:34 by minjungk          #+#    #+#             */
/*   Updated: 2022/07/27 02:41:55 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"

int	main(void)
{
	int	result;

	printf("$$\n");
//	result = ft_printf("%dHello\n");
	printf("0123456789ABCDEF0123456789ABCDEF\n");
//	result = ft_printf("num : %d\tfloat : %f\n char : %c\t str : %s$$\n", 123, 12.3, 'A', "hi test");
	result = ft_printf("num : %  +++  +0-d\tfloat : %f\n char : %c\t str : %s$$\n", 123, 12.3, 'A', "hi test");
	printf("print_word is %d\n", result);
	return (0);
}

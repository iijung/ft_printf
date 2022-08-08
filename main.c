/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 11:43:34 by minjungk          #+#    #+#             */
/*   Updated: 2022/08/08 08:55:29 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ft_printf.h"

int	main(void)
{
	int	num;
	int	result;

	srand(time(NULL));
	num = rand();

//	result = ft_printf("%dHello\n");
//	printf("0123456789ABCDEF0123456789ABCDEF\n");
//	result = ft_printf("%10c--\n", num % 128);
//	result = ft_printf("num : %d\tfloat : %f\n char : %c\t str : %s$$\n", 123, 12.3, 'A', "hi test");
//	result = ft_printf("num : %  +++  +0-d\tfloat : %f\n char : %c\t str : %s$$\n", 123, 12.3, 'A', "hi test");
//	result = ft_printf("== %20x ==\n", num);
//	printf("print_word is %d\n", result);
	result = printf("== %-p ==\n", &num);
	printf("print_word is %d\n", result);
	result = ft_printf("== %-p ==\n", &num);
	printf("print_word is %d\n", result);
	return (0);
}

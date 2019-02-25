/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 13:18:00 by stdenis           #+#    #+#             */
/*   Updated: 2019/02/25 17:22:29 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int		main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	long long		nb;
	nb = 5643254623165146555;
	short test;

	test = 4455;
	ft_printf("plus:%+hd ", test);
	printf("plus:%+hd ", test);
	/*ft_printf("space% lld ", nb);
	ft_printf("plus:%+lld ", nb);
	ft_printf("precision:%.5lld ", nb);
	ft_printf("space + prec:% .5lld ", nb);
	ft_printf("Plus + prec / grande:%+.5lld ", nb);
	ft_printf("Prec + 0:%0.5lld ", nb);
	ft_printf("Prec + minus:%-.5lld ", nb);
	ft_printf("size:%5lld ", nb);
	ft_printf("size + space:% 5lld ", nb);
	ft_printf("size + plus:%+5lld ", nb);
	ft_printf("size + minus:%-5lld ", nb);
	ft_printf("size + 0:%05lld ", nb);
	ft_printf("size + 0 + plus:%+05lld ", nb);
	ft_printf("size + 0 + plus:%0+5lld ", nb);
	ft_printf("size + 0 + prec:%05.3lld ", nb);
	ft_printf("size + minus + prec:%-5.3lld ", nb);
	ft_printf("size + plus + 0 + prec:%+05.3lld ", nb);
	ft_printf("size + espace + zero + prec:%0 5.3lld ", nb);
	ft_printf("size + espace + zero + prec:% 05.3lld ", nb);
	ft_printf("size + minus + plus + prec:%-+5.3lld ", nb);*/

	/*printf("space% lld ", nb);
	printf("plus:%+lld ", nb);
	printf("precision:%.5lld ", nb);
	printf("space + prec:% .5lld ", nb);
	printf("Plus + prec / grande:%+.5lld ", nb);
	printf("Prec + 0:%0.5lld ", nb);
	printf("Prec + minus:%-.5lld ", nb);
	printf("size:%5lld ", nb);
	printf("size + space:% 5lld ", nb);
	printf("size + plus:%+5lld ", nb);
	printf("size + minus:%-5lld ", nb);
	printf("size + 0:%05lld ", nb);
	printf("size + 0 + plus:%+05lld ", nb);
	printf("size + 0 + plus:%0+5lld ", nb);
	printf("size + 0 + prec:%05.3lld ", nb);
	printf("size + minus + prec:%-5.3lld ", nb);
	printf("size + plus + 0 + prec:%+05.3lld ", nb);
	printf("size + espace + zero + prec:%0 5.3lld ", nb);
	printf("size + espace + zero + prec:% 05.3lld ", nb);
	printf("size + minus + plus + prec:%-+5.3lld ", nb);*/
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 11:40:14 by stdenis           #+#    #+#             */
/*   Updated: 2019/02/28 14:16:40 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>
#include "ft_printf.h"


double	ft_modf(double a, double *b)
{
	unsigned long c;
	double d;

	c = (unsigned long)a;
	*b = (double)c;
	d = a - (double)c;
	return (d);
}

double	ft_modf_2(double a, double *b)
{
	unsigned long c;
	double d;

	c = (unsigned long)a;
/*	if (c > 5 && c < 9)
		c++;*/
	*b = (double)c;
	d = a - (double)c;
	return (d);
}

intmax_t	digits_after(double fl)
{
	intmax_t i;

	i = 0;
	while (fl > 1)
	{
		fl /= 10;
		i++;
	}
	return (i);
}
#include <stdio.h>
void	check_float(va_list ap, t_printf *tab)
{
	double		fl;
	double		res;
	int 		prec =20;
	intmax_t	size;

	(void)tab;
	fl = va_arg(ap, double);
	size = 0;
	while (fl > 1)
	{
		fl /= 10;
		size++;
	}
	while (size-- > 0)
	{
		fl = ft_modf(fl * 10, &res);
		fill_buffer((int)(res) + '0', tab);
	}
	fill_buffer('.', tab);
	while (fl > FLT_MIN && prec-- > 0)
	{
		fl = ft_modf_2(fl * 10, &res);
		if ((int)(res) == 9)
		{
			int lk = tab->buffer[tab->buff - 1] - '0';
			printf("|%d|\n", lk);
			if (lk != 0)
				tab->buffer[tab->buff - 1] = (lk + 1) + '0';
			fill_buffer(0 + '0', tab);
		}
		else if ((int)res > 5)
			fill_buffer((int)(res + 1) + '0', tab);
		else
			fill_buffer((int)(res) + '0', tab);
	}

}

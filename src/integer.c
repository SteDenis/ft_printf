/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 15:16:42 by stdenis           #+#    #+#             */
/*   Updated: 2019/02/25 17:35:28 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_buffer(long n, t_printf *tab)
{
	long	res;

	res = n;
	if (n < 0)
		fill_buffer('-', tab);
	res = (n < 0) ? (res * -1) : n;
	if (res > 9)
	{
		ft_putnbr_buffer(res / 10, tab);
		fill_buffer((res % 10) + '0', tab);
	}
	else
		fill_buffer(res + '0', tab);
}

void	fill_integer(long value, t_printf *tab)
{
	char	fill;

	fill = ' ';
	if (tab->arg.flag & ZERO)
		fill = '0';
	if (tab->arg.flag & ZERO && tab->arg.flag & PLUS)
		fill_buffer('+', tab);
	while (!(tab->arg.flag & MINUS) && tab->arg.larg-- > 0)
		fill_buffer(fill, tab);
	if (tab->arg.flag & SPACE)
		fill_buffer(' ', tab);
	if (!(tab->arg.flag & ZERO) && tab->arg.flag & PLUS)
		fill_buffer('+', tab);
	while (tab->arg.prec-- > 0)
		fill_buffer('0', tab);
	ft_putnbr_buffer(value, tab);
	while ((tab->arg.flag & MINUS) && tab->arg.larg-- > 0)
		fill_buffer(fill, tab);
}

size_t	int_length(long value)
{
	size_t	i;

	i = 0;
	if (value < 0)
		value *= -1;
	while (value > 0)
	{
		i++;
		value /= 10;
	}
	return (i);
}

void	prepare_int(long value, t_printf *tab)
{
	size_t	len;

	len = int_length(value);
	if (tab->arg.flag & PREC)
		tab->arg.prec = ((int)len < tab->arg.prec) ? tab->arg.prec - (int)len : 0;
	tab->arg.larg -= len;
	tab->arg.larg -= (tab->arg.prec > 0) ? tab->arg.prec : 0;
	if (tab->arg.flag & PLUS)
		tab->arg.larg--;
	if (tab->arg.flag & SPACE)
		tab->arg.larg--;
	fill_integer(value, tab);
}

void	prepare_short(short value, t_printf *tab)
{
	size_t	len;

	len = int_length(value);
	if (tab->arg.flag & PREC)
		tab->arg.prec = ((int)len < tab->arg.prec) ? tab->arg.prec - (int)len : 0;
	tab->arg.larg -= len;
	tab->arg.larg -= (tab->arg.prec > 0) ? tab->arg.prec : 0;
	if (tab->arg.flag & PLUS)
		tab->arg.larg--;
	if (tab->arg.flag & SPACE)
		tab->arg.larg--;
	fill_integer(value, tab);
}

void	check_integer(va_list ap, t_printf *tab)
{
	/*if (tab->arg.flag & H)
		prepare_short(va_arg(ap, short), tab);
	else if (tab->arg.flag & HH)
		prepare_char(va_arg(ap, int), tab);
	else if (tab->arg.flag & L)
		prepare_long(va_arg(ap, long), tab);
	else if (tab->arg.flag & LL)
		prepare_long_long(va_arg(ap, long long), tab);
	else*/
	if (tab->arg.flag & LL)
		prepare_int(va_arg(ap, long), tab);
	else
		prepare_int(va_arg(ap, int), tab);
}

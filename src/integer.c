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

#include <stdint.h>
#include "ft_printf.h"

void	ft_putnbr_buffer_pos(intmax_t res, t_printf *tab)
{
	if (res > 9)
	{
		ft_putnbr_buffer_pos(res / 10, tab);
		fill_buffer((res % 10) + '0', tab);
	}
	else if (res >= 0)
		fill_buffer(res + '0', tab);
}

void	ft_putnbr_buffer_neg(intmax_t res, t_printf *tab)
{
	if (res < -9)
	{
		ft_putnbr_buffer_neg(res / 10, tab);
		fill_buffer(-(res % 10) + '0', tab);
	}
	else if (res <= 0)
		fill_buffer((-res) + '0', tab);
}


void	fill_integer(intmax_t value, t_printf *tab)
{
	char	fill;
	bool	print;

	fill = ' ';
	print = (value == 0 && tab->arg.prec == 0 && tab->arg.flag & PREC) ? false : true;
	if (tab->arg.flag & ZERO)
	{
		fill = '0';
		if (value < 0)
			fill_buffer('-', tab);
	}
	if (tab->arg.flag & ZERO && tab->arg.flag & PLUS && value >= 0)
		fill_buffer('+', tab);
	while (!(tab->arg.flag & MINUS) && tab->arg.larg-- > 0)
		fill_buffer(fill, tab);
	if (tab->arg.flag & SPACE && value >= 0)
		fill_buffer(' ', tab);
	if (!(tab->arg.flag & ZERO) && tab->arg.flag & PLUS && value >= 0)
		fill_buffer('+', tab);
	if (!(tab->arg.flag & ZERO) && value < 0)
		fill_buffer('-', tab);
	while (tab->arg.prec-- > 0)
		fill_buffer('0', tab);
	if (print && value < 0)
		ft_putnbr_buffer_neg(value, tab);
	else if (print)
		ft_putnbr_buffer_pos(value, tab);
	while ((tab->arg.flag & MINUS) && tab->arg.larg-- > 0)
		fill_buffer(fill, tab);
}

size_t	int_length(intmax_t value)
{
	size_t	i;

	i = 0;
	if (value < 0)
	{
		value++;
		value *= -1;
	}
	while (value > 0)
	{
		i++;
		value /= 10;
	}
	return ((i == 0) ? 1 : i);
}

void	prepare_int(intmax_t value, t_printf *tab)
{
	size_t	len;

	len = int_length(value);
	if (tab->arg.flag & PREC)
		tab->arg.prec = ((int)len < tab->arg.prec) ? tab->arg.prec - (int)len : 0;
	tab->arg.larg -= len;
	tab->arg.larg -= (tab->arg.prec > 0) ? tab->arg.prec : 0;
	if (tab->arg.flag & PLUS && value >= 0)
		tab->arg.larg--;
	if (tab->arg.flag & SPACE && value >= 0)
		tab->arg.larg--;
	if (value < 0)
		tab->arg.larg--;
	fill_integer(value, tab);
}

void	check_integer(va_list ap, t_printf *tab)
{
	if (tab->arg.flag & H)
		prepare_int((short int)va_arg(ap, intmax_t), tab);
	else if (tab->arg.flag & HH)
		prepare_int((char)va_arg(ap, intmax_t), tab);
	else if (tab->arg.flag & L)
		prepare_int((long int)va_arg(ap, intmax_t), tab);
	else if (tab->arg.flag & LL)
		prepare_int((long long int)va_arg(ap, intmax_t), tab);
	else
		prepare_int((int)va_arg(ap, intmax_t), tab);
}

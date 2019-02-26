/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 15:16:42 by stdenis           #+#    #+#             */
/*   Updated: 2019/02/26 16:28:19 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "ft_printf.h"

void	fill_integer(intmax_t value, t_printf *tab, char fill)
{
	bool	print;

	print = true;
	if (value == 0 && tab->arg.prec == 0 && tab->arg.flag & PREC)
	{
		print = false;
		tab->arg.larg++;
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

void	prepare_int(intmax_t value, t_printf *tab)
{
	int		len;

	len = int_length(value, 10);
	if (tab->arg.flag & PREC)
		tab->arg.prec = (len < tab->arg.prec) ? tab->arg.prec - len : 0;
	tab->arg.larg -= len;
	tab->arg.larg -= (tab->arg.prec > 0) ? tab->arg.prec : 0;
	if (tab->arg.flag & PLUS && value >= 0)
		tab->arg.larg--;
	if (tab->arg.flag & SPACE && value >= 0)
		tab->arg.larg--;
	if (value < 0)
		tab->arg.larg--;
	if (tab->arg.flag & ZERO)
	{
		if (value < 0)
			fill_buffer('-', tab);
		fill_integer(value, tab, '0');
	}
	else
		fill_integer(value, tab, ' ');
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

void	check_unsigned_integer(va_list ap, t_printf *tab)
{
	if (tab->arg.flag & H)
		prepare_int((unsigned short int)va_arg(ap, intmax_t), tab);
	else if (tab->arg.flag & HH)
		prepare_int((unsigned char)va_arg(ap, intmax_t), tab);
	else if (tab->arg.flag & L)
		prepare_int((unsigned long int)va_arg(ap, intmax_t), tab);
	else if (tab->arg.flag & LL)
		prepare_int((unsigned long long int)va_arg(ap, intmax_t), tab);
	else
		prepare_int((unsigned int)va_arg(ap, intmax_t), tab);
}

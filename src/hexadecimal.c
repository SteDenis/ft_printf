/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexadecimal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 11:44:55 by stdenis           #+#    #+#             */
/*   Updated: 2019/03/08 18:03:56 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	before_or_after(uintmax_t value, t_printf *tab, char fill)
{
	while (!(tab->arg.flag & (MINUS | ZERO)) && tab->arg.larg-- > 0)
		fill_buffer(fill, tab);
	if (tab->arg.flag & HASH && value != 0)
		fill_buffer('0', tab);
	if (tab->arg.type == X && tab->arg.flag & HASH && value != 0)
		fill_buffer('x', tab);
	else if (tab->arg.type == XX && tab->arg.flag & HASH && value != 0)
		fill_buffer('X', tab);
	while (check_flags(tab->arg.flag, 2, ZERO, MINUS) && tab->arg.larg-- > 0)
		fill_buffer(fill, tab);
}

static void	fill_hex(uintmax_t value, t_printf *tab, char fill)
{
	int		prec;

	prec = tab->arg.prec;
	before_or_after(value, tab, fill);
	while (tab->arg.prec-- > 0)
		fill_buffer('0', tab);
	if (value == 0)
	{
		if (((tab->arg.flag & PREC) && prec > 0) || !(tab->arg.flag & PREC))
			fill_buffer('0', tab);
	}
	else if (tab->arg.type == X)
		putnbr_c(value, tab, "0123456789abcdef", 16);
	else if (tab->arg.type == XX)
		putnbr_c(value, tab, "0123456789ABCDEF", 16);
	while ((tab->arg.flag & MINUS) && tab->arg.larg-- > 0)
		fill_buffer(fill, tab);
}

static void	prepare_hex(uintmax_t value, t_printf *tab)
{
	int		len;

	len = uint_length(value, 16);
	if (tab->arg.flag & PREC)
	{
		tab->arg.flag &= ~(ZERO);
		tab->arg.prec = (len < tab->arg.prec) ? tab->arg.prec - len : 0;
	}
	tab->arg.larg -= (value == 0) ? 0 : len;
	tab->arg.larg -= (tab->arg.prec > 0) ? tab->arg.prec : 0;
	if (tab->arg.flag & HASH && value != 0)
		tab->arg.larg -= 2;
	if (tab->arg.flag & ZERO && !(tab->arg.flag & MINUS))
		fill_hex(value, tab, '0');
	else
		fill_hex(value, tab, ' ');
}

void		check_hexadecimal(va_list ap, void *ptr)
{
	t_printf *tab;

	tab = (t_printf*)ptr;
	if (tab->arg.flag & H)
		prepare_hex((unsigned short int)va_arg(ap, uintmax_t), tab);
	else if (tab->arg.flag & HH)
		prepare_hex((unsigned char)va_arg(ap, uintmax_t), tab);
	else if (tab->arg.flag & L)
		prepare_hex((unsigned long int)va_arg(ap, uintmax_t), tab);
	else if (tab->arg.flag & LL)
		prepare_hex((unsigned long long int)va_arg(ap, uintmax_t), tab);
	else if (tab->arg.flag & J)
		prepare_hex(va_arg(ap, uintmax_t), tab);
	else if (tab->arg.flag & Z)
		prepare_hex((size_t)va_arg(ap, uintmax_t), tab);
	else
		prepare_hex((unsigned int)va_arg(ap, uintmax_t), tab);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 13:56:13 by stdenis           #+#    #+#             */
/*   Updated: 2019/03/09 14:00:18 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	before_or_after(uintmax_t value, t_printf *tab, char fill)
{
	while (!(tab->arg.flag & (MINUS | ZERO)) && tab->arg.larg-- > 0)
		fill_buffer(fill, tab);
	if (tab->arg.flag & HASH && value != 0)
		fill_buffer('0', tab);
	if (tab->arg.flag & HASH && value != 0)
		fill_buffer('b', tab);
	while (check_flags(tab->arg.flag, 2, ZERO, MINUS) && tab->arg.larg-- > 0)
		fill_buffer(fill, tab);
}

static void	fill_bin(uintmax_t value, t_printf *tab, char fill)
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
	else
		putnbr_c(value, tab, "01", 2);
	while ((tab->arg.flag & MINUS) && tab->arg.larg-- > 0)
		fill_buffer(fill, tab);
}

static void	prepare_bin(uintmax_t value, t_printf *tab)
{
	int		len;

	len = uint_length(value, 2);
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
		fill_bin(value, tab, '0');
	else
		fill_bin(value, tab, ' ');
}

void		check_binary(va_list ap, void *ptr)
{
	t_printf *tab;

	tab = (t_printf*)ptr;
	if (tab->arg.flag & H)
		prepare_bin((unsigned short int)va_arg(ap, uintmax_t), tab);
	else if (tab->arg.flag & HH)
		prepare_bin((unsigned char)va_arg(ap, uintmax_t), tab);
	else if (tab->arg.flag & L)
		prepare_bin((unsigned long int)va_arg(ap, uintmax_t), tab);
	else if (tab->arg.flag & LL)
		prepare_bin((unsigned long long int)va_arg(ap, uintmax_t), tab);
	else if (tab->arg.flag & J)
		prepare_bin(va_arg(ap, uintmax_t), tab);
	else if (tab->arg.flag & Z)
		prepare_bin((size_t)va_arg(ap, uintmax_t), tab);
	else
		prepare_bin((unsigned int)va_arg(ap, uintmax_t), tab);
}

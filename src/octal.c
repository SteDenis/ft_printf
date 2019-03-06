/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   octal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 13:17:40 by stdenis           #+#    #+#             */
/*   Updated: 2019/03/05 19:09:39 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	fill_oct(uintmax_t value, t_printf *tab, char fill)
{
	bool print;

	print = true;
	if (tab->arg.prec <= 0 && (tab->arg.flag & PREC))
		print = false;
	if (value == 0 && (tab->arg.flag & HASH) && tab->arg.prec == 1)
		print = false;
	if (!print && tab->arg.larg > 0 && value == 0)
		tab->arg.larg++;
	while (!(tab->arg.flag & MINUS) && tab->arg.larg-- > 0)
		fill_buffer(fill, tab);
	while (tab->arg.prec-- > 0)
		fill_buffer('0', tab);
	if (value != 0)
		ft_putnbr_buffer_conv(value, tab, "01234567");
	else if (print)
		fill_buffer('0', tab);
	while ((tab->arg.flag & MINUS) && tab->arg.larg-- > 0)
		fill_buffer(fill, tab);
}

static void	prepare_oct(uintmax_t value, t_printf *tab)
{
	int		len;

	len = int_length(value, 8);
	if (tab->arg.flag & PREC)
		tab->arg.prec = (len < tab->arg.prec) ? tab->arg.prec - len : 0;
	tab->arg.larg -= len;
	tab->arg.larg -= (tab->arg.prec > 0) ? tab->arg.prec : 0;
	if (tab->arg.flag & HASH)
	{
		if (tab->arg.prec <= 0)
		{
			tab->arg.prec = (tab->arg.prec <= 0) ? 1 : tab->arg.prec;
			tab->arg.larg--;
		}
	}
	if (tab->arg.flag & ZERO && !(tab->arg.flag & PREC) && !(tab->arg.flag & MINUS))
		fill_oct(value, tab, '0');
	else
		fill_oct(value, tab, ' ');
}

void	check_octal(va_list ap, t_printf *tab)
{
	if (tab->arg.flag & H)
		prepare_oct((unsigned short int)va_arg(ap, uintmax_t), tab);
	else if (tab->arg.flag & HH)
		prepare_oct((unsigned char)va_arg(ap, uintmax_t), tab);
	else if (tab->arg.flag & L)
		prepare_oct((unsigned long int)va_arg(ap, uintmax_t), tab);
	else if (tab->arg.flag & LL)
		prepare_oct((unsigned long long int)va_arg(ap, uintmax_t), tab);
	else
		prepare_oct((unsigned int)va_arg(ap, uintmax_t), tab);
}

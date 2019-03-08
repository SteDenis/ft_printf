/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 15:16:42 by stdenis           #+#    #+#             */
/*   Updated: 2019/03/08 18:40:25 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "ft_printf.h"

static void	fill_integer_zero(intmax_t value, t_printf *tab, char fill)
{
	if (tab->arg.flag & SPACE && value >= 0)
		fill_buffer(' ', tab);
	if (value < 0)
		fill_buffer('-', tab);
	if (tab->arg.flag & PLUS && value >= 0)
		fill_buffer('+', tab);
	while (!(tab->arg.flag & MINUS) && tab->arg.larg-- > 0)
		fill_buffer(fill, tab);
	while (tab->arg.prec-- > 0)
		fill_buffer('0', tab);
	if (value < 0)
		putnbr_n(value, tab);
	else
		putnbr_p(value, tab);
	while ((tab->arg.flag & MINUS) && tab->arg.larg-- > 0)
		fill_buffer(fill, tab);
}

static void	fill_integer(intmax_t value, t_printf *tab, char fill)
{
	bool	print;

	print = true;
	if (value == 0 && tab->arg.prec == 0 && tab->arg.flag & PREC)
	{
		print = false;
		tab->arg.larg++;
	}
	while (!(tab->arg.flag & MINUS) && tab->arg.larg-- > 0)
		fill_buffer(fill, tab);
	if (value >= 0 && tab->arg.flag & SPACE)
		fill_buffer(' ', tab);
	if (value >= 0 && tab->arg.flag & PLUS)
		fill_buffer('+', tab);
	else if (value < 0)
		fill_buffer('-', tab);
	while (tab->arg.prec-- > 0)
		fill_buffer('0', tab);
	if (print && value < 0)
		putnbr_n(value, tab);
	else if (print)
		putnbr_p(value, tab);
	while ((tab->arg.flag & MINUS) && tab->arg.larg-- > 0)
		fill_buffer(fill, tab);
}

static void	prepare_int(intmax_t value, t_printf *tab)
{
	int		len;

	len = int_length(value, 10);
	if (tab->arg.flag & PREC)
	{
		tab->arg.flag &= ~(ZERO);
		tab->arg.prec = (len < tab->arg.prec) ? tab->arg.prec - len : 0;
	}
	tab->arg.larg -= len;
	tab->arg.larg -= (tab->arg.prec > 0) ? tab->arg.prec : 0;
	if (tab->arg.flag & PLUS && value >= 0)
	{
		tab->arg.larg--;
		tab->arg.flag &= ~(SPACE);
	}
	if (tab->arg.flag & SPACE && value >= 0)
		tab->arg.larg--;
	if (value < 0)
		tab->arg.larg--;
	if (tab->arg.flag & ZERO && !(tab->arg.flag & MINUS))
		fill_integer_zero(value, tab, '0');
	else
		fill_integer(value, tab, ' ');
}

void		check_integer(va_list ap, void *ptr)
{
	t_printf *tab;

	tab = (t_printf*)ptr;
	if (tab->arg.flag & H && !(tab->arg.flag & Z) && !(tab->arg.flag & J))
		prepare_int((short int)va_arg(ap, intmax_t), tab);
	else if (tab->arg.flag & HH)
		prepare_int((char)va_arg(ap, intmax_t), tab);
	else if (tab->arg.flag & J)
		prepare_int(va_arg(ap, intmax_t), tab);
	else if (tab->arg.flag & Z)
		prepare_int((long int)va_arg(ap, intmax_t), tab);
	else if (tab->arg.flag & L)
		prepare_int((long int)va_arg(ap, intmax_t), tab);
	else if (tab->arg.flag & LL)
		prepare_int((long long int)va_arg(ap, intmax_t), tab);
	else
		prepare_int((int)va_arg(ap, intmax_t), tab);
}

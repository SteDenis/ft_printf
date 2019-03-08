/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 12:45:26 by stdenis           #+#    #+#             */
/*   Updated: 2019/03/08 18:15:33 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "double.h"
#include <stdio.h>

static int	check_integrity(t_dbl *tab_dbl)
{
	t_binary	uni;
	int			exp;
	int			mant;

	uni.val = tab_dbl->ldbl;
	tab_dbl->sign = uni.t_bits.exposign >> 15;
	exp = uni.t_bits.exposign & 0x7fff;
	mant = uni.t_bits.mantissa >> 63;
	if (!exp && !mant)
		return (uni.t_bits.mantissa ? 0 : 1);
	if (!mant)
		return (2);
	if (exp == 0x7fff)
		return (uni.t_bits.mantissa << 1 ? 3 : 4);
	return (5);
}

static void	printing_ldbl(t_dbl *tab_dbl, t_printf *tab)
{
	size_t	len;

	while (tab_dbl->digits <= tab_dbl->before_dot)
	{
		len = int_length(*tab_dbl->digits, 10);
		while (tab_dbl->digits != tab_dbl->head && len++ < 9)
			fill_buffer('0', tab);
		putnbr_p(*tab_dbl->digits, tab);
		tab_dbl->digits++;
	}
	if (tab->arg.prec > 0 || (tab->arg.flag & HASH))
		fill_buffer('.', tab);
	while (tab_dbl->digits < tab_dbl->last && tab->arg.prec > 0)
	{
		len = int_length(*tab_dbl->digits, 10);
		while (len++ < 9 && tab->arg.prec-- > 0)
			fill_buffer('0', tab);
		tab->arg.prec -= int_length(*tab_dbl->digits, 10);
		while (tab->arg.prec < 0 && tab->arg.prec++)
			*tab_dbl->digits = (*tab_dbl->digits / 10);
		if (*tab_dbl->digits > 0)
			putnbr_p(*tab_dbl->digits, tab);
		tab_dbl->digits++;
	}
}

void		print_flags_ldbl(t_dbl *tab_dbl, t_printf *tab, char fill)
{
	if (check_flags(tab->arg.flag, 1, PLUS, ZERO) && tab_dbl->sign == 0)
		fill_buffer('+', tab);
	if (check_flags(tab->arg.flag, 1, SPACE, ZERO) && tab_dbl->sign == 0)
		fill_buffer(' ', tab);
	if ((tab->arg.flag & ZERO) && tab_dbl->sign == 1)
		fill_buffer('-', tab);
	while (!(tab->arg.flag & MINUS) && tab->arg.larg-- > 0)
		fill_buffer(fill, tab);
	if (check_flags(tab->arg.flag, 2, SPACE, ZERO) && tab_dbl->sign == 0)
		fill_buffer(' ', tab);
	if (check_flags(tab->arg.flag, 2, PLUS, ZERO) && tab_dbl->sign == 0)
		fill_buffer('+', tab);
	if (tab_dbl->sign == 1 && !(tab->arg.flag & ZERO))
		fill_buffer('-', tab);
	printing_ldbl(tab_dbl, tab);
	while (tab->arg.prec-- > 0)
		fill_buffer('0', tab);
	while ((tab->arg.flag & MINUS) && tab->arg.larg-- > 0)
		fill_buffer(fill, tab);
}

void		print_zero(t_printf *tab, char fill, t_dbl *tab_dbl)
{
	if (check_flags(tab->arg.flag, 1, PLUS, ZERO) && tab_dbl->sign == 0)
		fill_buffer('+', tab);
	if (check_flags(tab->arg.flag, 1, SPACE, ZERO) && tab_dbl->sign == 0)
		fill_buffer(' ', tab);
	if ((tab->arg.flag & ZERO) && tab_dbl->sign == 1)
		fill_buffer('-', tab);
	while (!(tab->arg.flag & MINUS) && tab->arg.larg-- > 0)
		fill_buffer(fill, tab);
	if (check_flags(tab->arg.flag, 2, SPACE, ZERO) && tab_dbl->sign == 0)
		fill_buffer(' ', tab);
	if (check_flags(tab->arg.flag, 2, PLUS, ZERO) && tab_dbl->sign == 0)
		fill_buffer('+', tab);
	if (tab_dbl->sign == 1 && !(tab->arg.flag & ZERO))
		fill_buffer('-', tab);
	fill_buffer('0', tab);
	if (tab->arg.prec > 0 || (tab->arg.flag & HASH))
		fill_buffer('.', tab);
	while (tab->arg.prec-- > 0)
		fill_buffer('0', tab);
	while ((tab->arg.flag & MINUS) && tab->arg.larg-- > 0)
		fill_buffer(fill, tab);
}

void		check_float(va_list ap, void *ptr)
{
	t_dbl			tab_dbl;
	t_printf		*tab;
	int				check;
	int				prec;

	tab = (t_printf*)ptr;
	if (!(tab->arg.flag & PREC))
		tab->arg.prec = 6;
	prec = tab->arg.prec;
	if (!(tab->arg.flag & LDBL))
	{
		tab_dbl.dbl = va_arg(ap, double);
		tab_dbl.ldbl = (long double)tab_dbl.dbl;
	}
	else
		tab_dbl.ldbl = va_arg(ap, long double);
	check = check_integrity(&tab_dbl);
	if (check == 5)
	{
		transform_ldbl_80b(&tab_dbl, tab);
		if (prec == 0)
			rounding_prec_zero(&tab_dbl, tab);
	}
	else
		print_others(&tab_dbl, check, tab);
}

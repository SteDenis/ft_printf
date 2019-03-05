/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 12:45:26 by stdenis           #+#    #+#             */
/*   Updated: 2019/03/05 15:56:46 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "double.h"

static void	print_zero(t_printf *tab, char fill)
{
	int		minus;

	minus = (tab->arg.prec > 0 || (tab->arg.flag & HASH)) ? 1 : 0;
	minus += (tab->arg.flag & SPACE) ? 1 : 0;
	tab->arg.larg -= 1 + tab->arg.prec + minus;
	while (!(tab->arg.flag & MINUS) && tab->arg.larg-- > 0)
		fill_buffer(fill, tab);
	if (tab->arg.flag & SPACE)
		fill_buffer(' ', tab);
	if (tab->arg.flag & PLUS)
		fill_buffer('+', tab);
	fill_buffer('0', tab);
	if (tab->arg.prec > 0 || (tab->arg.flag & HASH))
		fill_buffer('.', tab);
	while (tab->arg.prec-- > 0)
		fill_buffer('0', tab);
	while ((tab->arg.flag & MINUS) && tab->arg.larg-- > 0)
		fill_buffer(fill, tab);
}

static void	printing_ldbl(t_dbl *tab_dbl, t_printf *tab)
{
	size_t	len;

	while (tab_dbl->digits <= tab_dbl->before_dot)
	{
		len = int_length(*tab_dbl->digits, 10);
		while (tab_dbl->digits != tab_dbl->head && len++ < 9)
			fill_buffer('0', tab);
		ft_putnbr_buffer_pos(*tab_dbl->digits, tab);
		tab_dbl->digits++;
	}
	if (tab->arg.prec > 0 || (tab->arg.flag & HASH))
		fill_buffer('.', tab);
	while (tab_dbl->digits < tab_dbl->last && tab->arg.prec > 0)
	{
		len = int_length(*tab_dbl->digits, 10);
		tab->arg.prec -= len;
		while (len++ < 9 && tab->arg.prec--)
			fill_buffer('0', tab);
		while (tab->arg.prec < 0 && tab->arg.prec++)
			*tab_dbl->digits = (*tab_dbl->digits / 10);
		ft_putnbr_buffer_pos(*tab_dbl->digits, tab);
		tab_dbl->digits++;
	}
	while (tab->arg.prec-- > 0)
		fill_buffer('0', tab);
}

void		printing_flags_ldbl(t_dbl *tab_dbl, t_printf *tab, char fill)
{
	size_t	len;

	len = 0;
	while (!(tab->arg.flag & MINUS) && tab->arg.larg-- > 0)
		fill_buffer(fill, tab);
	if (tab->arg.flag & SPACE)
		fill_buffer(' ', tab);
	if (tab->arg.flag & PLUS)
		fill_buffer('+', tab);
	printing_ldbl(tab_dbl, tab);
	while ((tab->arg.flag & MINUS) && tab->arg.larg-- > 0)
		fill_buffer(fill, tab);
}

int			check_float(va_list ap, t_printf *tab)
{
	t_dbl	tab_dbl;
	int		check;

	check = 0;
	if (!(tab->arg.flag & PREC))
		tab->arg.prec = 6;
	if (!(tab->arg.flag & LDBL))
	{
		tab_dbl.dbl = va_arg(ap, double);
		check = (int)&tab_dbl.dbl;
		if ((check & 0x10))
		{
			if (tab->arg.flag & ZERO)
				print_zero(tab, '0');
			else
				print_zero(tab, ' ');
			return (1);
		}
		tab_dbl.ldbl = (long double)tab_dbl.dbl;
	}
	else
		tab_dbl.ldbl = va_arg(ap, long double);
	transform_ldbl_80b(&tab_dbl, tab);
	return (0);
}

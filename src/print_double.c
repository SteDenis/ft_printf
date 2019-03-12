/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 15:57:05 by stdenis           #+#    #+#             */
/*   Updated: 2019/03/11 16:10:14 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "double.h"

static void	print_decimal(t_dbl *tab_dbl, t_printf *tab)
{
	int		len;
	int		i;

	while (tab_dbl->digits < tab_dbl->last && tab->arg.prec > 0)
	{
		i = 0;
		len = (int)int_length(*tab_dbl->digits, 10);
		while (len + i < 9 && (tab->arg.prec - i++) > 0)
			fill_buffer('0', tab);
		tab->arg.prec -= i;
		while (len > tab->arg.prec && len--)
			*tab_dbl->digits = (*tab_dbl->digits / 10);
		if (tab->arg.prec > 0)
			putnbr_p(*tab_dbl->digits, tab);
		tab->arg.prec -= len;
		tab_dbl->digits++;
	}
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
	print_decimal(tab_dbl, tab);
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

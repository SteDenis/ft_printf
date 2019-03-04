/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 12:45:26 by stdenis           #+#    #+#             */
/*   Updated: 2019/03/04 20:43:10 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "double.h"

/*static void	print_zero(t_printf *tab, char fill)
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
	while (tab->arg.prec--)
		fill_buffer('0', tab);
	while ((tab->arg.flag & MINUS) && tab->arg.larg-- > 0)
		fill_buffer(fill, tab);
}*/

#include <stdio.h>
void		rounding_ldbl(t_dbl *tab_dbl, t_printf *tab)
{
	unsigned int	i;

	i = 10;
	if (tab_dbl->head < tab_dbl->last)
	{
		tab_dbl->entier = 9 * (tab_dbl->before_dot - tab_dbl->head);
		while (*tab_dbl->head >= i)
		{
			tab_dbl->entier++;
			i *= 10;
		}
	}
	else
		tab_dbl->entier = 0;
	printf("Entier = %d\n", tab_dbl->entier);
	while (tab_dbl->last > tab_dbl->head && !tab_dbl->last[-1])
		tab_dbl->last--;
	tab_dbl->digits = tab_dbl->head;
	if (tab_dbl->head > tab_dbl->before_dot)
		tab_dbl->head = tab_dbl->before_dot;
	while (tab_dbl->digits <= tab_dbl->before_dot)
	{
		if (tab_dbl->digits != tab_dbl->head && int_length(*tab_dbl->digits, 10) < 9)
			printf("0");
		printf("%u", *tab_dbl->digits);
		tab_dbl->digits++;
	}
	printf("\n");
	(void)tab;
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
		/*if (!(check & 0x10))
		{
			if (tab->arg.flag & ZERO)
				print_zero(tab, '0');
			else
				print_zero(tab, ' ');
			return (1);
		}*/
		tab_dbl.ldbl = (long double)tab_dbl.dbl;
	}
	else
		tab_dbl.ldbl = va_arg(ap, long double);
	transform_ldbl_80b(&tab_dbl, tab);
	return (0);
}

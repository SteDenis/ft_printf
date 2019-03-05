/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 09:22:38 by stdenis           #+#    #+#             */
/*   Updated: 2019/03/05 16:07:10 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "double.h"

static void	calculate_nbr_entier(t_dbl *tab_dbl)
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
}

void		rounding_ldbl(t_dbl *tab_dbl, t_printf *tab)
{
	int		minus;
	int	prec;
	int j, i;
	uint32_t x;

	calculate_nbr_entier(tab_dbl);
	prec = (tab->arg.prec > 10000) ? 10000 : tab->arg.prec;
	tab_dbl->digits = tab_dbl->before_dot + 1 + (prec / 9);
	j = tab->arg.prec;
	j %= 9;
	for (i=10, j++; j<9; i*=10, j++);
	x = *tab_dbl->digits % i;
	if (x && tab_dbl->digits + 1 != tab_dbl->last)
	{
		*tab_dbl->digits -= x;
		*tab_dbl->digits  = *tab_dbl->digits + i;
		while (*tab_dbl->digits > 999999999)
		{
			*tab_dbl->digits-- = 0;
			if (tab_dbl->digits < tab_dbl->head) *--tab_dbl->head = 0;
				(*tab_dbl->digits)++;
		}
		calculate_nbr_entier(tab_dbl);
	}
	if (tab_dbl->last>tab_dbl->digits+1)
		tab_dbl->last=tab_dbl->digits+1;
	while (tab_dbl->last > tab_dbl->head && !tab_dbl->last[-1])
		tab_dbl->last--;
	tab_dbl->digits = tab_dbl->head;
	if (tab_dbl->head > tab_dbl->before_dot)
		tab_dbl->head = tab_dbl->before_dot;
	minus = (tab->arg.prec > 0 || (tab->arg.flag & HASH)) ? 1 : 0;
	minus += (tab->arg.flag & SPACE) ? 1 : 0;
	tab->arg.larg -= 1 + tab_dbl->entier + tab->arg.prec + minus;
	if (tab->arg.flag & ZERO)
		printing_flags_ldbl(tab_dbl, tab, '0');
	else
		printing_flags_ldbl(tab_dbl, tab, ' ');
}

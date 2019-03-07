/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 09:22:38 by stdenis           #+#    #+#             */
/*   Updated: 2019/03/07 09:27:56 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "double.h"

static void	prepare_print(t_dbl *tab_dbl, t_printf *tab)
{
	int			minus = 0;

	if (tab_dbl->last > tab_dbl->digits + 1)
		tab_dbl->last = tab_dbl->digits + 1;
	while (tab_dbl->last > tab_dbl->head && !tab_dbl->last[-1])
		tab_dbl->last--;
	tab_dbl->digits = tab_dbl->head;
	if (tab_dbl->head > tab_dbl->before_dot)
		tab_dbl->head = tab_dbl->before_dot;
	minus = (tab->arg.prec > 0) ? 1 : 0;
	minus += (tab->arg.flag & SPACE && tab_dbl->sign == 0) ? 1 : 0;
	minus += (tab->arg.flag & PLUS && tab_dbl->sign == 0) ? 1 : 0;
	minus += (tab_dbl->sign == 1) ? 1 : 0;
	minus += (tab->arg.prec == 0 && tab->arg.flag & HASH) ? 1 : 0;
	tab->arg.larg -= 1 + tab_dbl->integer + tab->arg.prec + minus;
	tab_dbl->digits = tab_dbl->head;
	if (tab->arg.flag & ZERO)
		printing_flags_ldbl(tab_dbl, tab, '0');
	else
		printing_flags_ldbl(tab_dbl, tab, ' ');
}

void	calculate_nbr_integer(t_dbl *tab_dbl)
{
	unsigned int	i;

	i = 10;
	if (tab_dbl->head < tab_dbl->last)
	{
		tab_dbl->integer = 9 * (tab_dbl->before_dot - tab_dbl->head);
		while (*tab_dbl->head >= i)
		{
			tab_dbl->integer++;
			i *= 10;
		}
	}
	else
		tab_dbl->integer = 0;
}

void		check_inf_or_nan(t_uniondbl *uni, t_dbl *tab_dbl, t_printf *tab)
{
	if (uni->t_binary.mantissa1 == 0x80000000 && uni->t_binary.mantissa2 == 0x0)
	{
		if (tab_dbl->sign == 1)
			check_string("-inf", tab);
		else
			check_string("inf", tab);
	}
	else
		check_string("nan", tab);
}

void		re_positioning_pointers(t_dbl *tab_dbl, uint32_t last, int decal)
{
	uint32_t	*ptr;

	if (!*tab_dbl->head)
		tab_dbl->head++;
	if (last)
		*tab_dbl->last++ = last;
	ptr = tab_dbl->before_dot;
	if (tab_dbl->last - ptr > decal)
		tab_dbl->last = ptr + decal;
}

void		rounding_ldbl(t_dbl *tab_dbl, t_printf *tab)
{
	int			prec;
	int			j;
	int			i;

	prec = (tab->arg.prec > 10000) ? 10000 : tab->arg.prec;
	tab_dbl->digits = tab_dbl->before_dot + 1 + (prec / 9);
	j = ((tab->arg.prec) % 9) + 1;
	i = 10;
	while (j++ < 9)
		i *= 10;
	tab_dbl->rounding = *tab_dbl->digits % i;
	if (tab_dbl->rounding && tab_dbl->digits + 1 != tab_dbl->last)
	{
		if (tab_dbl->rounding / (i / 10) >= 5)
			*tab_dbl->digits = (*tab_dbl->digits - tab_dbl->rounding) + i;
		while (*tab_dbl->digits > 999999999)
		{
			*tab_dbl->digits-- = 0;
			if (tab_dbl->digits < tab_dbl->head)
				*--tab_dbl->head = 0;
			(*tab_dbl->digits)++;
		}
		calculate_nbr_integer(tab_dbl);
	}
	prepare_print(tab_dbl, tab);
}

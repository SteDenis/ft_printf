/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_ldbl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 14:55:36 by stdenis           #+#    #+#             */
/*   Updated: 2019/03/04 20:21:56 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "double.h"
#include <stdio.h>
static long double ft_frexpl(long double value, int *exp)
{
	union
	{
		long double val;
		struct 			s_binary
		{
			unsigned mantissa2 : 32;
			unsigned mantissa1 : 32;
			unsigned exponent : 15;
			unsigned sign :  1;
			unsigned empty : 16;
		}				t_binary;
	}					u_uniondbl;

	if (!value)
		return ((long double) 0);
	u_uniondbl.val = value;
	*exp = u_uniondbl.t_binary.exponent - 16383;
	u_uniondbl.t_binary.exponent = 16383;
	return (u_uniondbl.val);
}

static void	redirect_pointers_tab(t_dbl *tab_dbl, int exponent)
{
	if (exponent < 0)
	{
		tab_dbl->last = tab_dbl->numbers;
		tab_dbl->head = tab_dbl->numbers;
		tab_dbl->before_dot = tab_dbl->numbers;
	}
	else
	{
		tab_dbl->last = tab_dbl->numbers + 1000;
		tab_dbl->head = tab_dbl->numbers + 1000;
		tab_dbl->before_dot = tab_dbl->numbers + 1000;
	}
}

static void	handler_ldbl_pos(t_dbl *tab_dbl, t_printf *tab, int exponent)
{
	uint32_t	carry;
	uint64_t	value;
	int			power;

	while (exponent > 0)
	{
		carry = 0;
		power = (exponent < 29) ? exponent : 29;
		tab_dbl->digits = tab_dbl->last - 1;
		while (tab_dbl->digits >= tab_dbl->head)
		{
			value = ((uint64_t)*tab_dbl->digits << power) + carry;
			*tab_dbl->digits = value % 1000000000;
			carry = value / 1000000000;
			tab_dbl->digits--;
		}
		if (carry)
			*--tab_dbl->head = carry;
		while (tab_dbl->last > tab_dbl->head && !tab_dbl->last[-1])
			tab_dbl->last--;
		exponent -= power;
	}
	rounding_ldbl(tab_dbl, tab);
}

static void	handler_ldbl_neg(t_dbl *tab_dbl, t_printf *tab, int exponent)
{
	uint32_t	last;
	uint64_t	value;
	int			power;

	while (exponent < 0)
	{
		last = 0;
		power = (-exponent < 9) ? -exponent : 9;
		tab_dbl->digits = tab_dbl->head;
		while (tab_dbl->digits < tab_dbl->last)
		{
			value = *tab_dbl->digits & (1 << power) - 1;
			*tab_dbl->digits = (*tab_dbl->digits >> power) + last;
			last = (1000000000 >> power) * value;
			tab_dbl->digits++;
		}
		if (!*tab_dbl->head)
			tab_dbl->head++;
		exponent += power;
	}
	rounding_ldbl(tab_dbl, tab);
}

/*
** Transform the long double in a normalized number with ft_frexpl.
** If ldbl != 0, multiplicate by 0x1p28 (2^28 = 268435456) for better precision.
** Reduce exponent in the same way - (28 + 1) 1 for last bit to 0.
*/
void		transform_ldbl_80b(t_dbl *tab_dbl, t_printf *tab)
{
	int		exponent;

	if (tab_dbl->ldbl < 0)
		tab_dbl->ldbl = -tab_dbl->ldbl;
	tab_dbl->ldbl = ft_frexpl(tab_dbl->ldbl, &exponent) * 2;
	if (tab_dbl->ldbl)
	{
		tab_dbl->ldbl *= 0x1p28;
		exponent -= 29;
	}
	printf("EXP = %d\n", exponent);
	redirect_pointers_tab(tab_dbl, exponent);
	*tab_dbl->last = tab_dbl->ldbl;
	tab_dbl->ldbl = 1000000000 * (tab_dbl->ldbl - *tab_dbl->last++);
	while (tab_dbl->ldbl)
	{
		*tab_dbl->last = tab_dbl->ldbl;
		tab_dbl->ldbl = 1000000000 * (tab_dbl->ldbl - *tab_dbl->last++);
	}
	if (exponent > 0)
		handler_ldbl_pos(tab_dbl, tab, exponent);
	else
		handler_ldbl_neg(tab_dbl, tab, exponent);
	(void)tab;
}

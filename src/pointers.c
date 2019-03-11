/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 14:11:34 by stdenis           #+#    #+#             */
/*   Updated: 2019/03/09 15:22:07 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	fill_pointers(void *value, t_printf *tab, char fill)
{
	bool		prec;

	prec = (tab->arg.prec > 0 || !(tab->arg.flag & PREC)) ? true : false;
	while (!(tab->arg.flag & MINUS) && tab->arg.larg-- > 0)
		fill_buffer(fill, tab);
	if (!(tab->arg.flag & ZERO))
	{
		fill_buffer('0', tab);
		fill_buffer('x', tab);
	}
	while (tab->arg.prec-- > 0)
		fill_buffer('0', tab);
	if (value == NULL && prec)
		fill_buffer('0', tab);
	else
		putnbr_c((uintmax_t)value, tab, "0123456789abcdef", 16);
	while ((tab->arg.flag & MINUS) && tab->arg.larg-- > 0)
		fill_buffer(fill, tab);
}

static void	check_pointers(void *value, t_printf *tab)
{
	int		len;
	char	fill;

	fill = ' ';
	if ((tab->arg.flag & ZERO))
		fill = '0';
	len = uint_length((uintmax_t)value, 16);
	if (tab->arg.flag & PREC)
		tab->arg.prec = (len < tab->arg.prec) ? tab->arg.prec - len : 0;
	tab->arg.larg -= len + 2;
	tab->arg.larg -= (tab->arg.prec > 0) ? tab->arg.prec : 0;
	if ((tab->arg.flag & ZERO))
	{
		fill = '0';
		fill_buffer('0', tab);
		fill_buffer('x', tab);
	}
	fill_pointers(value, tab, fill);
}

void		get_pointers(va_list ap, void *ptr)
{
	t_printf *tab;

	tab = (t_printf*)ptr;
	check_pointers(va_arg(ap, void *), tab);
}

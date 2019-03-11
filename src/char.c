/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 15:01:04 by stdenis           #+#    #+#             */
/*   Updated: 2019/03/08 17:52:26 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	fill_with_char(const unsigned char value, t_printf *tab, char fill)
{
	while (!(tab->arg.flag & MINUS) && tab->arg.larg-- > 0)
		fill_buffer(fill, tab);
	fill_buffer(value, tab);
	while ((tab->arg.flag & MINUS) && tab->arg.larg-- > 0)
		fill_buffer(fill, tab);
}

static void	check_char(const unsigned char value, t_printf *tab)
{
	size_t		len;

	len = 1;
	if (tab->arg.flag & PREC)
		len = ((int)len < tab->arg.prec) ? 1 : tab->arg.prec;
	tab->arg.larg -= (tab->arg.larg > 0) ? len : 0;
	if (tab->arg.flag & ZERO && !(tab->arg.flag & MINUS))
		fill_with_char(value, tab, '0');
	else
		fill_with_char(value, tab, ' ');
}

void		get_char(va_list ap, void *ptr)
{
	t_printf	*tab;
	int			character;

	tab = (t_printf*)ptr;
	character = va_arg(ap, int);
	if (character >= 0 && character <= 200)
		check_char((unsigned char)character, tab);
}

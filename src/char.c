/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 15:01:04 by stdenis           #+#    #+#             */
/*   Updated: 2019/03/07 09:43:20 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	fill_with_char(const char value, t_printf *tab)
{
	size_t		i;

	i = -1;
	while (!(tab->arg.flag & MINUS) && tab->arg.larg-- > 0)
		fill_buffer(' ', tab);
	fill_buffer(value, tab);
	while ((tab->arg.flag & MINUS) && tab->arg.larg-- > 0)
		fill_buffer(' ', tab);
}

static void	check_char(const char value, t_printf *tab)
{
	size_t		len;

	len = 1;
	if (tab->arg.flag & PREC)
		len = ((int)len < tab->arg.prec) ? 1 : tab->arg.prec;
	tab->arg.larg -= (tab->arg.larg > 0) ? len : 0;
	fill_with_char(value, tab);
}

void	get_char(va_list ap, void *ptr)
{
	t_printf *tab;

	tab = (t_printf*)ptr;
	check_char((char)va_arg(ap, int), tab);
}

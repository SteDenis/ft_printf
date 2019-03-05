/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 14:11:34 by stdenis           #+#    #+#             */
/*   Updated: 2019/02/26 15:40:47 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	fill_pointers(void *value, t_printf *tab)
{
	while (!(tab->arg.flag & MINUS) && tab->arg.larg-- > 0)
		fill_buffer(' ', tab);
	fill_buffer('0', tab);
	fill_buffer('x', tab);
	while (tab->arg.prec-- > 0)
		fill_buffer('0', tab);
	if (value == NULL)
		fill_buffer('0', tab);
	else
		ft_putnbr_buffer_conv((uintmax_t)value, tab, "0123456789abcdef");
	while ((tab->arg.flag & MINUS) && tab->arg.larg-- > 0)
		fill_buffer(' ', tab);
}

void	check_pointers(void *value, t_printf *tab)
{
	int		len;

	len = int_length((intmax_t)value, 16);
	if (tab->arg.flag & PREC)
		tab->arg.prec = (len < tab->arg.prec) ? tab->arg.prec - len : 0;
	tab->arg.larg -= len + 2;
	tab->arg.larg -= (tab->arg.prec > 0) ? tab->arg.prec : 0;
	fill_pointers(value, tab);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 19:00:26 by stdenis           #+#    #+#             */
/*   Updated: 2019/03/05 19:03:01 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 15:16:42 by stdenis           #+#    #+#             */
/*   Updated: 2019/02/26 16:28:19 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "ft_printf.h"

static void	fill_unsigned(uintmax_t value, t_printf *tab, char fill)
{
	bool	print;

	print = true;
	if (value == 0 && tab->arg.prec == 0 && tab->arg.flag & PREC)
	{
		print = false;
		tab->arg.larg++;
	}
	while (!(tab->arg.flag & MINUS) && tab->arg.larg-- > 0)
		fill_buffer(fill, tab);
	while (tab->arg.prec-- > 0)
		fill_buffer('0', tab);
	if (print)
		ft_putnbr_buffer_pos(value, tab);
	while ((tab->arg.flag & MINUS) && tab->arg.larg-- > 0)
		fill_buffer(fill, tab);
}

static void	prepare_un(uintmax_t value, t_printf *tab)
{
	int		len;

	len = int_length(value, 10);
	if (tab->arg.flag & PREC)
	{
		tab->arg.flag &= ~(ZERO);
		tab->arg.prec = (len < tab->arg.prec) ? tab->arg.prec - len : 0;
	}
	tab->arg.larg -= len;
	tab->arg.larg -= (tab->arg.prec > 0) ? tab->arg.prec : 0;
	if (tab->arg.flag & ZERO)
		fill_unsigned(value, tab, '0');
	else
		fill_unsigned(value, tab, ' ');
}

void		check_unsigned_integer(va_list ap, t_printf *tab)
{
	if (tab->arg.flag & H)
		prepare_un((unsigned short int)va_arg(ap, uintmax_t), tab);
	else if (tab->arg.flag & HH)
		prepare_un((unsigned char)va_arg(ap, uintmax_t), tab);
	else if (tab->arg.flag & L)
		prepare_un((unsigned long int)va_arg(ap, uintmax_t), tab);
	else if (tab->arg.flag & LL)
		prepare_un((unsigned long long int)va_arg(ap, uintmax_t), tab);
	else
		prepare_un((unsigned int)va_arg(ap, uintmax_t), tab);
}

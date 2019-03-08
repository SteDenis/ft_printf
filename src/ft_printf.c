/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 13:32:02 by stdenis           #+#    #+#             */
/*   Updated: 2019/03/08 19:15:09 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	set_struct(t_printf *tab)
{
	tab->fmt = 0;
	tab->buff = 0;
	tab->rtn = 0;
	tab->dispatcher[0] = get_char;
	tab->dispatcher[1] = get_string;
	tab->dispatcher[2] = get_pointers;
	tab->dispatcher[3] = check_integer;
	tab->dispatcher[4] = check_octal;
	tab->dispatcher[5] = check_unsigned_integer;
	tab->dispatcher[6] = check_hexadecimal;
	tab->dispatcher[7] = check_hexadecimal;
	tab->dispatcher[8] = check_float;
	tab->dispatcher[9] = get_string_uni;
	tab->dispatcher[10] = get_char_uni;
	tab->arg.type = 0;
	tab->arg.larg = 0;
	tab->arg.prec = 0;
	tab->arg.flag = 0;
}

void	reset_arg(t_printf *tab)
{
	tab->arg.type ^= tab->arg.type;
	tab->arg.larg ^= tab->arg.larg;
	tab->arg.prec ^= tab->arg.prec;
	tab->arg.flag ^= tab->arg.flag;
}

int		ft_printf(const char *format, ...)
{
	va_list		ap;
	t_printf	tab;

	if (format == NULL)
		return (1);
	va_start(ap, format);
	set_struct(&tab);
	while (check_arg(format, &tab))
	{
		if (tab.arg.type == PERCENT)
			check_string("%", &tab);
		else if (tab.arg.type != 999)
			tab.dispatcher[tab.arg.type](ap, &tab);
		reset_arg(&tab);
	}
	if (tab.buff > 0)
		write(1, tab.buffer, tab.buff);
	va_end(ap);
	return (tab.rtn);
}

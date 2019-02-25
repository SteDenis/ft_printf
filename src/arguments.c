/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 13:34:41 by stdenis           #+#    #+#             */
/*   Updated: 2019/02/25 17:17:47 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int 	arg_printf(t_printf *tab, char c)
{
	if (c == 's')
		tab->arg.type = S;
	else if (c == 'd' || c == 'i')
		tab->arg.type = DI;
	else if (c == 'x')
		tab->arg.type = X;
	else if (c == 'X')
		tab->arg.type = XX;
	else if (c == 'o')
		tab->arg.type = O;
	else if (c == 'u')
		tab->arg.type = U;
	else if (c == 'p')
		tab->arg.type = P;
	else if (c == 'c')
		tab->arg.type = C;
	else if (c == 'f')
		tab->arg.type = F;
	else if (c == '%')
		tab->arg.type = PERCENT;
	else
		return (0);
	return (1);
}

int 	arg_flags(t_printf *tab, const char *format)
{
	if (format[tab->fmt] == '-')
		tab->arg.flag = (tab->arg.flag | MINUS) & ~(ZERO);
	else if (format[tab->fmt] == '+')
	tab->arg.flag = (tab->arg.flag | PLUS) & ~(SPACE);
	else if (format[tab->fmt] == '#')
	tab->arg.flag = (tab->arg.flag | HASH);
	else if (format[tab->fmt] == '0' && !(tab->arg.flag & PREC) && !(tab->arg.flag & MINUS))
	tab->arg.flag = (tab->arg.flag | ZERO);
	else if (format[tab->fmt] == ' ' && !(tab->arg.flag & PLUS))
	tab->arg.flag = (tab->arg.flag | SPACE);
	else if (format[tab->fmt] == '.')
	{
		tab->arg.flag = (tab->arg.flag | PREC) & ~(ZERO);
		get_size_flag(tab, &format[tab->fmt + 1], 1);
	}
	else if (format[tab->fmt] == 'h')
		if (tab->arg.flag & H)
			tab->arg.flag = (tab->arg.flag | HH) & ~(H);
		else
			tab->arg.flag = (tab->arg.flag | H);
	else if (format[tab->fmt] == 'l')
		if (tab->arg.flag & L)
			tab->arg.flag = (tab->arg.flag | LL) & ~(L);
		else
			tab->arg.flag = (tab->arg.flag | L);
	else
		return (0);
	return (1);
}

int 	check_arg(const char *format, t_printf *tab)
{
	int 			mode;

	mode = 0;
	while (format[tab->fmt])
	{
		if (mode == 0 && format[tab->fmt] == '%')
		{
			mode = 1;
			tab->fmt++;
		}
		if (mode == 0)
			fill_buffer(format[tab->fmt++], tab);
		else if (format[tab->fmt] == '%')
		{
			fill_buffer(format[tab->fmt++], tab);
			return (mode = 0);
		}
		else
		{
			if (arg_flags(tab, format))
				tab->fmt++;
			else if (get_size_flag(tab, &format[tab->fmt], 0))
				tab->fmt++;
			else if (arg_printf(tab, format[tab->fmt]))
			{
				tab->fmt++;
				return (1);
			}
		}
	}
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 13:34:41 by stdenis           #+#    #+#             */
/*   Updated: 2019/03/08 18:36:42 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		arg_printf(t_printf *tab, char c)
{
	if (c == 's' && ++tab->fmt)
		tab->arg.type = S;
	else if ((c == 'd' || c == 'i') && ++tab->fmt)
		tab->arg.type = DI;
	else if (c == 'x' && ++tab->fmt)
		tab->arg.type = X;
	else if (c == 'X' && ++tab->fmt)
		tab->arg.type = XX;
	else if (c == 'o' && ++tab->fmt)
		tab->arg.type = O;
	else if ((c == 'u' || c == 'U') && ++tab->fmt)
		tab->arg.type = U;
	else if (c == 'p' && ++tab->fmt)
		tab->arg.type = P;
	else if (c == 'c' && ++tab->fmt)
		tab->arg.type = C;
	else if (c == 'f' && ++tab->fmt)
		tab->arg.type = F;
	else if (c == '%' && ++tab->fmt)
		tab->arg.type = PERCENT;
	else
		tab->arg.type = 999;
	if (c == 'U')
		tab->arg.flag = (tab->arg.flag | L) & ~(H);
	return (1);
}

int		conv_flags(t_printf *tab, const char *format)
{
	if (format[tab->fmt] == 'h')
		if (tab->arg.flag & H)
			tab->arg.flag = (tab->arg.flag | HH) & ~(H);
		else
			tab->arg.flag = (tab->arg.flag | H);
	else if (format[tab->fmt] == 'l')
		if (tab->arg.flag & L)
			tab->arg.flag = (tab->arg.flag | LL) & ~(L);
		else
			tab->arg.flag = (tab->arg.flag | L) & ~(H) & ~(HH);
	else if (format[tab->fmt] == 'L')
		tab->arg.flag = (tab->arg.flag | LDBL);
	else if (format[tab->fmt] == 'j')
		tab->arg.flag = (tab->arg.flag | J);
	else if (format[tab->fmt] == 'z')
		tab->arg.flag = (tab->arg.flag | Z);
	else
		return (0);
	return (1);
}

int		arg_flags(t_printf *tab, const char *format)
{
	if (format[tab->fmt] == '-')
		tab->arg.flag = (tab->arg.flag | MINUS) & ~(ZERO);
	else if (format[tab->fmt] == '+')
		tab->arg.flag = (tab->arg.flag | PLUS) & ~(SPACE);
	else if (format[tab->fmt] == '#')
		tab->arg.flag = (tab->arg.flag | HASH);
	else if (format[tab->fmt] == '0')
		tab->arg.flag = (tab->arg.flag | ZERO);
	else if (format[tab->fmt] == ' ')
		tab->arg.flag = (tab->arg.flag | SPACE);
	else if (format[tab->fmt] == '.')
	{
		tab->arg.flag = (tab->arg.flag | PREC);
		get_size_flag(tab, &format[tab->fmt + 1], 1);
	}
	else
		return (0);
	return (1);
}

int		check_arg(const char *format, t_printf *tab)
{
	int		mode;

	mode = 0;
	while (format[tab->fmt])
	{
		if (mode == 0 && format[tab->fmt] == '%' && ++tab->fmt)
			mode = 1;
		if (mode == 0)
			fill_buffer(format[tab->fmt++], tab);
		else if (format[tab->fmt] != '\0')
		{
			if (format[tab->fmt] != '\0' && arg_flags(tab, format))
				++tab->fmt;
			else if (format[tab->fmt] != '\0' && conv_flags(tab, format))
				++tab->fmt;
			else if (get_size_flag(tab, &format[tab->fmt], 0))
				++tab->fmt;
			else if (arg_printf(tab, format[tab->fmt]))
				return (1);
		}
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 13:32:02 by stdenis           #+#    #+#             */
/*   Updated: 2019/02/25 15:19:24 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf(const char *format, ...)
{
	va_list		ap;
	t_printf	tab;

	va_start(ap, format);
	ft_memset(&tab, 0, sizeof(tab));
	ft_memset(&tab.arg, 0, sizeof(tab.arg));
	while (check_arg(format, &tab))
	{
		if (tab.arg.type == S)
			check_string(va_arg(ap, char *), &tab);
		else if (tab.arg.type == C)
			check_char((char)va_arg(ap, int), &tab);
		else if (tab.arg.type == DI)
			check_integer(ap, &tab);
		ft_memset(&tab.arg, 0, sizeof(tab.arg));
	}
	ft_putstr(tab.buffer);
	va_end(ap);
	return (tab.rtn);
}

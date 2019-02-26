/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 13:32:02 by stdenis           #+#    #+#             */
/*   Updated: 2019/02/26 15:35:26 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf(const char *format, ...)
{
	va_list		ap;
	t_printf	tab;

	if (format == NULL)
		return (1);
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
		else if (tab.arg.type == U)
			check_unsigned_integer(ap, &tab);
		else if (tab.arg.type == PERCENT)
			fill_buffer('%', &tab);
		else if (tab.arg.type == P)
			check_pointers(va_arg(ap, void *), &tab);
		else if (tab.arg.type == XX || tab.arg.type == X)
			check_hexadecimal(ap, &tab);
		else if (tab.arg.type == O)
			check_octal(ap, &tab);
		ft_memset(&tab.arg, 0, sizeof(tab.arg));
	}
	write(1, tab.buffer, tab.buff);
	va_end(ap);
	return (tab.rtn);
}

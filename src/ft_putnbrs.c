/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 13:55:31 by stdenis           #+#    #+#             */
/*   Updated: 2019/03/07 10:19:58 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "ft_printf.h"

bool	check_flags(t_flags flag, int method, t_flags first, t_flags second)
{
	if (method == 1 && (flag & (first | second)))
		return (true);
	else if (method == 2 && (flag & first) && !(flag & second))
		return (true);
	else if (method == 3 && !(flag & (first | second)))
		return (true);
	return (false);
}

void	ft_putnbr_buffer_conv(uintmax_t res, t_printf *tab, char *base)
{
	uintmax_t	base_l;
	uintmax_t	rtn;

	base_l = (uintmax_t)ft_strlen(base);
	if (res > 0)
	{
		rtn = (res / base_l);
		ft_putnbr_buffer_conv(rtn, tab, base);
	}
	if (res != 0)
	{
		rtn = (res % base_l);
		fill_buffer(base[rtn], tab);
	}
}

void	ft_putnbr_buffer_pos(uintmax_t res, t_printf *tab)
{
	if (res > 9)
	{
		ft_putnbr_buffer_pos(res / 10, tab);
		fill_buffer((res % 10) + '0', tab);
	}
	else
		fill_buffer(res + '0', tab);
}

void	ft_putnbr_buffer_neg(intmax_t res, t_printf *tab)
{
	if (res < -9)
	{
		ft_putnbr_buffer_neg(res / 10, tab);
		fill_buffer(-(res % 10) + '0', tab);
	}
	else if (res <= 0)
		fill_buffer((-res) + '0', tab);
}

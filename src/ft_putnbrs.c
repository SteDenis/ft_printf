/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 13:55:31 by stdenis           #+#    #+#             */
/*   Updated: 2019/03/07 20:11:05 by stdenis          ###   ########.fr       */
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

void	ft_putnbr_buffer_conv(uintmax_t res, t_printf *tab, char *base, int blen)
{
	uintmax_t	rtn;

	if (res > 0)
	{
		if (blen == 8)
			ft_putnbr_buffer_conv((res >> 3), tab, base, blen);
		else if (blen == 16)
			ft_putnbr_buffer_conv((res >> 4), tab, base, blen);
	}
	if (res != 0)
	{
		rtn = res & (blen - 1);
		fill_buffer(base[rtn], tab);
	}
}

void	ft_putnbr_buffer_pos(uintmax_t res, t_printf *tab)
{
	uintmax_t mod;
	uintmax_t p;

	mod = 0;
	p = 0;
	if (res > 9)
	{
		mod = res / 10;
		ft_putnbr_buffer_pos(mod, tab);
		p = (mod << 3) + (mod << 1);
		mod = res - p;
		fill_buffer((mod) + '0', tab);
	}
	else
		fill_buffer(res + '0', tab);
}

void	ft_putnbr_buffer_neg(intmax_t res, t_printf *tab)
{
	intmax_t mod;
	intmax_t p;

	mod = 0;
	p = 0;
	if (res < -9)
	{
		mod = res / 10;
		ft_putnbr_buffer_neg(mod, tab);
		p = (mod << 3) + (mod << 1);
		mod = res - p;
		fill_buffer(-(mod) + '0', tab);
	}
	else if (res <= 0)
		fill_buffer((-res) + '0', tab);
}

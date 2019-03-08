/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 13:55:31 by stdenis           #+#    #+#             */
/*   Updated: 2019/03/08 18:17:59 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "ft_printf.h"

bool	check_flags(t_flags flag, int m, t_flags f, t_flags s)
{
	if (m == 1 && (flag & f) && (flag & s))
		return (true);
	else if (m == 2 && (flag & f) && !(flag & s))
		return (true);
	else if (m == 3 && !(flag & f) && !(flag & s))
		return (true);
	return (false);
}

void	putnbr_c(uintmax_t res, t_printf *tab, char *base, int bl)
{
	uintmax_t	rtn;

	if (res > 0)
	{
		if (bl == 8)
			putnbr_c((res >> 3), tab, base, bl);
		else if (bl == 16)
			putnbr_c((res >> 4), tab, base, bl);
	}
	if (res != 0)
	{
		rtn = res & (bl - 1);
		fill_buffer(base[rtn], tab);
	}
}

int		uint_length(uintmax_t value, int base)
{
	size_t	i;

	i = 0;
	while (value > 0)
	{
		i++;
		value /= base;
	}
	return ((i == 0) ? 1 : i);
}

void	putnbr_p(uintmax_t res, t_printf *tab)
{
	uintmax_t mod;
	uintmax_t p;

	mod = 0;
	p = 0;
	if (res > 9)
	{
		mod = res / 10;
		putnbr_p(mod, tab);
		p = (mod << 3) + (mod << 1);
		mod = res - p;
		fill_buffer((mod) + '0', tab);
	}
	else
		fill_buffer(res + '0', tab);
}

void	putnbr_n(intmax_t res, t_printf *tab)
{
	intmax_t mod;
	intmax_t p;

	mod = 0;
	p = 0;
	if (res < -9)
	{
		mod = res / 10;
		putnbr_n(mod, tab);
		p = (mod << 3) + (mod << 1);
		mod = res - p;
		fill_buffer(-(mod) + '0', tab);
	}
	else if (res <= 0)
		fill_buffer((-res) + '0', tab);
}

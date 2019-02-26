/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 13:55:31 by stdenis           #+#    #+#             */
/*   Updated: 2019/02/26 14:02:53 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "ft_printf.h"

void	ft_putnbr_buffer_conv(intmax_t res, t_printf *tab, char *base)
{
	intmax_t	base_l;
	intmax_t	rtn;

	base_l = (intmax_t)ft_strlen(base);
	if (res > 0)
	{
		rtn = ((res / base_l) < 0) ? -(res / base_l) : (res / base_l);
		ft_putnbr_buffer_conv(rtn, tab, base);
	}
	if (res != 0)
	{
		rtn = ((res % base_l) < 0) ? -(res % base_l) : (res % base_l);
		fill_buffer(base[rtn], tab);
	}
}

void	ft_putnbr_buffer_pos(intmax_t res, t_printf *tab)
{
	if (res > 9)
	{
		ft_putnbr_buffer_pos(res / 10, tab);
		fill_buffer((res % 10) + '0', tab);
	}
	else if (res >= 0)
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
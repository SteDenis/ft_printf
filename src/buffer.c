/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 13:33:17 by stdenis           #+#    #+#             */
/*   Updated: 2019/03/07 15:58:09 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	fill_buffer(char c, t_printf *tab)
{
	if (tab->buff == 2047)
	{
		write(1, tab->buffer, tab->buff);
		ft_memset(tab->buffer, '\0', 2048);
		tab->buff = 0;
		tab->buffer[tab->buff] = c;
	}
	else
		tab->buffer[tab->buff] = c;
	++tab->buff;
	++tab->rtn;
}

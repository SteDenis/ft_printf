/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_unicode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 18:59:20 by stdenis           #+#    #+#             */
/*   Updated: 2019/03/08 19:39:16 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wchar.h>
#include "ft_printf.h"

size_t	ft_strlen_unicode(const wchar_t *str)
{
	size_t	i;
	size_t	len;

	i = -1;
	len = 0;
	while (str[++i] != L'\0')
		len += len_octects(str[i]);
	return (len);
}

size_t	len_octects(const wchar_t c)
{
	uint32_t	val;
	size_t		len;

	val = (uint32_t)c;
	len = 0;
	if (val <= 0x7F)
		return (len = 1);
	else if (val <= 0x7FF)
		return (len = 2);
	else if (val <= 0xFFFF)
		return (len = 3);
	else if (val <= 0x10FFFF)
		return (len = 4);
	return (len);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 13:58:57 by stdenis           #+#    #+#             */
/*   Updated: 2019/02/25 13:38:05 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		get_size_flag(t_printf *tab, const char *str, int prec)
{
	int		i;
	int		value;

	i = 0;
	value = 0;
	while ((str[i] >= '0' && str[i] <= '9'))
	{
		value = 10 * value + (str[i] - '0');
		i++;
	}
	if (i > 0)
	{
		if (prec == 1)
		{
			tab->fmt += i;
			tab->arg.prec = value;
		}
		else
		{
			tab->arg.larg = value;
			tab->fmt += i - 1;
		}
		return (1);
	}
	return (0);
}

void	*ft_memset(void *b, int c, size_t n)
{
	size_t			i;

	i = 0;
	while (i < n)
	{
		((unsigned char*)b)[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

void	ft_putstr(char const *s)
{
	int i;

	i = 0;
	if (s != NULL)
		while (s[i] != '\0')
		{
			write(1, &s[i], 1);
			i++;
		}
}

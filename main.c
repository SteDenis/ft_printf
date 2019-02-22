/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 13:18:00 by stdenis           #+#    #+#             */
/*   Updated: 2019/02/22 18:06:46 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_print.h"

void	fill_buffer(char c, t_printf *tab)
{
	static size_t	i;

	if (i == 2047)
	{
		write(1, tab->buffer, i);
		ft_memset(tab->buffer, '\0', 2048);
		i = 0;
		tab->buffer[i] = c;
	}
	else
		tab->buffer[i] = c;
	i++;
	tab->rtn += 1;
}

int 	arg_printf(t_printf *tab, char c)
{
	if (c == 's')
		tab->arg.type = 1;
	else
		return (0);
	return (1);
}

int 	arg_flags(t_printf *tab, const char *format, int *i)
{
	if (format[*i] == '-')
		tab->arg.flag.minus = true;
	else if (format[*i] == '+')
		tab->arg.flag.plus = true;
	else if (format[*i] == '#')
		tab->arg.flag.hash = true;
	else if (format[*i] == '0')
		tab->arg.flag.zero = true;
	else if (format[*i] == ' ')
		tab->arg.flag.space = true;
	else if (format[*i] == '.')
	{
		*i += 1;
		tab->arg.flag.prec = true;
		get_size_flag(tab, &format[*i], i, 1);
	}
	else
		return (0);
	return (1);
}

int 	check_arg(const char *format, t_printf *tab)
{
	static int		i;
	int 			mode;

	mode = 0;
	while (format[i])
	{
		if (mode == 0 && format[i] == '%')
		{
			mode = 1;
			i++;
		}
		if (mode == 0)
			fill_buffer(format[i++], tab);
		else
		{
			if (arg_flags(tab, format, &i))
				i++;
			else if (get_size_flag(tab, &format[i], &i, 0))
				i++;
			else if (arg_printf(tab, format[i]))
			{
				i++;
				return (1);
			}
		}
	}
	return (0);
}

void	fill_with_string(const char *value, t_printf *tab)
{
	size_t		i;
	size_t		len;

	i = -1;
	len = (tab->arg.prec > 0) ? tab->arg.prec : ft_strlen(value);
	tab->arg.larg -= (tab->arg.larg > 0) ? len : 0;
	while (!tab->arg.flag.minus && tab->arg.larg-- > 0)
		fill_buffer(' ', tab);
	while (value[++i] && len-- > 0)
		fill_buffer(value[i], tab);
	while (tab->arg.flag.minus && tab->arg.larg-- > 0)
		fill_buffer(' ', tab);
}

int		ft_print(const char *format, ...)
{
	va_list		ap;
	t_printf	tab;

	va_start(ap, format);
	while (check_arg(format, &tab))
	{
		if (tab.arg.type == 1)
			fill_with_string(va_arg(ap, char *), &tab);
		ft_memset(&tab.arg, 0, sizeof(tab.arg));
	}
	ft_putstr(tab.buffer);
	va_end(ap);
	return (tab.rtn);
}

int		main(int argc, char **argv)
{
	int a, b;
	(void)argc;
	(void)argv;
	a = ft_print("%40.5s %40s|", "testfdsfdsfsdfsd", "lalala");
	printf("\n");
	b = printf("%40.5s %40s|", "testfdsfdsfsdfsd", "lalala");
	printf("\n%d %d\n", a, b);
	return (0);
}
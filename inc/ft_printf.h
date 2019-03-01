/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 13:37:39 by stdenis           #+#    #+#             */
/*   Updated: 2019/02/26 15:34:39 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINT_H
#define FT_PRINT_H

#include <stdarg.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdint.h>

typedef unsigned int	flags;

enum {
	HASH = 0x01,
	PLUS = 0x02,
	MINUS = 0x04,
	ZERO = 0x08,
	SPACE = 0x10,
	PREC = 0x20,
	HH = 0x40,
	H = 0x80,
	LL = 0x100,
	L = 0x200
};

enum {
	C = 0,
	S = 1,
	P = 2,
	DI = 3,
	O = 4,
	U = 5,
	X = 6,
	XX = 7,
	PERCENT = 8,
	F = 9
};

typedef	struct			s_arg
{
	int		type;
	int		larg;
	int		prec;
	void	*value;
	flags	flag;
}						t_arg;

typedef struct			s_printf
{
	t_arg	arg;
	size_t	fmt;
	size_t	buff;
	size_t	rtn;
	char	buffer[2048];
}						t_printf;

/*
** buffer.c
*/
void	fill_buffer(char c, t_printf *tab);

/*
** arguments.c
*/
int 	check_arg(const char *format, t_printf *tab);

/*
** string.c
*/
void	fill_with_string(const char *value, t_printf *tab, size_t len);
void	check_string(const char *value, t_printf *tab);

/*
** char.c
*/
void	check_char(const char value, t_printf *tab);

/*
** integer.c
*/
void	check_integer(va_list ap, t_printf *tab);
void	check_unsigned_integer(va_list ap, t_printf *tab);

/*
** hexadecimal.c
*/
void	check_hexadecimal(va_list ap, t_printf *tab);

/*
** octal.c
*/
void	check_octal(va_list ap, t_printf *tab);

/*
** pointers.c
*/
void	check_pointers(void *value, t_printf *tab);

/*
** float.c
*/
void	check_float(va_list ap, t_printf *tab);

/*
** ft_putnbrs.c
*/
void	ft_putnbr_buffer_pos(intmax_t res, t_printf *tab);
void	ft_putnbr_buffer_neg(intmax_t res, t_printf *tab);
void	ft_putnbr_buffer_conv(intmax_t res, t_printf *tab, char *base);

/*
** ft_printf.c
*/
int		ft_printf(const char *format, ...);

/*
** utils.c
*/
void					*ft_memset(void *b, int c, size_t n);
size_t					ft_strlen(const char *str);
void					ft_putstr(char const *s);
int						get_size_flag(t_printf *tab, const char *str, int prec);
int						int_length(intmax_t value, int base);
#endif

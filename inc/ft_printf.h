/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 13:37:39 by stdenis           #+#    #+#             */
/*   Updated: 2019/03/07 10:26:17 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINT_H
#define FT_PRINT_H

#include <stdarg.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdint.h>
#include "double.h"


#include <stdio.h>

typedef unsigned int	t_flags;
typedef void			(*t_fnc[9])	(va_list, void*);

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
	L = 0x200,
	LDBL = 0x400,
	Z = 0x800,
	J = 0x1000,
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
	F = 8,
	PERCENT = 9
};

typedef	struct			s_arg
{
	int		type;
	int		larg;
	int		prec;
	void	*value;
	t_flags	flag;
}						t_arg;

typedef struct			s_printf
{
	t_arg	arg;
	size_t	fmt;
	size_t	buff;
	size_t	rtn;
	t_fnc	dispatcher;
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
void	check_string(const char *value, t_printf *tab);
void	get_string(va_list ap, void *ptr);

/*
** char.c
*/
void	get_char(va_list ap, void *ptr);

/*
** integer.c
*/
void	check_integer(va_list ap, void *ptr);
void	check_unsigned_integer(va_list ap, void *ptr);
void		prepare_un(uintmax_t value, t_printf *tab);

/*
** hexadecimal.c
*/
void	check_hexadecimal(va_list ap, void *ptr);

/*
** octal.c
*/
void	check_octal(va_list ap, void *ptr);

/*
** pointers.c
*/
void	get_pointers(va_list ap, void *ptr);

/*
** double.c
*/
void			check_float(va_list ap, void *ptr);
void		printing_flags_ldbl(t_dbl *tab_dbl, t_printf *tab, char fill);

/*
** utils_double.c
*/
void		rounding_ldbl(t_dbl *tab_dbl, t_printf *tab);
void		re_positioning_pointers(t_dbl *tab_dbl, uint32_t last, int decal);
void		check_inf_or_nan(t_uniondbl *uni, t_dbl *tab_dbl, t_printf *tab);
void		calculate_nbr_integer(t_dbl *tab_dbl);

/*
** transform_ldbl.c
*/
void		transform_ldbl_80b(t_dbl *tab_dbl, t_printf *tab);

/*
** ft_putnbrs.c
*/
void	ft_putnbr_buffer_pos(uintmax_t res, t_printf *tab);
void	ft_putnbr_buffer_neg(intmax_t res, t_printf *tab);
void	ft_putnbr_buffer_conv(uintmax_t res, t_printf *tab, char *base);
bool	check_flags(t_flags flag, int method, t_flags first, t_flags second);

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 13:37:39 by stdenis           #+#    #+#             */
/*   Updated: 2019/02/22 17:27:09 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINT_H
#define FT_PRINT_H

#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct			s_flg
{
	bool	hash;
	bool	plus;
	bool	minus;
	bool	zero;
	bool	space;
	bool	prec;
}						t_flg;

typedef	struct			s_arg
{
	int		type;
	int		larg;
	int		prec;
	void	*value;
	t_flg	flag;
}						t_arg;

typedef struct			s_printf
{
	t_arg	arg;
	size_t	rtn;
	char	buffer[2048];
}						t_printf;


/*
** utils.c
*/
void					*ft_memset(void *b, int c, size_t n);
size_t					ft_strlen(const char *str);
void					ft_putstr(char const *s);
int						get_size_flag(t_printf *tab, const char *str, int *k, int prec);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 12:53:48 by stdenis           #+#    #+#             */
/*   Updated: 2019/03/04 20:21:03 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOUBLE_H
#define DOUBLE_H

typedef struct		s_dbl
{
	double			dbl;
	long double		ldbl;
	int				entier;
	uint32_t		numbers[2000];
	uint32_t		*head;
	uint32_t		*last;
	uint32_t		*before_dot;
	uint32_t		*digits;
}					t_dbl;

#endif

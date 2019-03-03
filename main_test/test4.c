/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 10:54:55 by stdenis           #+#    #+#             */
/*   Updated: 2019/03/03 14:10:43 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include <float.h>
#include <stdint.h>
#include <limits.h>
#include <stdlib.h>

#define MAX(a,b) ((a)>(b) ? (a) : (b))
#define MIN(a,b) ((a)<(b) ? (a) : (b))

static char *fmt_u(uintmax_t x, char *s)
{
	unsigned long y;
	for (   ; x>ULONG_MAX; x/=10) *--s = '0' + x%10;
	for (y=x;           y; y/=10) *--s = '0' + y%10;
	return s;
}

void double_to_bits(void *var)
{
	int		byte;
	unsigned char *tmp = (unsigned char *)var;
	int i = sizeof(int);
	int j;

	while (i--)
	{
		j = 7;
		while (j >= 0)
		{
			byte = (tmp[i] >> j) & 1;
			printf("%d", byte);
			j--;
		}
		printf(" ");
	}
}

int 	main(void)
{
	char buf[999999];
	double c = LDBL_MIN;
	long double y =  LDBL_MIN;
	printf("MANT_DIG = %d, MAX_EXP = %d  %d\n", LDBL_MANT_DIG, LDBL_MAX_EXP, 3U);
	//uint32_t big[(LDBL_MANT_DIG+28)/29 + 1          // mantissa expansion
	//			 + (LDBL_MAX_EXP+LDBL_MANT_DIG+28+8)/9]; // exponent expansion
	uint32_t big[2000];
	uint32_t *a, *d, *r, *z;
	int e2=0, e, i, j, l;
	int			p = 10;

	if (y < 0)
		y=-y;
	y = frexpl(y, &e2) * 2;
	double_to_bits(&e2);
	printf("\nfrexp() makes %Lf * 2^%d\n", y, e2);
	if (y)
		e2--;
	double_to_bits(&e2);
	printf("\n");
	if (y)
	{
		y *= 0x1p28;
		e2 -= 28;
	}
	double_to_bits(&e2);
	printf("\n");
	printf("frexp() makes %Lf * 2^%d\n", y, e2);
	if (e2<0) a=r=z=big;
	else a=r=z=big+sizeof(big)/sizeof(*big) - LDBL_MANT_DIG - 1;

	do {
		*z = y;
		y = 1000000000*(y-*z++);
	} while (y);
	while (e2>0) {
		uint32_t carry=0;
		int sh=MIN(29,e2);
		for (d=z-1; d>=a; d--) {
			uint64_t x = ((uint64_t)*d<<sh)+carry;
			*d = x % 1000000000;
			carry = x / 1000000000;
		}
		if (carry) *--a = carry;
		while (z>a && !z[-1]) z--;
		e2-=sh;
	}
	while (e2<0) {
		uint32_t carry=0, *b;
		int sh=MIN(9,-e2), need=1+(p+LDBL_MANT_DIG/3U+8)/9;
		for (d=a; d<z; d++) {
			uint32_t rm = *d & (1<<sh)-1;
			*d = (*d>>sh) + carry;
			carry = (1000000000>>sh) * rm;
		}
		if (!*a) a++;
		if (carry) *z++ = carry;
		/* Avoid (slow!) computation past requested precision */
		b = r;
		if (z-b > need) z = b+need;
		e2+=sh;
	}

	if (a<z) for (i=10, e=9*(r-a); *a>=i; i*=10, e++);
	else e=0;


	char t = 'f';
	j = p - ((t)!='f')*e - ((t)=='g' && p);
	if (j < 9*(z-r-1)) {
		uint32_t x;
		/* We avoid C's broken division of negative numbers */
		d = r + 1 + ((j+9*LDBL_MAX_EXP)/9 - LDBL_MAX_EXP);
		j += 9*LDBL_MAX_EXP;
		j %= 9;
		for (i=10, j++; j<9; i*=10, j++);
		x = *d % i;
		/* Are there any significant digits past j? */
		if (x || d+1!=z) {
			long double round = 2/LDBL_EPSILON;
			long double small;
			if ((*d/i & 1) || (i==1000000000 && d>a && (d[-1]&1)))
				round += 2;
			if (x<i/2) small=0x0.8p0;
			else if (x==i/2 && d+1==z) small=0x1.0p0;
			else small=0x1.8p0;
			round*=-1;
			small*=-1;
			*d -= x;
			/* Decide whether to round by probing round+small */
			if (round+small != round) {
				*d = *d + i;
				while (*d > 999999999) {
					*d--=0;
					if (d<a) *--a=0;
					(*d)++;
				}
				for (i=10, e=9*(r-a); *a>=i; i*=10, e++);
			}
		}
		if (z>d+1) z=d+1;
	}



	for (; z>a && !z[-1]; z--);

	if (e > INT_MAX-l) return -1;
	if (e>0) l+=e;

	if (a>r) a=r;
	for (d=a; d<=r; d++) {
		char *s = fmt_u(*d, buf+9);
		if (d!=a) while (s>buf) *--s='0';
		else if (s==buf+9) *--s='0';
		//out(f, s, buf+9-s);
		printf("%s", s);
	}
	printf(".");
	//if (p || (fl&ALT_FORM)) out(f, ".", 1);
	for (; d<z && p>0; d++, p-=9) {
		char *s = fmt_u(*d, buf+9);
		while (s>buf) *--s='0';
		printf("%s", s);
	}
	//printf("\n\n\n%.18000Lf", LDBL_MIN);
}

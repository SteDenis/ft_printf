#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>


void ft_show_tab(int *tab) {
	int i = 64;
	while (i >= 0) {
		printf("%d", tab[i]);
		if (i % 8 == 0)
			printf(" ");
		i--;
	}
}

void double_to_bits2(double val, int tab_bit[65])
{
	unsigned idx;
	int i;
	unsigned char *ptr = (unsigned char*) &val;
	i = 63;
	for (idx=CHAR_BIT * sizeof val; idx-- ; ) {
		if (ptr[idx/CHAR_BIT] & (1u << (idx%CHAR_BIT)))
			tab_bit[i] = 1;
		else
			tab_bit[i] = 0;
		i--;
	}
}
int ft_get_expo(int tab_bit[65]) {
	int i = 62;
	int ex = 1024;
	int res = 0;
	printf("\nexposant calcul: ");
	while (i >= 52) {
		printf("%d", tab_bit[i]);
		if (tab_bit[i] == 1)
			res = res + ex;
		ex = ex / 2;
		i--;
	}
	printf("\n");
	return (res - 1023);
}
double ft_puissance(int puis) {
	if (puis == 0)
		return (1);
	int i = 0;
	double res = 1;
	while (i < puis) {
		res = res * 2;
		i++;
	}
	return (res);
}
double ft_puissance_negative(int puis) {
	int i = 0;
	double res = 1;
	double ex = 1;
	puis = puis * -1;
	while (i < puis) {
		ex = ex * 5;
		i++;
	}
	res = ex;
	return (res);
}
double ft_get_fraction(int tab_bit[65]) {
	int i = 51;
	double ex = 1;
	double res = 1;
	double d;
	double puis = 2;
	//tab_bit[i] = 1;
	while (i >= 0) {
		printf("%d", tab_bit[i]);
		/*if (tab_bit[i] == 1) {
			res = res + ex;
		}
		res = res * 10;
		i--;
		ex = ex * 5;*/
		if (tab_bit[i] == 1)
			res += 1 / puis;
		i--;
		puis = puis + puis;
	}
	return (res);
}
int size_nb_g(__int128 nb) {
	int i = 0;
	while (nb > 0) {
		i++;
		nb = nb / 10;
	}
	return (i);
}
void ft_into_char(char int_to_char[2048], double nombre, double deb, int exposant) {
	typedef unsigned __int128 NU128;
	typedef          __int128 NI128;
	char test[2048];
	int i;

	__int64_t a = (__int64_t)nombre;
	unsigned __int128 double_to_int = (unsigned __int128)nombre;
	while (nombre > 554112867134706473364364839029663282043.00) {
		nombre = nombre / 10;
	}
	double_to_int = (unsigned __int128)nombre;
	i = size_nb_g(double_to_int) - 1;
	while (double_to_int > 0) {
		int_to_char[i] = double_to_int % 10 + '0';
		i--;
		double_to_int = double_to_int / 10;
	}
}
int main()
{
	double nb = DBL_MAX;
	int tab_bit[65];
	double exposant;
	double fraction;
	double nb_final;
	__int64_t es;
	char final_nb[2048];
	int i;
	double_to_bits2(nb, tab_bit);
	i = ft_get_expo(tab_bit);
	if (i >= 0) {
		exposant = ft_puissance(i);
	} else {
		exposant = ft_puissance_negative(i);
		i = i * -1;
	}
	printf("valeur pour le calcul : %f, v exposant : %d\n", exposant, i);
	printf("signe du nombre (0 = + && 1 = -) : %d\npartie binaire de la fraction : ", tab_bit[63]);
	ft_show_tab(tab_bit);
	printf("\n\n");
	fraction = ft_get_fraction(tab_bit);
	//printf("\nFraction : %f", fraction);
	//nb_final = fraction * exposant;
	long f = 2;
	nb_final = fraction * exposant;
	printf("\nvaleur final double: %f\n", nb_final);
	ft_into_char(final_nb, nb_final, nb, i);
	printf("nombre que j'affiche : %s\n", final_nb);
	printf("nombre a afficher   : %f", nb);
}


#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>


#define MAX_FCONVERSION	512
#define MAX_EXPT	5	/* largest possible exponent field */
#define MAX_FRACT	39	/* largest possible fraction field */

#define TESTFLAG(x)	0


typedef double rtype;

extern double modf(double, double *);
#define	to_char(n)	((n) + '0')
#define	to_digit(c)	((c) - '0')
#define _isNan(arg)	((arg) != (arg))

static int cvt (rtype arg, int prec, char *signp, int fmtch,
		char *startp, char *endp);
static char *roundd (double fract, int *exp, char *start, char *end,
		    char ch, char *signp);
static char *exponent(char *p, int exp, int fmtch);


/*
 * _finite arg not Infinity or Nan
 */
static int _finite(rtype d)
{
#if ENDIAN == ENDIAN_LITTLE
    struct IEEEdp {
	unsigned manl:32;
	unsigned manh:20;
	unsigned exp:11;
	unsigned sign:1;
    } *ip;
#else
    struct IEEEdp {
	unsigned sign:1;
	unsigned exp:11;
	unsigned manh:20;
	unsigned manl:32;
    } *ip;
#endif

    ip = (struct IEEEdp *)&d;
    return (ip->exp != 0x7ff);
}


static void dtoaf (char *dbuf, rtype arg, int fmtch, int width, int prec)
{
	char	buf[MAX_FCONVERSION+1], *cp;
	char	sign;
	int	size;

	if( !_finite(arg) ) {
		if( _isNan(arg) )
			strcpy (dbuf, "NaN");
		else if( arg < 0) 
			strcpy (dbuf, "-Infinity");
		else
			strcpy (dbuf, "Infinity");
		return;
	}

	if (prec == 0)
		prec = 6;
	else if (prec > MAX_FRACT)
		prec = MAX_FRACT;

	/* leave room for sign at start of buffer */
	cp = buf + 1;

    /*
     * cvt may have to round up before the "start" of
     * its buffer, i.e. ``intf("%.2f", (double)9.999);'';
     * if the first character is still NUL, it did.
     * softsign avoids negative 0 if _double < 0 but
     * no significant digits will be shown.
     */
	*cp = '\0';
	size = cvt (arg, prec, &sign, fmtch, cp, buf + sizeof(buf));
	if (*cp == '\0')
		cp++;

	if (sign)
		*--cp = sign, size++;

	cp[size] = 0;
	memcpy (dbuf, cp, size + 1);
}


double	ft_modf(double a, double *b)
{
	double c;
	double d;

	c = a;
	*b = (double)c;
	d = a - (double)c;
	return (d);
}

#include <math.h>
double ffmod(double x, double y)
{
	int ir,iy;
	double r,w;

	r = fabs(x);
	y = fabs(y);
	(void)frexp(y,&iy);
	while (r >= y) {
		(void)frexp(r,&ir);
		w = ldexp(y,ir-iy);
		r -= w <= r ? w : w*(double)0.5;
	}
	return x >= (double)0 ? r : -r;
}
static int
cvt(rtype number, int prec, char *signp, int fmtch, char *startp, char *endp)
{
	register char *p, *t;
	register double fract;
	double integer, tmp;
	int dotrim, expcnt, gformat;
	dotrim = expcnt = gformat = 0;
	if (number < 0) {
		number = -number;
		*signp = '-';
	} else
		*signp = 0;
	fract = modf(number, &integer);

	/* get an extra slot for rounding. */
	t = ++startp;

	/*
	 * get integer portion of number; put into the end of the buffer; the
	 * .01 is added for modf(356.0 / 10, &integer) returning .59999999...
	 */
	/*long double a;
	modfl((long double)number, &a);
	long double tmpp;
	for (p = endp - 1; a; ++expcnt) {
		tmpp = modfl(a / 10, &a);
		printf("%d", (int)((tmpp + .01) * 10.0));
	}
	printf("\n");

	long double a;
	modfl((long double)number, &a);
	long double tmpp;
	for (p = endp - 1; a; ++expcnt) {
		tmpp = fmod(a, 10.0);
		a = a - tmpp;
		printf("%d", (int)((tmpp + .01) * 10.0));
	}

	for (p = endp - 1; integer; ++expcnt) {
		tmp = modf(integer / 10, &integer);
		printf("%d", (int)((tmp + .01) * 10.0));
		*p-- = to_char((int)((tmp + .01) * 10.0));
	}*/
	long double a = integer;
	long double tmpp;
	long double pp;
	for (p = endp - 1; a; ++expcnt) {
		//tmp = modf(integer / 10, &integer);
		//printf("%d", (int)((ffmod(integer, 10.0) + .01)));
		pp = ffmod(a, 10.0);
		a -= pp;
		*p-- = to_char((int)pp);
		a /= 10.0;
	}
	switch (fmtch) {
	case 'f':
		/* reverse integer into beginning of buffer */
		if (expcnt)
			for (; ++p < endp; *t++ = *p);
		else
			*t++ = '0';
		/*
		 * if precision required or alternate flag set, add in a
		 * decimal point.
		 */
		if (prec || TESTFLAG(ALTERNATE_FORM))
			*t++ = '.';
		/* if requires more precision and some fraction left */
		if (fract) {
			if (prec)
				do {
					fract = modf(fract * 10, &tmp);
					*t++ = to_char((int)tmp);
				} while (--prec && fract);
			if (fract)
				startp = roundd(fract, (int *)NULL, startp,
				    t - 1, (char)0, signp);
		}
		for (; prec--; *t++ = '0');
		break;
	}
	return (t - startp);
}


static char *
roundd(double fract, int *exp, char *start, char *end, char ch, char *signp)
{
	double tmp;

	if (fract)
		(void)modf(fract * 10, &tmp);
	else
		tmp = to_digit(ch);
	if (tmp > 4)
		for (;; --end) {
			if (*end == '.')
				--end;
			if (++*end <= '9')
				break;
			*end = '0';
			if (end == start) {
				if (exp) {	/* e/E; increment exponent */
					*end = '1';
					++*exp;
				}
				else {		/* f; add extra digit */
				*--end = '1';
				--start;
				}
				break;
			}
		}
	/* ``"%.3f", (double)-0.0004'' gives you a negative 0. */
	else if (*signp == '-')
		for (;; --end) {
			if (*end == '.')
				--end;
			if (*end != '0')
				break;
			if (end == start)
				*signp = 0;
		}
	return (start);
}

static char *
exponent(char *p, int exp, int fmtch)
{
	char *t;
	char expbuf[MAX_FCONVERSION];

	*p++ = fmtch;
	if (exp < 0) {
		exp = -exp;
		*p++ = '-';
	}
	else
		*p++ = '+';
	t = expbuf + MAX_FCONVERSION;
	if (exp > 9) {
		do {
			*--t = to_char(exp % 10);
		} while ((exp /= 10) > 9);
		*--t = to_char(exp);
		for (; t < expbuf + MAX_FCONVERSION; *p++ = *t++);
	}
	else {
		*p++ = '0';
		*p++ = to_char(exp);
	}
	return (p);
}


char buffer[99999];

#include <stdio.h>
#include <float.h>
#include <limits.h>

int main () {
	int i = 5;
	double f = FLT_MAX;
	dtoaf (buffer, f, 'f', 5, 0);
	printf("%s", buffer);
	printf("\n%f", f);
	return(0);
}
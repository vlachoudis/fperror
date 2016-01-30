/**
 * $Id$
 *
 * Author:	Vasilis.Vlachoudis@cern.ch
 * Date:	29-Jan-2016
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "fperror.h"

using namespace std;

/**
 * Numerically robust quadratic equation: x^2 + bx + c = 0.
 * @param a,b,c	coefficients
 * @param x1,x2	two real solutions.
 *              In case of no real solution then -b/2a is returned
 * @param acc	accuracy of comparison operations
 * @return the number of real solutions
 */
inline int quadratic(const Double b, const Double c,
		Double *x1, Double *x2, const Double acc)
{
	b.dump(cout,"b=") << endl;
	c.dump(cout,"c=") << endl;

	Double D = b*b - 4.0*c;
	D.dump(cout,"D=") << endl;

	Double sD = sqrt(D);
	sD.dump(cout,"  sD=") << endl;

	Double fc = 4.0*c;
	Double b2 = b*b;
	Double ssD;
	if (b2 >= fabs(fc))
		ssD = b * sqrt(1.0 - fc/b2);
	else
		ssD = sqrt(fc) * sqrt(1.0 + b2/fc);
	ssD.dump(cout," ssD=") << endl;

	Double sc = 2.0*sqrt(c);
	Double sssD = sqrt((b+sc)*(b-sc));
	sssD.dump(cout,"sssD=") << endl;

	if (D <= 0.0) {
		*x1 = *x2 = -0.5*b;	// Always return this as a solution!!!
		if (D >= -acc*(b*b+fabs(c)))
			return 1;
		else
			return 0;
	} else {
		Double bD;
		if (b>0.0)
			bD = -b - sqrt(D);
		else
			bD = -b + sqrt(D);
		*x1 = 0.5 * bD;
		*x2 = 2.0 * c / bD;
		return 2;
	}
	return -10;
} /* quadratic */

int main(int ac, char *av[])
{
//	float  f = 0.1f;
//	double d = 0.1;
//	long double ld = 0.1l;

//	cout << "f="  << setprecision(30) << f << endl;
//	cout << "d="  << setprecision(30) << d << endl;
//	cout << "ld=" << setprecision(30) << ld << endl;

	Double b(19792412.3l);
	Double c(0.000001l);

	Double x1, x2;
	Double acc = 1e-15f;
	quadratic(b,c,&x1,&x2,acc);

	cout << "x1="; x1.dump(cout) << endl;
	cout << "x2="; x2.dump(cout) << endl;

//	Double A, B;

//	a.errorBits(5);
//
//	cout << "  a=" << a << endl;
//	cout << "  b=" << b << endl;
//	cout << "a+a=" << a+a << endl;
//	cout << "a+b=" << a+b << endl;
//	cout << "b+b=" << b+b << endl;
//
//	cout << "a-a=" << a-a << endl;
//	cout << "a-b=" << a-b << endl;
//	cout << "b-b=" << b-b << endl;

//	cout << d << endl;
//	d.addBits(1);
//	cout << "+1bit: " << d << endl;
//	d.addBits(-1);
//	cout << "-1bit: " << d << endl;
//
//	cout << endl;
//	cout << "a=" << a << endl;
//	cout << "b=" << b << endl;
//	cout << "a+b=" << a+b << endl;
//	cout << "a-b=" << a-b << endl;

//	double _a = 439864.324;
//	double _b;
//	double _one = 0.0000001;
//	for (int i=0; i<10; i++) {
//		_b = _a * (1.0 + _one);
//		_one *= 10;
//
//		cout << endl;
//		a = (float)_a;
//		b = (float)_b;
//		cout << "          a="; a.dump(cout); cout << endl;
//		cout << "          b="; b.dump(cout); cout << endl;
//		cout << "        a+b="; (a+b).dump(cout); cout << endl;
//		cout << "        a-b="; (a-b).dump(cout); cout << endl;
//		cout << "        a*a="; (a*a).dump(cout); cout << endl;
//		cout << "        b*b="; (b*b).dump(cout); cout << endl;
//		cout << "    a*a-b*b="; (a*a-b*b).dump(cout); cout << endl;
//		cout << "(a+b)*(a-b)="; ((a+b)*(a-b)).dump(cout); cout << endl;
//		cout << "       diff="; ((a*a-b*b) - ((a+b)*(a-b))).dump(cout); cout << endl;
//
////		cout << "          a=" << b << endl;
////		cout << "          b=" << b << endl;
////		cout << "        a+b=" << a+b << endl;
////		cout << "        a-b=" << a-b << endl;
////		cout << "        a*a=" << a*a << endl;
////		cout << "        b*b=" << b*b << endl;
////		cout << "    a*a-b*b=" << a*a-b*b << endl;
////		cout << "(a+b)*(a-b)=" << (a+b)*(a-b) << endl;
////		cout << "       diff=" << (a*a-b*b) - ((a+b)*(a-b)) << endl;
//	}

//	cout << endl;
//	A = _a;
//	B = _b;
//	cout << "          A=" << A << endl;
//	cout << "          B=" << B << endl;
//	cout << "        A+B=" << A+B << endl;
//	cout << "        A-B=" << A-B << endl;
//	cout << "        A*A=" << A*A << endl;
//	cout << "        B*B=" << B*B << endl;
//	cout << "    A*A-B*B=" << A*A-B*B << endl;
//	cout << "(A+B)*(A-B)=" << (A+B)*(A-B) << endl;
//	cout << "       DIFF=" << (A*A-B*B) - ((A+B)*(A-B)) << endl;

//	cout << endl;
//	a = 0.1;
//	Float s = 0.0;
//	cout << "s=" << s << endl;
//	for (int i=0; i<10; i++) {
//		s = s + a;
//		cout << i << " s="; s.dump(cout); cout << endl;
//	}

//	Double A(100.00001);
//	Double B(100.0);
//	cout << endl;
//	cout << "          A=" << A << endl;
//	cout << "          B=" << B << endl;
//	cout << "        A*A=" << A*A << endl;
//	cout << "        B*B=" << B*B << endl;
//	cout << "    A*A-B*B=" << A*A-B*B << endl;
//	cout << "(A+B)*(A-B)=" << (A+B)*(A-B) << endl;

//	printf("Num=%.21g frac=%.21g exp=%d BITS=%16lX\n",d, frac, exp, *(unsigned long*)&d);

//	float d = 1.0;
//	frac = frexpf(d, &exp);
//	printf("Num=%.21g frac=%.21g exp=%d BITS=%16lX\n",d, frac, exp, *(unsigned long*)&d);
//
//	float dp = nextafterf(d,0.1);
//	float dn = nextafterf(d,100.0);
//
//	*(unsigned long *)&d |= 1;
//	frac = frexpf(d, &exp);
//	printf("Num=%.21g frac=%.21g exp=%d BITS=%16lX\n",d, frac, exp, *(unsigned long*)&d);
//
//	d = dn;
//	frac = frexpf(d, &exp);
//	printf("Num=%.21g frac=%.21g exp=%d BITS=%16lX\n",d, frac, exp, *(unsigned long*)&d);
//
//	d = dp;
//	frac = frexpf(d, &exp);
//	printf("Num=%.21g frac=%.21g exp=%d BITS=%16lX\n",d, frac, exp, *(unsigned long*)&d);

//	printf("1+2^%d-2 = %.21g\n", exp-Float::precision, exp2(exp-Float::precision-2)+ 1.0);
//	printf("1+2^%d-1 = %.21g\n", exp-Float::precision, exp2(exp-Float::precision-1)+ 1.0);
//	printf("1+2^%d   = %.21g\n", exp-Float::precision, exp2(exp-Float::precision  )+ 1.0);
//	printf("1+2^%d+1 = %.21g\n", exp-Float::precision, exp2(exp-Float::precision+1)+ 1.0);


//	cout << f.precision << endl;
//	cout << d.precision << endl;
//	printf("unsigned = %d\n",sizeof(unsigned));
//	printf("unsigned long = %d\n",sizeof(unsigned long));
//	printf("unsigned long long = %d\n",sizeof(unsigned long long));
} // main

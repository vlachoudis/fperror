/**
 * A template number class for estimating the floating point rounding
 * errors introduced in operations
 *
 * Replace all variables with
 *	float  -> Float
 *	double -> Double
 *
 * The code will double all operations once in the type used (float/double)
 * and once in "long double" precision.
 * At any moment you can inspect the error of the operation
 *
 * e.g.
 *	Float a = 100.00001f;
 *	Float b = 100.0f;
 *
 *	// The following two are equivalent
 *	Float c = a*a - b*b;		// - introduces a catastrophic cancellation
 *	Float d = (a+b)*(a-b);		// +/- introduces a benign cancellation
 *
 *	c.dump(cout,"c=") << endl;
 *	d.dump(cout,"d=") << endl;
 *
 * Author:	Vasilis.Vlachoudis@cern.ch
 * Date:	29-Jan-2016
 */

#ifndef __FPERROR_H
#define __FPERROR_H

#include <ostream>
#include <iomanip>

#include <math.h>
#include <assert.h>

/*================================== Number ===================================*/
template <class T>
class Number {
public:
	T		value;
	long double	real;

public:
	Number() {};
	Number(const float f)                  : value((T)f),    real(f) {}
	Number(const double f)                 : value((T)f),    real(f) {}
	Number(const long double r)            : value((T)r),    real(r) {}
	Number(const T f, const long double r) : value(f),       real(r) {}
	Number(const Number<T>& f)             : value(f.value), real(f.real) {}

	/** @return error */
	long double	error()			const	{ return (long double)value - real; }

	/** set number */
	Number<T>&	operator = (const float f)	{ value = real = f; return *this; }
	Number<T>&	operator = (const double f)	{ value = real = f; return *this; }
	Number<T>&	operator = (const Number<T> f)	{ value = f.value; real = f.real; return *this; }
//			operator T ()		const	{ return value; }
//	long double	operator () ()	const	{ return real; }

	Number<T>&	operator +=(const Number<T>& f) {
				value += f.value;
				real  += f.real;
				return *this;
			}
	Number<T>	operator +(const Number<T>& n)	const { return Number<T>(value+n.value, real+n.real); }
	Number<T>	operator +(const float f)	const { return Number<T>(value+f, real+f); }
	Number<T>	operator +(const double f)	const { return Number<T>(value+f, real+f); }

	Number<T>&	operator -=(const Number<T>& f) {
				value -= f.value;
				real  -= f.real;
				return *this;
			}
	Number<T>	operator -(const Number<T>& n)	const { return Number<T>(value-n.value, real-n.real); }
	Number<T>	operator -(const float f)	const { return Number<T>(value-f, real-f); }
	Number<T>	operator -(const double f)	const { return Number<T>(value-f, real-f); }
	Number<T>	operator -()			const { return Number<T>(-value, -real); }

	Number<T>&	operator *=(const Number<T>& f) {
				value *= f.value;
				real  *= f.real;
				return *this;
			}
	Number<T>	operator *(const Number<T>& n)	const { return Number<T>(value*n.value, real*n.real); }
	Number<T>	operator *(const float f)	const { return Number<T>(value*f, real*f); }
	Number<T>	operator *(const double f)	const { return Number<T>(value*f, real*f); }

	Number<T>&	operator /=(const Number<T>& f) {
				value /= f.value;
				real  /= f.real;
				return *this;
			}
	Number<T>	operator /(const Number<T>& n)	const { return Number<T>(value/n.value, real/n.real); }
	Number<T>	operator /(const float f)	const { return Number<T>(value/f, real/f); }
	Number<T>	operator /(const double f)	const { return Number<T>(value/f, real/f); }

	bool		operator ==(const Number<T>& n)	const { return value==n.value; }
	bool		operator ==(const float f)	const { return value==f; }
	bool		operator ==(const double f)	const { return value==f; }

	bool		operator !=(const Number<T>& n)	const { return value!=n.value; }
	bool		operator !=(const float f)	const { return value!=f; }
	bool		operator !=(const double f)	const { return value!=f; }

	bool		operator <(const Number<T>& n)	const { return value<n.value; }
	bool		operator <(const float f)	const { return value<f; }
	bool		operator <(const double f)	const { return value<f; }

	bool		operator <=(const Number<T>& n)	const { return value<=n.value; }
	bool		operator <=(const float f)	const { return value<=f; }
	bool		operator <=(const double f)	const { return value<=f; }

	bool		operator >(const Number<T>& n)	const { return value>n.value; }
	bool		operator >(const float f)	const { return value>f; }
	bool		operator >(const double f)	const { return value>f; }

	bool		operator >=(const Number<T>& n)	const { return value>=n.value; }
	bool		operator >=(const float f)	const { return value>=f; }
	bool		operator >=(const double f)	const { return value>=f; }

	std::ostream&	dump(std::ostream& s, const char* prefix=NULL) const {
				if (prefix) s << prefix;
				s <<  "f:"  << std::setw(sizeof(T)*3+6) << std::setprecision(sizeof(T)*3) << std::left << value;
				s <<  " r:" << std::setw(56) << std::setprecision(50)<< std::left << real;
				s <<  " e:" << std::setw(15) << std::setprecision(9) << std::left << error();
				return s;
			}
}; // class Number<T>

template <class T> inline Number<T> operator + (const float  a, const Number<T>& b) { return b+a; }
template <class T> inline Number<T> operator + (const double a, const Number<T>& b) { return b+a; }

template <class T> inline Number<T> operator - (const float  a, const Number<T>& b) { return Number<T>(a-b.value, a-b.real); }
template <class T> inline Number<T> operator - (const double a, const Number<T>& b) { return Number<T>(a-b.value, a-b.real); }

template <class T> inline Number<T> operator * (const float  a, const Number<T>& b) { return b*a; }
template <class T> inline Number<T> operator * (const double a, const Number<T>& b) { return b*a; }

template <class T> inline Number<T> operator / (const float  a, const Number<T>& b) { return Number<T>(a/b.value, a/b.real); }
template <class T> inline Number<T> operator / (const double a, const Number<T>& b) { return Number<T>(a/b.value, a/b.real); }

typedef Number<float>  Float;
typedef Number<double> Double;

#define MATH_FUNC(T,F,E)  \
	inline Number<T> F(const Number<T>& x) \
		{ return Number<T>(F##E(x.value), F##l(x.real)); }

#define MATH_FUNCF(T,F,E)  \
	inline Number<T> F(const Number<T>& x) \
		{ return Number<T>(F##f(x.value), F##l(x.real)); }

#define MATH_FUNC2(T,F,E) \
	inline Number<T> F(const Number<T>& x, const Number<T>& y) \
		{ return Number<T>(F##E(x.value, y.value), F##l(x.real, y.real)); }

MATH_FUNC(float,acos,f)
MATH_FUNC(float,acosh,f)
MATH_FUNC(float,asin,f)
MATH_FUNC(float,asinh,f)
MATH_FUNC(float,atan,f)
MATH_FUNC(float,atanh,f)
MATH_FUNC(float,cbrt,f)
MATH_FUNC(float,ceil,f)
MATH_FUNC(float,cos,f)
MATH_FUNC(float,cosh,f)
MATH_FUNC(float,erf,f)
MATH_FUNC(float,erfc,f)
MATH_FUNC(float,exp,f)
MATH_FUNC(float,exp2,f)
MATH_FUNC(float,expm1,f)
MATH_FUNCF(float,fabs,f)
MATH_FUNC(float,floor,f)
MATH_FUNC(float,lgamma,f)
MATH_FUNC(float,log,f)
MATH_FUNC(float,log10,f)
MATH_FUNC(float,log1p,f)
MATH_FUNC(float,log2,f)
MATH_FUNC(float,logb,f)
MATH_FUNC(float,nearbyint,f)
MATH_FUNC(float,rint,f)
MATH_FUNC(float,round,f)
MATH_FUNC(float,sin,f)
MATH_FUNC(float,sinh,f)
MATH_FUNCF(float,sqrt,f)
MATH_FUNC(float,tan,f)
MATH_FUNC(float,tanh,f)
MATH_FUNC(float,tgamma,f)
MATH_FUNC(float,trunc,f)
MATH_FUNC(float,y0,f)
MATH_FUNC(float,y1,f)

MATH_FUNC2(float,remainder,f)
MATH_FUNC2(float,pow,f)
MATH_FUNC2(float,nextafter,f)
MATH_FUNC2(float,hypot,f)
MATH_FUNC2(float,fmod,f)
MATH_FUNC2(float,fmin,f)
MATH_FUNC2(float,fmax,f)
MATH_FUNC2(float,fdim,f)
MATH_FUNC2(float,copysign,f)
MATH_FUNC2(float,atan2,f)

MATH_FUNC(double,acos,)
MATH_FUNC(double,acosh,)
MATH_FUNC(double,asin,)
MATH_FUNC(double,asinh,)
MATH_FUNC(double,atan,)
MATH_FUNC(double,atanh,)
MATH_FUNC(double,cbrt,)
MATH_FUNC(double,ceil,)
MATH_FUNC(double,cos,)
MATH_FUNC(double,cosh,)
MATH_FUNC(double,erf,)
MATH_FUNC(double,erfc,)
MATH_FUNC(double,exp,)
MATH_FUNC(double,exp2,)
MATH_FUNC(double,expm1,)
MATH_FUNC(double,fabs,)
MATH_FUNC(double,floor,)
MATH_FUNC(double,lgamma,)
MATH_FUNC(double,log,)
MATH_FUNC(double,log10,)
MATH_FUNC(double,log1p,)
MATH_FUNC(double,log2,)
MATH_FUNC(double,logb,)
MATH_FUNC(double,nearbyint,)
MATH_FUNC(double,rint,)
MATH_FUNC(double,round,)
MATH_FUNC(double,sin,)
MATH_FUNC(double,sinh,)
MATH_FUNC(double,sqrt,)
MATH_FUNC(double,tan,)
MATH_FUNC(double,tanh,)
MATH_FUNC(double,tgamma,)
MATH_FUNC(double,trunc,)
MATH_FUNC(double,y0,)
MATH_FUNC(double,y1,)

MATH_FUNC2(double,remainder,)
MATH_FUNC2(double,pow,)
MATH_FUNC2(double,nextafter,)
MATH_FUNC2(double,hypot,)
MATH_FUNC2(double,fmod,)
MATH_FUNC2(double,fmin,)
MATH_FUNC2(double,fmax,)
MATH_FUNC2(double,fdim,)
MATH_FUNC2(double,copysign,)
MATH_FUNC2(double,atan2,)

#undef MATH_FUNC
#undef MATH_FUNC2

#endif

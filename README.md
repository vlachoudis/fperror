Floating point rounding error estimation library

Author:	Vasilis.Vlachoudis@cern.ch
Date:	29-Jan-2016

A template number class for estimating the floating point rounding
errors introduced in operations

Replace all variables with
     `float  -> Float`
     `double -> Double`

The code will double all operations once in the type used (float/double)
and once in "long double" precision.
At any moment you can inspect the error of the operation

e.g.
```
#include <iostream>
#include <fperror.h>

int main(int, char**)
{
     Float a = 100.00001f;
     Float b = 100.0f;

     // The following two are equivalent
     Float c = a*a - b*b;		// - introduces a catastrophic cancellation
     Float d = (a+b)*(a-b);		// +/- introduces a benign cancellation

     c.dump(std::cout,"c=") << std::endl;
     d.dump(std::cout,"d=") << std::endl;
     return 0;
}
```
Compile and run:
```
$ make test
g++ -o test test.cc -Wall -I.. -O3
$ ./test
c=f:0.001953125        r:0.0015258789644576609134674072265625                     e:0.000427246036
d=f:0.00152587890625   r:0.0015258789644576609134674072265625                     e:-5.82076609e-11
```
It is visible that the error introduced by the first operation is dramatic
compared to the second.

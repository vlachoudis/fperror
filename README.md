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
     Float a = 100.00001f;
     Float b = 100.0f;

     // The following two are equivalent
     Float c = a*a - b*b;		// - introduces a catastrophic cancellation
     Float d = (a+b)*(a-b);		// +/- introduces a benign cancellation

     c.dump(cout,"c=") << endl;
     d.dump(cout,"d=") << endl;
```


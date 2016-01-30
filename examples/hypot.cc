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

//typedef Float	Real;
typedef Double	Real;

int main(int ac, char *av[])
{
	Real A = 100000.001l;
	Real B = 0.000001l;

	A.dump(cout,"A=") << endl;
	B.dump(cout,"B=") << endl;

	Real C = sqrt(A*A + B*B);
	C.dump(cout,"C=") << endl;

	Real D;
	if (A < B) 
		D = A * sqrt(1.0 + B*B/A/A);
	else
		D = B * sqrt(1.0 + A*A/B/B);
	D.dump(cout,"D=") << endl;

	Real diff = C-D;
	diff.dump(cout,"d=") << endl;
} // main

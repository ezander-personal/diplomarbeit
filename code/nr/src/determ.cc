#include <math.h>

#include "nrutil.h"
#include "_nr.h"

#define TINY 1.0e-20;


double determ( double** a, int n )
{
	int indx[n]; 
	double d;
	
	ludcmp2( a, n, indx-1, &d );
	for( int j=1; j<=n; j++ ) d*=a[j][j];
	
	return d;
}
	

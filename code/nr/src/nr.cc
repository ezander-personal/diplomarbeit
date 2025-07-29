#include "nrutil.h"
#include "nr.h"
#include "_nr.h"


double determ(dMatrix x, int n)
{
	return determ( x.nrmat(), n );
}

void  four1(dVector& data, int nn, int isign)
{
	four1( data.nrvec(), nn, isign );
}

void  tqli(dVector& d, dVector& e, int n, dMatrix& z)
{
	tqli( d.nrvec(), e.nrvec(), n, z.nrmat() );
}

void  tred2(dMatrix& a, int n, dVector& d, dVector& e)
{
	tred2( a.nrmat(), n, d.nrvec(), e.nrvec() );
}




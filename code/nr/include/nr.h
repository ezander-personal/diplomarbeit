#ifndef __NR_H__
#define __NR_H__

#include "nrutil.h"

	double determ(dMatrix x, int n);
	void  four1(dVector& data, int nn, int isign);
	void  tqli(dVector& d, dVector& e, int n, dMatrix& z);
	void  tred2(dMatrix& a, int n, dVector& d, dVector& e);

#endif // __NR_H__

#ifndef __NR_H__
#define __NR_H__

#include "nrutil.h"

	double determ(dMatrix x, int n);
	// void  fit(double *x, double *y, int ndata, double *sig, int mwt, double *a, 
	void  four1(dVector& data, int nn, int isign);	
	// double gammln(double xx);
	// double gammq(double a, double x);
	// void  gcf(double *gammcf, double a, double x, double *gln);
	// void  gser(double *gamser, double a, double x, double *gln);
	// void  ludcmp(double **a, int n, int *indx, double *d);
	// void  realft(double *data, int n, int isign);
	void  tqli(dVector& d, dVector& e, int n, dMatrix& z);
	void  tred2(dMatrix& a, int n, dVector& d, dVector& e);

#endif // __NR_H__

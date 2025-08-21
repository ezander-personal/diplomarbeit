#ifndef ___NR_H__
#define ___NR_H__

#include "nrutil.h"

double determ(double** x, int n);
void  four1(double *data, int nn, int isign);
void  ludcmp(double **a, int n, int *indx, double *d);
void  ludcmp2(double **a, int n, int *indx, double *d);
void  tqli(double *d, double *e, int n, double **z);
void  tred2(double **a, int n, double *d, double *e);

#endif // ___NR_H__

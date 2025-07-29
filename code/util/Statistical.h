// ;-*-C++-*-
// tells emacs to use C++-mode instead of C-mode


#ifndef __STATISTICAL_H__
#define __STATISTICAL_H__

#include "nrutil.h" 


double mean( const double* x, int n );
inline double mean( const dVector& x ) { return mean( x(), x.getsize() ); }


double deviation( const double* x, int n );
double deviation( const double* x, int n, double mean );

inline double deviation( const dVector& x ) { return deviation( x(), x.getsize() ); }
inline double deviation( const dVector& x, double mean ) {return deviation( x(), x.getsize(), mean );}

double sqrMean( const double* x, int n );
inline double sqrMean( const dVector& x ) { return sqrMean( x(), x.getsize() ); }


void autoCorr( const double* x, int n, double* corr, int tauMin, int tauMax, 
	       boolean correction=FALSE );


void linReg( const double* x, const double* y, int start, int stop, double& m, double& n,  
	     boolean logX=FALSE, boolean logY = FALSE );
void linReg( const double* x, const double* y, int start, int stop, double& m, double& n,  
	     double& err_m, double& err_n, boolean logX=FALSE, boolean logY = FALSE );


double getMin( const double* x, int n);
double getMax( const double* x, int n);
inline double getMin( const dVector& x ){ return getMin( x(), x.getsize() ); }
inline double getMax( const dVector& x ) { return getMax( x(), x.getsize() ); }

void getMinMax( const double* x, int n, double& min, double& max);
inline void getMinMax( const dVector& x, double& min, double& max ){getMinMax( x(), x.getsize(), min, max );}


double correlationCoefficient( const double* x, const double* y, int count );
double correlationCoefficient2( const double* x, const double* y, int count, double rangeExp );
double difference( const double* x, const double* y, int count );

#endif // __STATISTICAL_H__


















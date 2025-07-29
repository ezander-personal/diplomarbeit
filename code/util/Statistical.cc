#include <math.h>

#include "General.h"
#include "Statistical.h"

#include "nr.h"

double mean( const double* x, int n )
{
  double sum = 0.0;
  
  for( int i=0; i<n; i++ ) { sum += *x;  x++; }

  return sum/double( n );
}

double deviation( const double* x, int n )
{
  return deviation( x, n, mean( x, n ) );
}

double deviation( const double* x, int n, double mean )
{
  double sum = 0.0;
  
  for( int i=0; i<n; i++ ) { sum += (*x-mean) * (*x-mean); x++; }

  return sqrt( sum / double(n-1) );
}


double sqrMean( const double* x, int n )
{
  double sum = 0.0;
  
  for( int i=0; i<n; i++ ) { sum += *x * *x; x++; }

  return sqrt( sum / double(n-1) );
}



double autoCorr( const double* x, int n, int tau, int count, double mean, boolean correction )
{
  int m = n-tau;
  if( count<m && count!=-1 ) m=count;
  double corr = correction ?  double(count) / m : 1.0;

  double sum = 0.0;
  
  for( register int i=0, j=tau; i<m; i++, j++ ) sum += (x[i]-mean)*(x[j]-mean);

  return sum*corr;
}

void autoCorr( const double* x, int n, double* corr, int tauMin, int tauMax, boolean correction )
{
  int m=n-tauMin;

  double mean = ::mean( x, n );

  for( int i=0; i<=(tauMax-tauMin); i++ )
    {
      corr[i] = autoCorr( x, n, i+tauMin, m, mean, correction );
    }
}

void linReg( const double* x, const double* y, int start, int stop, double& m, double& n,  boolean logX, boolean logY)
{
  double sx=0.0, sy=0.0, sxy=0.0, sxx=0.0, syy=0.0;

  double xv, yv;

  for( int i=start; i<stop; i++)
    {
      xv = x ? x[i] : i;
      if( logX ) xv = log( xv );

      yv = y ? y[i] : i;
      if( logY ) yv = log( yv );

      sx  += xv;
      sy  += yv;
      sxx += xv * xv;
      sxy += xv * yv;
      syy += yv * yv;
    }

  int cn = stop-start;

  n = ( sy*sxx - sxy*sx ) / ( cn*sxx - sx*sx );
  m = ( cn*sxy - sx *sy ) / ( cn*sxx - sx*sx );
}


void linReg( const double* x, const double* y, int start, int stop, double& m, double& n,  double& err_m, double& err_n, boolean logX, boolean logY )
{
  logX=logY; logY=logX;
  // double chi2, q;
  // fit( x,y,stop-start, NULL, 0, &m, &n, &err_m, &err_n, &chi2, &q );

 
  double sx=0.0, sy=0.0, sxy=0.0, sxx=0.0, syy=0.0;

  double xv, yv;

  for( int i=start; i<stop; i++)
    {
      xv = x ? x[i] : i;
      if( logX ) xv = log( xv );

      yv = y ? y[i] : i;
      if( logY ) yv = log( yv );

      sx  += xv;
      sy  += yv;
      sxx += xv * xv;
      sxy += xv * yv;
      syy += yv * yv;
    }

  int s = stop-start;
  double d = s*sxx-sx*sx;

  n = ( sy*sxx - sxy*sx ) / d;
  m = ( s*sxy  - sx *sy ) / d;

  double chi2 = 0.0;

  for( int i=start; i<stop; i++)
    {
      xv = x ? x[i] : i;
      if( logX ) xv = log( xv );

      yv = y ? y[i] : i; if( logY ) yv = log( yv ); 
      double f = yv - m*xv - n; 

      chi2 += f*f; 
    }

  err_m = sqrt( s / d * chi2 / (s-2) );
  err_n = sqrt( sxx / d * chi2 / (s-2) );
}


double getMin( const double* x, int n)
{
  double min=*x;
  for( int i=1; i<n; i++ ) 
    if( *(++x) < min ) min=*x;
  return min;
}

double getMax( const double* x, int n)
{
  double max=*x;
  for( int i=1; i<n; i++ ) 
    if( *(++x) > max ) max=*x;
  return max;
}

void getMinMax( const double* x, int n, double& min, double& max)
{
  min=*x, max=*x;
  for( int i=1; i<n; i++ ) 
    {
      ++x;
      if( *x < min ) min=*x;
      if( *x > max ) max=*x;
    }
}

double correlationCoefficient( const double* px, const double* py, int count )
{
  ASSERT( count > 0 );

  double meanX = mean( px, count );
  double meanY = mean( py, count );
  
  double sig_x=0.0, sig_y=0.0, sig_xy=0.0;
  
  for( int i=0; i<count; i++ )
    {
      double x=*px++, y=*py++;

      sig_x  += (x-meanX)*(x-meanX);
      sig_y  += (y-meanY)*(y-meanY);
      sig_xy += (x-meanX)*(y-meanY);
    }

  if( sig_x == 0.0 || sig_y == 0 ) return HUGE_VAL;
  
  return sig_xy / sqrt( sig_x * sig_y );
}

double correlationCoefficient2( const double* px, const double* py, int count, double rangeExp )
{

  double m=0.0, n=0.0;
  linReg( px, py, 0, count, m, n );

  double err=0.0;
  for( int i=0; i<count; i++ )
    {
      double diff=(py[i]-(m*px[i]+n));
      err += diff*diff;
    }
  err = sqrt(err)/sqrt(1+m*m);

  return -err * pow(double(count),-rangeExp);
}


double correlationCoefficient2b( const double* px, const double* py, int count, double rangeExp )
{
  ASSERT( count > 0 );

  double meanX = mean( px, count );
  double meanY = mean( py, count );
  
  double sig_x=0.0, sig_y=0.0, sig_xy=0.0;
  
  for( int i=0; i<count; i++ )
    {
      double x=*px++, y=*py++;

      sig_x  += (x-meanX)*(x-meanX);
      sig_y  += (y-meanY)*(y-meanY);
      sig_xy += (x-meanX)*(y-meanY);
    }

  if( sig_x == 0.0 || sig_y == 0 ) return HUGE_VAL;

  return -(1-sig_xy / sqrt( sig_x * sig_y )) * pow(double(count),-rangeExp);
}


double difference( const double* px, const double* py, int count )
{
  double df=0.0;
  
  for( int i=0; i<count; i++ )
    df += (*px++) - (*py++);
  
  return df;

}




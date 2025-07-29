#include <math.h>
#include <stdlib.h>
#include <memory.h>
#include "General.h"

#include "Statistical.h"


inline int cmp_int( int a, int b) { return a-b; };
int cmp_i( const int* a, const int* b ) { return cmp_int( *a, *b ); }

double calcInfo( const int* x, int count )
{
  int y[count];
  memcpy( y, x, count * sizeof(int) );

  qsort( y, count, sizeof(int), (__compar_fn_t)cmp_i );

  double info=0.0, p=0.0, inv=1.0/float(count);
  double gp=0;
  int n=0,m=0;

  for( int i=0; i<=count; i++ )
    {
      if( i==0 )
	p=inv,m=1;
      else if( i==count )
	info+=p*log(p), gp+=p, n+=m;
      else
	if( y[i]==y[i-1] ) {
	  p+=inv;
	  m++;
	}
	else {
	  info+=p*log(p), gp+=p, n+=m;
	  p=inv, m=1;
	}
    }

  return -info;
}

void mutual( const String& ifilename, const String& ofilename, double epsilon, int min_time, int max_time )
{
  int rows = getFileRows( ifilename );
  if( max_time<=0 ) max_time=rows/10;

  dVector t(rows), x(rows);
  dVector I( min_time, max_time );

  if( readFileColsInc( ifilename, 0, t(), x(), NULL ) ) exit( 1 );
    
  I.clear();

  int max_i = rows - max_time-1;
  double mean_ = mean( x );
  double dev = deviation( x, mean_ );
  double x_diff = epsilon * 0.01 * dev;

  iVector n1(rows), n2(rows);
  for( int i=0; i<rows; i++ )
    n1[i] = int((x[i]-mean_)/x_diff);

  double H1=calcInfo( n1(), max_i );

  for( int tau=min_time; tau<=max_time; tau++ )
    {
      for( int i=0; i<max_i; i++ )
	{
	  n2[i] = n1[i] + (n1[i+tau]<<16);
	}

      double H2 = calcInfo( n2(), max_i );

      I[tau] = 2*H1 - H2;
    }


  ofstream fout( ofilename, ios::out | ios::trunc );

  for( int tau=min_time; tau<=max_time-1; tau++ )
    {
      fout << tau*(t[2]-t[1]) << tab << I[tau] << endl;
    }

  fout.close();

  gpInfo gpi( ofilename );
  gpi.using1( 1 ). using2( 2 );
  gpi.Title( "mutual information" ).xTitle( "t" ).yTitle( "N" );
  gpi.setPlotStyle( LINESPOINTS ).pause();
  gpi.NewFile();
  gpi.AppendToFile();
}














#include <math.h>

#include "General.h"

#include "Statistical.h"


void recurr( const String& ifilename, const String& ofilename, double epsilon, int min_time, int max_time )
{
  int rows = getFileRows( ifilename );
  if( max_time<=0 ) max_time=rows/10;

  double t[ rows ], x[ rows ];
  dVector N( min_time, max_time );

  if( readFileColsInc( ifilename, 0, t, x, NULL ) ) exit( 1 );
    
  N.clear();

  int max_i = rows - max_time-1;
  double mean_ = mean( x, rows );
  double dev = deviation( x, rows, mean_ );
  double x_diff = epsilon * 0.01 * dev;

  for( int i=0; i<max_i; i++ )
    {
      for( int tau=min_time; tau<=max_time; tau++ )
	{
	  if( fabs( x[i]-x[i+tau] ) <= x_diff ) 
	    {
	      N[tau]++;
	    }
	}
    }

  ofstream fout( ofilename, ios::out | ios::trunc );

  for( int tau=min_time; tau<=max_time-1; tau++ )
    {
      fout << tau*(t[2]-t[1]) << tab << N[tau] << endl;
    }

  fout.close();

  gpInfo gpi( ofilename );
  gpi.using1( 1 ). using2( 2 );
  gpi.Title( "recurrence times" ).xTitle( "t" ).yTitle( "N" );
  gpi.setPlotStyle( LINESPOINTS ).pause();
  gpi.NewFile();
  gpi.AppendToFile();
}














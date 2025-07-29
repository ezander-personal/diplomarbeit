#include <math.h>

#include "General.h"

#include "Statistical.h"


void makets( const String& ifilename, const String& ofilename, int axis, int nDiff, int points, double time, boolean ignore, boolean normalize )
{
  int rows = getFileRows( ifilename );
  int cols = getFileCols( ifilename );

  if( rows==-1 || cols==-1 ) exit( 1 );
  if( axis >= cols ) exit( 1 );
  if( axis<0 )
    {
      if( cols==1 ) 
	axis=0;
      else
	axis=1;
    }

  int maxCount = int( (rows-1) / nDiff )+1;
  if( (points < maxCount) && (points>1) ) maxCount = points;

  int maxRows = std::max(maxCount*nDiff, rows );


  dVector t( rows), x( rows );
  if( readFileCol( ifilename, axis, x(), cols, maxRows ) ) exit( 1 );
  if( cols>1 )
    readFileCol( ifilename, 0, t(), cols, maxRows );

  dVector y( maxCount );
  for( int i=0, ii=0; i<maxCount; i++, ii+=nDiff )
    y[i] = x[ii];

  if( normalize )
    {
      double ymean = mean( y );
      for( int i=0; i<maxCount; i++ ) y[i]-=ymean;
      double yfact = 1.0 / sqrMean( y );
      for( int i=0; i<maxCount; i++ ) y[i]*=yfact;
    }


  ofstream fout( ofilename, ios::out | ios::trunc );

  for( int i=0, ii=0; i<maxCount; i++, ii+=nDiff )
    {
      if( cols>1 && !ignore )
	fout << t[ii] << tab;
      else
	fout << time*ii << tab;
      
      fout << y[i] << endl;
    }

  fout.close();


  gpInfo gpi( ofilename );
  gpi.using1( 1 ). using2( 2 );
  gpi.Title( "time series" ).xTitle( "t" );
  gpi.setPlotStyle( LINES ).pause();
  gpi.NewFile();
  gpi.AppendToFile();
}














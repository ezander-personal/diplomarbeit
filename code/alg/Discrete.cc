#include "General.h"
#include "Statistical.h"


void discretize( const String& ifilename, const String& ofilename, double level )
{
  int rows = getFileRows( ifilename );

  dVector t(rows), x(rows);

  if( readFileColsInc( ifilename, 0, t(), x(), NULL ) ) exit( 1 );

  double xMean = mean( x );
  double xDev = deviation( x, xMean );


  double xfac = (1.0/xDev)/(level/100.0);
  double ixfac = 1.0/xfac;

  for( int i=0; i<rows; i++)
    x[i] = double(long(x[i]*xfac))*ixfac;


  ofstream fout( ofilename, ios::out | ios::trunc );

  for( int i=0; i<rows; i++ )
      fout << t[i] << tab << x[i] << endl;

  fout.close();


  gpInfo gpi( ofilename );
  gpi.using1( 1 ). using2( 2 );
  gpi.Title( "time series (noise=" + toString( (int)level ) + "%)" ).xTitle( "t" );
  gpi.setPlotStyle( LINES ).pause();
  gpi.NewFile();
  gpi.AppendToFile();
}














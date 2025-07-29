#include <math.h>
#include <ACG.h>
#include <Normal.h>
#include <Uniform.h>
#include <time.h>

#include "General.h"

#include "Statistical.h"


void noise( const String& ifilename, const String& ofilename, int type, double level )
{
  int rows = getFileRows( ifilename );

  dVector t(rows), x(rows);

  if( readFileColsInc( ifilename, 0, t(), x(), NULL ) ) exit( 1 );

  double xMean = mean( x );
  double xDev = deviation( x, xMean );


  ACG rng( (long)time(NULL) ); // ( seed, size);
  Normal normDist( 0, level*xDev/100.0, &rng );

  for( int i=0; i<rows; i++)
    x[i] += normDist();


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














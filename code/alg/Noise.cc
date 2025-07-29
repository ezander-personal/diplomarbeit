#include <math.h>
#include <ACG.h>
#include <Normal.h>
#include <Uniform.h>
#include <time.h>

#include "General.h"
#include "Statistical.h"
#include "nr.h"


void noise1( const String& ifilename, const String& ofilename, int type, double level )
{
  int rows = getFileRows( ifilename );

  dVector t(rows), x(rows);

  if( readFileColsInc( ifilename, 0, t(), x(), NULL ) ) exit( 1 );

  double xMean = mean( x );
  double xDev = deviation( x, xMean );


  ACG rng( (long)time(NULL) ); // ( seed, size);
  double nl=level*xDev/100.0;
  Normal normDist( 0, nl*nl, &rng );

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

void noise2( const String& ofilename, int length, double level )
{
  int rows=length;

  dVector d( 1, 2*rows);

  ACG rng( (long)time(NULL) ); // ( seed, size);
  Normal normDist( 0, 1.0, &rng );

  for( int i=1; i<=2*rows; i++ ) {
    double f=100.0/double(i);
    d[i]=normDist()*f*f;
  }

  four1( d, rows, 1);


  ofstream fout( ofilename, ios::out | ios::trunc );

  for( int i=0; i<rows; i++ )
      fout << double(i)/100.0 << tab << d[2*i+1] << endl;
  
  fout.close();
  
  gpInfo gpi( ofilename );
  gpi.using1( 1 ). using2( 2 );
  gpi.Title( "time series (noise=" + toString( (int)level ) + "%)" ).xTitle( "t" );
  gpi.setPlotStyle( LINES ).pause();
  gpi.NewFile();
  gpi.AppendToFile();
  
}

void noise( const String& ifilename, const String& ofilename, int type, double level )
{
  if( type==0 )
    noise1( ifilename, ofilename, type, level );
  else
    noise2( ofilename, type, level );
     
}














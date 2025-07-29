#include <math.h>
#include <stdlib.h>


#include "General.h"
#include "Statistical.h"


static int compareDoubles( const double* d1, const double* d2 )
{
  if( *d1>*d2 )
    return 1;
  else if( *d1==*d2 )
    return 0;
  else
    return -1;
}

void stat( const String& ifilename, const String& ofilename, double resolution )
{
  int rows = getFileRows( ifilename );
  int cols = getFileCols( ifilename );

  dVector x( rows ), t( rows );

  readFileCol( ifilename, 1, x(), cols, rows );

  double min, max;
  getMinMax( x, min, max );
  
  qsort( x(), rows, sizeof(double), compareDoubles );
  
  ofstream fout( ofilename, ios::out | ios::trunc );
  
  double res=resolution/100;
  int count=int(1.0/res);
  int N=rows;
  for( int j=0; j<=count; j++ ) {
    int i1 = int(j*res*double(N));
    int i2 = int((j+1)*res*double(N));
    if(i2>=rows) i2=rows-1;
    if(i1>=rows) break;
    fout << x[i1] << tab << double(i2-i1)/(x[i2]-x[i1]) << endl;
    fout << x[i2] << tab << double(i2-i1)/(x[i2]-x[i1]) << endl;
  }
  fout.close();
  	  

  gpInfo gpi( ofilename );
  gpi.using1( 1 ). using2( 2 );
  gpi.Title( "Histogramm Rand" ).xTitle( "x" ).yTitle( "n" );
  gpi.setPlotStyle( LINES | IMPULSES ).pause();
  gpi.NewFile();
  gpi.AppendToFile();
  
}




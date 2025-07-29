#include <math.h>

#include "General.h"
#include "nr.h"


inline double wMean( double x1, double x2, double t)
{
  return (x1 + (x2-x1)*t);
}

void poinc( const String& ifilename, const String& ofilename, int axis, double crossVal, boolean pCross, boolean nCross )
{
  int rows = getFileRows( ifilename );
  int cols = getFileCols( ifilename );

  int maxDim = cols-1;

  dVector t( rows );
  dMatrix v( 0, maxDim, 0, rows-1 );


  readFileCol( ifilename, 0, t(), cols );
  readFileCols( ifilename, cols, v() );

  ofstream foutp( ofilename+".p", ios::out | ios::trunc );
  ofstream foutn( ofilename+".n", ios::out | ios::trunc );

  double* x = v[axis-1];

  for( int i=0; i<rows-1; i++ )
    {
      boolean pCrossing = FALSE, nCrossing = FALSE;
      if( x[i]<=crossVal && x[i+1]>=crossVal ) pCrossing = TRUE;
      if( x[i]>=crossVal && x[i+1]<=crossVal ) nCrossing = TRUE;

      if( x[i]==x[i+1] ) continue;

      double tc = (crossVal-x[i])/(x[i+1]-x[i]);

      if( pCrossing && pCross )
	{
	  foutp << wMean( t[i], t[i+1], tc );

	  for( int j=1; j<=maxDim; j++ )
	    {
	      if( j==axis-1 ) continue;
	      foutp << tab << wMean( v[j][i], v[j][i+1], tc );
	    }
	  foutp << endl;
	}

      if( nCrossing && nCross )
	{
	  foutn << wMean( t[i], t[i+1], tc );

	  for( int j=1; j<=maxDim; j++ )
	    {
	      if( j==axis-1 ) continue;
	      foutn << tab << wMean( v[j][i], v[j][i+1], tc );
	    }
	  foutn << endl;
	}
      
    }

  foutp.close();  
  foutn.close();


  gpInfo gpi( ofilename );
  gpi.Title( "poincare-plot" ).xTitle( "x" ).yTitle( "y" );

  
  gpi.setPlotStyle( POINTS ).pause();
  
  gpi.using1( 2 ).using2( 3 );
  
  gpi.NewFile();

  gpi.color( 1 );
  gpi.dataFile( ofilename+".p", 0 ).dataFile( ofilename+".n", 1 );

  gpi.AppendToFile();
}











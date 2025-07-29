#include <math.h>

#include "General.h"
#include "nr.h"

void takdim( const String& ifilename, const String& ofilename
, double epsilon )
{
  // perliminary
  double begin, end;
  boolean units=TRUE;

  int rows = getFileRows( ifilename );
  int cols = getFileCols( ifilename );

  boolean calcBegin = (begin==-1);
  boolean calcEnd = (end==-1);

  int maxDim = cols-1;

  dVector r( rows );
  dMatrix C( 0, maxDim, 0, rows-1 );


  readFileCol( ifilename, 0, r(), cols );
  readFileCols( ifilename, cols, C() );

  ofstream fout( ofilename, ios::out | ios::trunc );

  int _end, _begin;
  if( !units )
    {
      _end = (int)end; _begin=(int)begin;
    }
  else
    {
      _begin=0; _end=rows-1;
      for( int i=0; i<rows; i++ )
	{
	  if( fabs( r[i]-begin ) < fabs( r[_begin]-begin ) ) _begin=i;
	  if( fabs( r[i]-end ) < fabs( r[_end]-end ) ) _end=i;
	}
    }

  for( int d=1; d<=maxDim; d++ )
    {

      double m,n,err_m=0, err_n=0;
      fout << d << tab << m << tab << err_m << endl; 
    }
  
  fout.close();


  gpInfo gpi( ofilename );
  gpi.Title( "correlation-dimension" ).xTitle( "d" ).yTitle( "D2" );
  
  gpi.setPlotStyle( ERRORBARS | LINES ).pause();
  
  gpi.using1( 1 ).using2( 2 ).using3( 3 );
  
  gpi.NewFile();
  gpi.AppendToFile();
}











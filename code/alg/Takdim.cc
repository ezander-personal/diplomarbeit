#include <math.h>

#include "General.h"
#include "nr.h"

void takdim( const String& ifilename, const String& ofilename, double epsilon )
{
  int rows = getFileRows( ifilename );
  int cols = getFileCols( ifilename );

  int maxDim = cols-1;

  dVector r( rows );
  dMatrix C( 0, maxDim, 0, rows-1 );


  readFileCol( ifilename, 0, r(), cols );
  readFileCols( ifilename, cols, C() );

  ofstream fout( ofilename, ios::out | ios::trunc );

  int _begin=0, _end=0;
  for( int i=0; i<rows; i++ ) {
    if( r[i]<epsilon ) 
      _end=i;
    else
      break;
  }

  for( int d=1; d<=maxDim; d++ ) {
      double sum_ln_r = 0.0;

      double CE=exp(C[d][_end]);

      for( int i=_begin; i<_end; i++ )
	{
	  double ln_r = r[i+1]-r[_end];
	  double ln_C1 = C[d][i];
	  double ln_C2 = C[d][i+1];
	  double C1=exp(ln_C1);
	  double C2=exp(ln_C2);
	  double p=(C2-C1)/CE;
	  
	  sum_ln_r += ln_r * p;
	}

    
    fout << d << tab << -1.0/sum_ln_r <<  endl; 
  }
  
  fout.close();


  gpInfo gpi( ofilename );
  gpi.Title( "correlation-dimension" ).xTitle( "d" ).yTitle( "D2" );
  
  gpi.setPlotStyle( LINESPOINTS ).pause();
  
  gpi.using1( 1 ).using2( 2 );
  
  gpi.NewFile();
  gpi.AppendToFile();
}











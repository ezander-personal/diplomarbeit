#include <math.h>

#include "General.h"
#include "nr.h"
#include <iomanip.h>


void takslp( const String& ifilename, const string& ofilename, int minimum )
{
  // read input file 
  int rows = getFileRows( ifilename );
  int cols = getFileCols( ifilename );

  int points = rows;
  int maxDim = cols-1;

  dVector r( points );
  dMatrix C( 0, maxDim, 0, points ), DC( 1, maxDim, 0, points );

  readFileCol( ifilename, 0, r(), cols );
  readFileCols( ifilename, cols, C() );

  for( int d=1; d<=maxDim; d++ ) {
    
    for( int _end=minimum; _end<points; _end++ ) {
      double sum_ln_r = 0.0;
      double CE=exp(C[d][_end]);
      
      for( int i=0; i<_end; i++ )
	{
	  double ln_r = r[i+1]-r[_end];
	  double ln_C1 = C[d][i];
	  double ln_C2 = C[d][i+1];
	  double C1=exp(ln_C1);
	  double C2=exp(ln_C2);
	  double p=(C2-C1)/CE;
	  
	  sum_ln_r += ln_r * p;
	}
      DC[d][_end]=(sum_ln_r ? -1.0/sum_ln_r : 0 );
    }
    
    // fout << d << tab << -1.0/sum_ln_r <<  endl; 
  }


  // write output
  ofstream fout( ofilename, ios::out | ios::trunc );

  for( int i=minimum; i<points; i++ )
    {
      fout << r[i];
      for( int d=1; d<=maxDim; d++ )
	fout << tab << DC[d][i];
      fout << endl;
    }
  fout.close();
      
  
  // write gnuplot file
  gpInfo gpi( ofilename );

  gpi.Title( "correlation dimension (takens)" ).xTitle( "ln r" ).yTitle( "D_2" );
  gpi.setPlotStyle( LINESPOINTS );
  gpi.pause();
  gpi.using1( 1 ).using2( 2, maxDim+1 );

  gpi.NewFile();
  gpi.AppendToFile();
}










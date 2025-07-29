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

  // calc the slopes
  for( int d=1; d<=maxDim; d++ )
    {
      double sum_ln_r = 0.0;

      // cout << endl << endl << "---------------------------------------" << endl;
      // cout << "dimension: " << d << endl;

      for( int i=0; i<points; i++ )
	{
	  DC[d][i] = 0.0;
	  double lnC1 = C[d][i];
	  double lnC0 = (i==0 ? exp(-100) : C[d][i-1] );
	  double C1 = exp( lnC1 );
	  double C0 = (i==0 ? 0.0 : exp( lnC0 ) );

	  sum_ln_r += r[i] * ( C1 - C0 );
	  if( sum_ln_r )
	    DC[d][i] = -1.0/(sum_ln_r / C1 - r[i]);
	  else
	    DC[d][i] = 0.0;
	  
	  /*	  
		  cout << r[i] << tab << C[d][i] << tab << exp(C[d][i]) << tab
		  << exp(C[d][i]) - exp(C[d][i-1]) << tab << sum_ln_r  << tab 
		  << sum_ln_r / exp( C[d][i]) << tab << (sum_ln_r / exp( C[d][i]) - r[i]) << endl;
		  */
	  /*
	  cout << setprecision( 10 ) 
	       << lnC1 << tab 
	       << lnC0 << tab 
	       << lnC1-lnC0 << tab 
	       << C1 << tab 
	       << C0 << tab 
	       << C1 - C0 << endl;
	       */
	}
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

  gpi.Title( "correlation dimension (takens)" ).xTitle( "log r" ).yTitle( "d{ln C(r)} / d{ ln r}" );
  gpi.setPlotStyle( LINESPOINTS );
  gpi.pause();
  gpi.using1( 1 ).using2( 2, maxDim+1 );

  gpi.NewFile();
  gpi.AppendToFile();
}










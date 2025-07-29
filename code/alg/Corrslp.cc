#include <math.h>

#include "General.h"
#include "Statistical.h"
#include "nr.h"



void corrslp( const String& ifilename, const string& ofilename, double slope, double minRadius, double maxRadius, boolean units, boolean nolog, double radius )
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

  if( radius>0 )
    {
      /*
      for( int i=0; i<points; i++ )
	{
	  double x=exp(r[i])/radius;
	  r[i] = log(2*x-x*x);
	  if( x>1 ) 
	    {
	      points=i;
	      break;
	    }
	}
	*/
      for( int i=0; i<points; i++ ){
	r[i]=log(exp(r[i])+radius/2);
      }
    }

  // calc the slopes
  for( int d=1; d<=maxDim; d++ )
    {
      for( int i=0; i<points-( units ? 2 : slope); i++ )
	{
	  double m,n;
	  if( !units )
	    linReg( r(), C[d], i, i+int(slope), m, n, FALSE, FALSE );
	  else
	    {
	      int max;
	      for( max=i+2; max<points; max++)
		if( r[max]-r[i]>=slope ) break;
	      linReg( r(), C[d], i, max, m, n, FALSE, FALSE );
	    }
	  DC[d][i] = m;
	}
    }


  // write output
  ofstream fout( ofilename, ios::out | ios::trunc );

  for( int i=0; i<points-(units ? 2 : slope); i++ )
    {
      if( ((units && r[i]>=minRadius) || ( !units && i>minRadius)) 
        &&((units && r[i]<=maxRadius) || ( !units && i<(points-slope-maxRadius))) )
	{
	  fout << r[i];
	  for( int d=1; d<=maxDim; d++ )
	    fout << tab << DC[d][i];
	  fout << endl;
	}
    }
  fout.close();
      
  
  // write gnuplot file
  gpInfo gpi( ofilename );

  gpi.Title( "correlation dimension" ).xTitle( "ln r" ).yTitle( "d{ln C(r)} / d{ ln r}" );
  gpi.setPlotStyle( LINESPOINTS );
  gpi.pause();
  gpi.using1( 1 ).using2( 2, maxDim+1 );
  gpi.setYRange().yRange(0,3);

  gpi.NewFile();
  gpi.AppendToFile();
}










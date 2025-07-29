#include <math.h>

#include "General.h"
#include "Statistical.h"
#include "nr.h"


inline double intexp( double d, int n )
{
  double r=1.0;
  if( n<7 ) // this is faster for n<7
    {
      for( int i=0; i<n; i++) r*=d;
    }
  else
    {
      while( n )
	{
	  if( n&1 ) r*=d;
	  d*=d;
	  n>>=1;
	}
    }
  return r;
} 



void corrint( const String& ifilename,  const String& ofilename, int maxDim, int lagTime, int refDist, int ignore, int points, int q, int expansionFac, int binScales, boolean constWindow, boolean euclidianNorm )
{
  // read time series
  int rows = getFileRows( ifilename );
  double min, max, maxAbstInv;

  boolean scalar;

  dVector x;
  dMatrix y;

  if( maxDim )
    {
      scalar = TRUE;

      x.size( rows );

      if( readFileCol( ifilename, 1, x() )  ) exit( 1 );

      getMinMax( x, min, max );
    }
  else
    {
      scalar = FALSE;

      maxDim = getFileCols( ifilename )-1;

      y.size( 0, maxDim+1, 0, rows-1 );
      
      readFileCols( ifilename, maxDim+1, y() );

      for( int i=1; i<=maxDim; i++ )
	{
	  double _min, _max;
	  getMinMax( y[i], rows, _min, _max );
	  if( _min < min ) min = _min;
	  if( _max > max ) max = _max;
	}
      
    }
  if( !euclidianNorm )
    maxAbstInv = 1.0/(max-min);
  else
    {
      maxAbstInv = 1.0/( (max-min) * maxDim );
      binScales += int( log( maxDim ) / log( 2 ) );
    }
  
  
  
  // allocate memory for N_eps
  int m=expansionFac*binScales;

  iMatrix nEps( 1, maxDim, 0, m );
  dMatrix ndEps( 1, maxDim, 0, m );

  nEps.clear(); ndEps.clear();

  dVector abstVec( 1, maxDim );
  int N=rows-(maxDim-1)*lagTime-1;
    
  
  for( int i=0; i<N; i++ )
    {
      if( points!=-1 && i > points ) break;
      
      cerr << i+1 << "/" << N << car;

      for( int j=i+ignore+1; j<N-1; j+=refDist )
	{
	  double dx;

	  for( int dim=1, add=0; dim<=maxDim; dim++, add+=lagTime )
	    {
	      if( scalar )
		dx = x[i+add] - x[j+add];
	      else
		dx = y[dim][i] - y[dim][j];

	      if( !euclidianNorm )
		abstVec[dim] = fabs( dx );
	      else
		abstVec[dim] = ( dim > 0 ? abstVec[dim-1] + dx * dx : dx * dx );
	    }

	  double dabst=0.0;
	  int    nabst=0;
	  for( int dim=1; dim<=maxDim; dim++ )
	    {
	      if( dim==1 || abstVec[dim]>dabst )
		{
		  if( !euclidianNorm )
		    dabst = abstVec[dim];
		  else
		    dabst = sqrt( abstVec[dim] );
		    
		  int nexp;
		  frexp( intexp(dabst*maxAbstInv,expansionFac), &nexp );
		  nabst = nexp+m-1;
		  
		  if( nabst > m ) nabst=m;
		  if( nabst < 0 ) nabst=0;
		}
	      nEps[ dim ][ nabst ]++;
	    }
	  
	}
    }
  

  // sum up nEps
  for( int d=1; d<=maxDim; d++ )
    {
      int n=0;
      for( int i=0; i<=m; i++ )
	{
	  n += nEps[ d ][ i ];
	  
	  if( n==0 ) n=1;
	  
	  ndEps[ d ][ i ] = nEps[ d ][ i ] = n;
	}
    }


  // write all the stuff to disk
  ofstream fout( ofilename, ios::out | ios::trunc );
  for( int i=0; i<=m; i++ )
    {
      // fout << log(i+1);
      fout << double(i-m)/double(expansionFac)*log(2);
      for( int d=1; d<=maxDim; d++ )
	{
	  fout << tab << log( ndEps[ d ][ i ] / ndEps[d][m] );
	  // fout << tab << y[ d ][ i ];
	}
      fout << endl;
    }
  fout.close();  
  
  // write gnuplot file
  gpInfo gpi( ofilename );

  gpi.Title( "correlation integral" ).xTitle( "log r" ).yTitle( "log C(r)" );
  gpi.setPlotStyle( LINESPOINTS );
  gpi.pause();
  gpi.using1( 1 ).using2( 2, maxDim+1 );

  gpi.NewFile();
  gpi.AppendToFile();
}










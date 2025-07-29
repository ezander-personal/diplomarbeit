#include <math.h>

#include "General.h"
#include "nr.h"


void fourier( const String& ifilename, const String& ofilename, int n  )
{
  int rows = getFileRows( ifilename );
  dVector x(rows), t(rows);

  if( readFileColsInc( ifilename, 0, t(), x(), NULL ) ) exit( 1 );

  if( n<= 1 )
    {
      n=1;
      while( 2*n<rows ) n*=2;
    }

  ofstream fout( ofilename, ios::out | ios::trunc );
  
  dVector d(1, 2*n);
    
  for( int i=1; i<=n; i++ )
    {
      d[2*i-1] = x[i-1];
      d[2*i  ] = 0.0;
    }
  
  four1( d, n, 1);



  double delta=t[1]-t[0];
  double f0 = 1.0 / (n*delta);


  for( int i=n/2; i>=1; i-- )
    {
      double re = d[ 2*(n-(i-1))-1 ];
      double im = d[ 2*(n-(i-1)) ];
      
      fout << -(i*f0) << tab << log( hypot( re, im ) ) << tab << re << tab << im << tab << atan2( im, re ) << endl;
    }

  for( int i=0; i<n/2; i++ )
    {
      double re = d[ 2*i+1 ];
      double im = d[ 2*i+2 ];
      
      fout << i*f0 << tab << log( hypot( re, im ) ) << tab << re << tab << im << tab << atan2( im, re ) << endl;
    }



  fout.close();
  

  gpInfo gpi( ofilename );
  gpi.using1( 1 ). using2( 2 );
  gpi.Title( "fourier spectrum" ).xTitle( "w" ).yTitle( "log P(w)" );
  gpi.setXRange().xRange( 0.0, n*f0/2.0 );
  gpi.setPlotStyle( LINES ).pause();
  gpi.NewFile();
  gpi.AppendToFile();
}










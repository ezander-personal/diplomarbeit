#include "General.h"
#include "Statistical.h"

#include "nr.h"

#include <math.h>


void autocorr( const String& ifilename, const String& ofilename, int maxtau, boolean correction )
{
  ofstream fout( ofilename, ios::out | ios::trunc );
  
  int rows = getFileRows( ifilename );
  
  dVector x(rows), t(rows);
  if( readFileColsInc( ifilename, 0, t(), x(), NULL ) ) exit( 1 );

  dVector d(0,maxtau);
  autoCorr( x(), rows, d(), 0, maxtau, correction );
  
  boolean zeroFound = FALSE;
  for( int i=0; i<=maxtau; i++ )
    {
      fout << t[i]-t[0] << tab << d[i] << endl;
      
      if( !zeroFound && i<maxtau && d[i]>=0 && d[i+1]<0 )
	{
	  zeroFound = TRUE;
	  cout << "autocorrelation crosses zero at " << i << endl;
	}
    }
  
  fout.close();
  
  if( !zeroFound ) cout << "couldn't find zero-crossing" << endl;

  
  gpInfo gpi( ofilename );
  gpi.using1( 1 ). using2( 2 );
  gpi.Title( "auto-correlation" ).xTitle( "tau" ).yTitle("C(tau)");
  gpi.setPlotStyle( LINES ).pause();
  gpi.NewFile();
  gpi.AppendToFile();
}


void autocorr2( const String& ifilename, const String& ofilename, int maxtau, boolean correction )
{
  int rows = getFileRows( ifilename );
  
  dVector x(rows), t(rows);
  if( readFileColsInc( ifilename, 0, t(), x(), NULL ) ) exit( 1 );

  int n=1;
  while( n<maxtau+1 ) n*=2;

  dVector d(1, 2*n);

  for( int i=1; i<=n; i++ )
    {
      d[2*i-1] = x[i-1];
      d[2*i  ] = 0.0;
    }
  
  four1( d, n, 1);

  for( int i=1; i<=n; i++ )
    {
      d[2*i-1 ] = hypot( d[2*i-1], d[2*i] );
      d[2*i ] = 0.0;
    }

  four1( d, n, -1);

 
  ofstream fout( ofilename, ios::out | ios::trunc );
  
  boolean zeroFound = FALSE;
  for( int i=0; i<=maxtau; i++ )
    {
      fout << t[i]-t[0] << tab << d[2*i+1]/d[1] << tab << d[2*i] << endl;
      
      if( !zeroFound && i<maxtau && d[2*+1]>=0 && d[2*i+3]<0 )
	{
	  zeroFound = TRUE;
	  cout << "autocorrelation crosses zero at " << i+1 << endl;
	}
    }
  
  fout.close();
  
  if( !zeroFound ) cout << "couldn't find zero-crossing" << endl;

  
  gpInfo gpi( ofilename );
  gpi.using1( 1 ). using2( 2 );
  gpi.Title( "auto-correlation" ).xTitle( "tau" ).yTitle("C(tau)");
  gpi.setPlotStyle( LINES ).pause();
  gpi.NewFile();
  gpi.AppendToFile();
}







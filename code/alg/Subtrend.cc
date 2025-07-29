#include "General.h"
#include "Statistical.h"


void subtrend( const String& ifilename, const String& ofilename )
{
  int rows = getFileRows( ifilename );
  
  dVector x(rows), t(rows);
  if( readFileColsInc( ifilename, 0, t(), x(), NULL ) ) exit( 1 );

  double m,n;
  linReg( t(), x(), 0, rows, m, n );

  cerr << "Offset: " << n << "  Slope: " << m << endl;

  const int count=10, wlength=1000; 
  dVector xq(count), tq(count);
  for( int i=0; i<count; i++ ){
    xq[i]=mean( x()+i*wlength, wlength );
    tq[i]=mean( t()+i*wlength, wlength );
  }
  linReg( tq(), xq(), 0, count, m, n );
  cerr << "Offset: " << n << "  Slope: " << m << endl;


  ofstream fout( ofilename, ios::out | ios::trunc );

  for( int i=0; i<rows; i++ )
    fout << t[i] << tab << x[i]-m*t[i] << endl;

  fout.close();

  gpInfo gpi( ofilename );
  gpi.using1( 1 ). using2( 2 );
  gpi.Title( "time series (trendless)" ).xTitle( "t" );
  gpi.setPlotStyle( LINES ).pause();
  gpi.NewFile();
  gpi.AppendToFile();

}



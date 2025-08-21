#include "General.h"

void cuts( const String& ifilename, const String& ofilename, int length, int diff, int max )
{  
  int rows = getFileRows( ifilename );
  
  dVector x(rows), t(rows);
  if( readFileColsInc( ifilename, 0, t(), x(), NULL ) ) exit( 1 );

  if( diff<=0 ) diff = length/2;
  int count = 0;
  int start = 0;

  while ( TRUE )
    {
      count++;

      if( max!=-1 && count>max ) break;
      if( start+length-1>=rows ) break;

      ofstream fout( ofilename + toString( count ), ios::out | ios::trunc );
      
      for( int i=start; i<start+length; i++ )
	{
	  fout << t[i] << tab << x[i] << endl;
	}
      
      fout.close();
      start+=diff;
    }



  gpInfo gpi( ofilename );
  gpi.NewFile();
  for ( int i = 1; i<count; ++i)
  {
    gpi.dataFile(ofilename + toString( i ));
    gpi.using1( 1 ). using2( 2 );
    gpi.Title( "time series" ).xTitle( "t" );
    gpi.setPlotStyle( LINES ).pause();
    gpi.AppendToFile();
  }
}














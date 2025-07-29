#include <math.h>

#include "General.h"

#include "Statistical.h"


void histo( const String& ifilename, const String& ofilename, double resolution, boolean isInteger, int col )
{
  int rows = getFileRows( ifilename );
  int cols = getFileCols( ifilename );

  dVector x( rows );

  readFileCol( ifilename, col-1, x(), cols, rows );

  if( isInteger )
    {
      ASSERT( 0 );
    }
  else
    {
      double min, max;
      getMinMax( x, min, max );

      int count=int(100.0/resolution)+1;
      double xres=(max-min)/(100.0/resolution);
      int n[count];
      for( int i=0; i<count; i++ ) n[i]=0;

      for( int i=0; i<rows; i++ )
	{
	  int index = int( (x[i]-min)/xres );
	  ASSERT( index>=0 );
	  if( index==count ) index=count-1;
	  ASSERT( index<count );
	  n[index]++;
	}
      
      
      ofstream fout( ofilename, ios::out | ios::trunc );
      for( int i=0; i<count; i++ )
	{
	  fout << i*xres+min << tab << n[i] << endl;
	}
      
      fout.close();
    }





  gpInfo gpi( ofilename );
  gpi.using1( 1 ). using2( 2 );
  gpi.Title( "Histogramm" ).xTitle( "x" ).yTitle( "n" );
  gpi.setPlotStyle( POINTS ).pause();
  gpi.NewFile();
  gpi.AppendToFile();
}














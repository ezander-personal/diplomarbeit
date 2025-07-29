#include <math.h>
#include "General.h"



double Mean( double* x, int length )
{
  double sum=0.0;
  for( int i=0; i<length; i++,x++ ) sum+=*x;
  return sum/length;
}

double corrCoefficient( double* x, int length )
{
  double xa = x[0], xe = x[length-1];
  double m = (xe-xa)/(length-1.0);

  double meanx = Mean( x, length );
  double meany = (xa+xe)/2.0;

  double dxy=0.0, dxx=0.0, dyy=0.0;

  for( int i=0; i<length; i++ )
    {
      double dx = x[i] - meanx;
      double dy = (i*m+xa) - meany;

      dxy += dx * dy;
      dxx += dx * dx;
      dyy += dy * dy;
    }

  if( dxx==0.0 || dyy==0 ) 
    return 1;
  else
    return dxy / sqrt( dxx * dyy );
}

void linear( const String& ifilename, const String& ofilename, int maxLength, int points )
{
  int size = getFileRows( ifilename );
  if( size==-1 ) return;

  
  dVector arr(size);

  int realsize = size;
  if( points!=-1 && points<=size ) realsize=points;

  if( getFileCols( ifilename ) == 1 )
    { if( readFileCol( ifilename, 0, arr() ) ) return; }
  else
    { if( readFileCol( ifilename, 1, arr() ) ) return; }


  ofstream fout( ofilename, ios::out | ios::trunc );

  for( int length=2; length<=maxLength; length++ )
    {
      double corrsum = 0.0;

      for( int pos=0; pos<realsize-length; pos++ )
	{
	  corrsum += corrCoefficient( arr()+pos, length );
	}

      fout << length << tab << corrsum / (realsize - length) << endl;
    }
  
  fout.close();

  gpInfo gpi( ofilename );
  gpi.Title( "linearity-test" ).xTitle( "length" ).yTitle( "linearity-ocefficient" );
  
  gpi.setPlotStyle( LINESPOINTS ).pause();
  
  gpi.using1( 1 ).using2( 2 );
  
  gpi.NewFile();
  gpi.AppendToFile();

}








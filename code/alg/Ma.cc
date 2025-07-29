#include <math.h>

#include "General.h"


double WeightedAvg( double* x, int nData, int i, double* weights, int start, int count, boolean logarithmic )
{
  int n=i+start; 
  double d=0.0, w=0.0, y=0.0; 

  for( int j=0; j<count; j++ )
    {
      if( n<0 )
	y = x[0];
      else if (n>=nData )
	y = x[ nData-1 ];
      else
	y = x[n];
      
      d += weights[j]*( logarithmic ? log( y ) : y );

      w=w+weights[j];
      n++;
    }
  return logarithmic ? exp(d/w) :  d/w;
}


void ma( const String& ifilename, const String& ofilename, int width, boolean gaussian )
{
  int rows=getFileRows( ifilename );
  dVector x(rows), t(rows);

  if( readFileColsInc( ifilename, 0, t(), x(), NULL ) ) exit( 1 );

  ofstream fout( ofilename, ios::out | ios::trunc );
  
  double weight[ width ];
  for( int i=0; i<width; i++ ) weight[i] = 1/double(width);
  // int count = 7, start = -3;

  for( int i=0; i<rows; i++ )
    {
      fout << t[i] << tab << x[i] - WeightedAvg( x(), rows, i, weight, -(int)(width/2), width, FALSE ) << endl;
    }


  fout.close();

  WriteGpFile( ofilename, "filtered", "t", NULL, 1, FALSE );
}




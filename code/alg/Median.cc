#include <stdlib.h>

#include "General.h"


int compare_double( const double* a, const double* b )
{
  if( *a>*b )
    return 0;
  else
    return 1;
}

inline void sort( double* x, int length )
{
  qsort( x, length, sizeof( double ), compare_double );
}

void medianFilter( double *vector, int length, int order )
{
  int sortLen = 2*order+1;

  double y[ length ];
  double sortArr[ sortLen ];
  double* psort = sortArr+order;

  for( int i=0; i<length; i++ )
    {
      for( int j=-order; j<=order; j++ )
	{
	  if( i+j<0 ) 
	    psort[j]=vector[0];
	  else if( i+j>=length )
	    psort[j]=vector[length-1];
	  else
	    psort[j]=vector[i+j];
	}

      sort( sortArr, sortLen );
      y[i] = *psort;
    }

  memcpy( vector, y, length*sizeof(double) );
}


void median( const string& ifilename, const string& ofilename, int order, int passes )
{
  int rows = getFileRows( ifilename );
  dVector x(rows), t(rows), re(rows), im(rows), phi(rows);
  
  if( readFileColsInc( ifilename, 0, t(), x(), re(), im(), phi(), NULL ) ) exit( 1 );
  
  
  for( int p=0; p<passes; p++ )
    medianFilter( x(), rows, order );


  
  ofstream fout( ofilename, ios::out | ios::trunc );

  for( int i=0; i<rows; i++ )
    fout << t[i] << tab << x[i] << tab << re[i] << tab << im[i] << tab << phi[i] << endl;

  fout.close();
  
  gpInfo gpi( ofilename );
  gpi.using1( 1 ). using2( 2 );
  gpi.Title( "fourier spectrum" ).xTitle( "w" ).yTitle( "log P(w)" );
  gpi.setXRange().xRange( 0.0, t[rows-1] );
  gpi.setPlotStyle( LINES ).pause();
  gpi.NewFile();
  gpi.AppendToFile();

}

































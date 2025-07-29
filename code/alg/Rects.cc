#include "General.h"

void rects( const String& ifilename, const String& ofilename, int lag, int dimension, boolean lines )
{
  ofstream fout( ofilename, ios::out | ios::trunc );

  int rows = getFileRows( ifilename );

  dVector d(rows), t(rows);
  
  if( readFileColsInc( ifilename, 0, t(), d(), NULL) ) exit( 1 );

  int N = lag*(dimension-1);

  for( int k=0; k<rows-N; k++ )
    {
      double *x = d()+k;

      fout << t[k];

      for( int i=0; i<dimension; i++ )
	{
	  fout << tab << x[i*lag];
	}
      fout << endl;
    }
  
  fout.close();
  
  WriteGpFile( ofilename, "reconstruction", NULL, NULL, dimension, !lines ); 
}










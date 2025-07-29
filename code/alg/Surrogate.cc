#include <ACG.h>
#include <Normal.h>
#include <Uniform.h>
#include <time.h>
#include <stdlib.h>

#include "nr.h"

#include "General.h"


/*
**  some helpers for sortby
*/

inline int cmp_double( double a, double b) { if( a>b ) return 1; else if( a<b) return -1; else return 0; }
inline int cmp_int( int a, int b) { return a-b; };

int cmp_d( const double* a, const double* b ) { return cmp_double( *a, *b ); }
int cmp_i( const int* a, const int* b ) { return cmp_int( *a, *b ); }

struct sortstruct
{
  union
  {
    int i;
    double dummy;
  };
  double d;
  
  void set( int i, double d ) { this->i=i; this->d=d; }

  static int cmp_d( const sortstruct* a, const sortstruct* b ) { return cmp_double(a->d, b->d); }
  static int cmp_i( const sortstruct* a, const sortstruct* b ) { return cmp_int( a->i, b->i ); }
};


/*
** sortby sorts the second array in the orer of the first one
*/

void sortby( double* a ,double* b, int n )
{
  sortstruct ss[ n ];

  for( int i=0; i<n; i++ ) ss[i].set(i,a[i]);

  qsort( ss, n, sizeof(sortstruct), (comparison_fn_t)sortstruct::cmp_d );
  qsort( b, n, sizeof(double), (comparison_fn_t)cmp_d );

  for( int i=0; i<n; i++ ) ss[i].d = b[i];

  qsort( ss, n, sizeof(sortstruct), (comparison_fn_t)sortstruct::cmp_i );

  for( int i=0; i<n; i++ ) b[i] = ss[i].d;
}

void surrogate( const String& ifilename, const String& ofilename, char type, boolean amplitudeAdj, int number )
{
  // create a random number generator and two distributions
  // for latter use

  ACG rng( (long)time(NULL) ); // ( seed, size);
  Normal normDist( 0, 1, &rng );
  Uniform uniDist( 0, 2*PI, &rng );


  // read the file

  int rows = getFileRows( ifilename );
  
  dVector x(rows), t(rows), s(rows), s2(rows), y(rows);

  
  // we need rows to be a multiple of two for fourier-transform
  int maxrows=1;
  while( 2*maxrows<=rows )
    maxrows*=2;

  rows = maxrows;

  if( readFileColsInc( ifilename, 0, t(), x(), NULL ) ) exit( 1 );
  

  // create gaussian distributed time series s which follows x
  // or copy original time sereis x to s

  if( amplitudeAdj )
    {
      for( int i=0; i<rows; i++ )
	s[i] = normDist();
      
      sortby( x(), s(), rows );
    }
  else
    {
      for( int i=0; i<rows; i++ ) s[i] = x[i];
    }


  // fourier transform the time series
  // and save the amplitude in s (still have to implement WFT)
  dVector d( 1, 2*rows);
  
  for( int i=0; i<rows; i++) 
    d[2*i+1]=s[i];

  four1( d, rows, 1);

  for( int i=0; i<rows; i++) 
    s[i] =  hypot( d[2*i+1], d[2*i+2] );
  
  
  // create surrogate data from s (n times)
  
  dVector d2( 1, 2*rows );

  for( int j=0; j<number; j++ )
    {
      // shift the phases

      d2[1] = d[1];
      d2[2] = d[2];
      d2[rows+1] = d[rows+1];
      d2[rows+2] = d[rows+2];

      int i1=3; int i2=2*rows-1;

      for( int i=1; i<rows/2; i++ )
	// for( int i=0; i<rows; i++ )
	{
	  double phi = uniDist();

	  d2[i1]   =  s[i] * cos( phi );
	  d2[i1+1] =  s[i] * sin( phi );
	  d2[i2]   =  s[i] * cos( phi );
	  d2[i2+1] = -s[i] * sin( phi );

	  i1+=2; i2-=2;
	}


      // backtransfromation, nromalization, save in s2
      four1( d2, rows, -1);
      
      for( int i=0; i<rows; i++) 
	{
	  s2[i]=d2[2*i+1] / (double)rows;
	}

      // now sort copied original time series according to s2
      // or copy s2 to new surrogate time series y

      if( amplitudeAdj )
	{
	  for( int i=0; i<rows; i++ ) y[i] = x[i];
	  sortby( s2(), y(), rows );
	}
      else
	{
	  for( int i=0; i<rows; i++ ) y[i] = s2[i];
	}

      // save surrogate data y on disk
      ofstream fout;
      if( number>1 )
	fout.open( ofilename+toString(j+1), ios::out | ios::trunc );
      else
	fout.open( ofilename, ios::out | ios::trunc );

      for( int i=0; i<rows; i++ )
	{
	  fout << t[i] << tab << y[i] << endl;
	}
      fout.close();
    }

  
  // write gp-file

  gpInfo gpi( ofilename );
  gpi.using1( 1 ). using2( 2 );
  gpi.setPlotStyle( LINES ).pause();
  gpi.NewFile();

  gpi.Title( "original" ).xTitle( "t" ).yTitle("x");
  gpi.dataFile( ifilename );
  gpi.AppendToFile();

  gpi.Title( "surrogates" ).xTitle( "t" ).yTitle("x");
  if( number>1 )
    for( int j=0; j<number; j++) {
      gpi.dataFile( ofilename+toString(j+1) );
      gpi.AppendToFile();
    }
  else {
    gpi.dataFile( ofilename );
    gpi.AppendToFile();
  }

}










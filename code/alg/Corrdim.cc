#include <math.h>

#include "General.h"
#include "Statistical.h"
#include "nr.h"

#define MIN_BEGIN_END_DIFF  10
#define MIN_BEGIN_DIFF 1.0e-8

int findMinBegin( double* x, int count )
{
  int minBegin = 0;
  while( TRUE )
    {
      if( fabs( x[minBegin+1]-x[minBegin] ) > MIN_BEGIN_DIFF ) return minBegin;
      minBegin++;
      if( minBegin+1 == count ) return 0;
    }
}

void findMaxCC( double* x, double* y, int count, boolean calcBegin, boolean calcEnd, int* begin, int* end )
{
  int _begin=*begin, _end=*end;
  double minCC;

  if( calcBegin && calcEnd )
    {
      _begin=0; _end=_begin+MIN_BEGIN_END_DIFF;
      minCC = correlationCoefficient( x+_begin, y+_begin, _end-_begin ); 

      for( int i=0; i<count-MIN_BEGIN_END_DIFF; i++ )
	for( int j=i+MIN_BEGIN_END_DIFF; j<count; j++ )
	  {
	    double cc = correlationCoefficient( x+i, y+i, j-i ); 

	    if( cc > minCC ) 
	      {
		minCC = cc;
		_begin = i; _end = j;
	      }
	  }
    }
  else if( calcBegin )
    {
      _begin=0; 
      minCC = correlationCoefficient( x+_begin, y+_begin, _end-_begin ); 

      for( int i=0; i<_end-MIN_BEGIN_END_DIFF; i++ )
	{
	  double cc = correlationCoefficient( x+i, y+i, _end-_begin ); 
	  if( cc > minCC ) 
	    {
	      minCC = cc;
	      _begin = i;
	    }
	  }
    }
  else if( calcEnd )
    {
      _end=_begin+MIN_BEGIN_END_DIFF; 
      minCC = correlationCoefficient( x+_begin, y+_begin, _end-_begin ); 

      for( int j=0; j<count; j++ )
	{
	  double cc = correlationCoefficient( x+_begin, y+_begin, j-_begin ); 
	  if( cc > minCC ) 
	    {
	      minCC = cc;
	      _end = j;
	    }
	  }
    }
  else
    ASSERT( FALSE );

  *begin = _begin; *end = _end;
}

void corrdim( const String& ifilename, const String& ofilename, double begin, double end, boolean units )
{
  int rows = getFileRows( ifilename );
  int cols = getFileCols( ifilename );

  boolean calcBegin = (begin==-1);
  boolean calcEnd = (end==-1);

  int maxDim = cols-1;

  dVector r( rows );
  dMatrix C( 0, maxDim, 0, rows-1 );


  readFileCol( ifilename, 0, r(), cols );
  readFileCols( ifilename, cols, C() );

  ofstream fout( ofilename, ios::out | ios::trunc );

  int _end, _begin;
  if( !units )
    {
      _end = (int)end; _begin=(int)begin;
    }
  else
    {
      _begin=0; _end=rows-1;
      for( int i=0; i<rows; i++ )
	{
	  if( fabs( r[i]-begin ) < fabs( r[_begin]-begin ) ) _begin=i;
	  if( fabs( r[i]-end ) < fabs( r[_end]-end ) ) _end=i;
	}
    }

  for( int d=1; d<=maxDim; d++ )
    {

      double m,n,err_m=0, err_n=0;
      int minBegin = findMinBegin( C[d], rows ) + 3;

      if( calcBegin || calcEnd ) findMaxCC( r(), C[d], rows, calcBegin, calcEnd, &_begin, &_end );

      if( _begin < minBegin ) _begin = minBegin;
      if( _end < minBegin + MIN_BEGIN_END_DIFF ) _end = minBegin + MIN_BEGIN_END_DIFF;
      if( _end >= rows ) _end = rows-1;
      cerr << "hurps" << tab << _begin << tab << r[_begin] << tab  << _end << tab << r[_end] << endl;
      linReg( r(), C[d], _begin, _end, m, n, err_m, err_n, FALSE, FALSE );
      fout << d << tab << m << tab << err_m << endl; 
    }
  
  fout.close();


  gpInfo gpi( ofilename );
  gpi.Title( "correlation-dimension" ).xTitle( "d" ).yTitle( "D2" );
  
  gpi.setPlotStyle( ERRORBARS | LINES ).pause();
  
  gpi.using1( 1 ).using2( 2 ).using3( 3 );
  
  gpi.NewFile();
  gpi.AppendToFile();
}










